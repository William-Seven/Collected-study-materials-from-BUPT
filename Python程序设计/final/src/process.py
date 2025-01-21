import os
import rasterio
from rasterio.features import geometry_mask
from shapely.geometry import box
import numpy as np
import json
import concurrent.futures

# 配置输入输出路径
input_folder = "/mnt/new_disk/dh/zcy/final/gpw-v4-population-count-rev11_2020_30_sec_asc/"
output_file = "population_3x3_degree.json"

# 网格大小（单位：度）
GRID_SIZE = 3

# 存储预处理后的网格人口数据
grid_population_data = {}


def load_raster_files():
    """加载所有的ASC文件，并提取相关的元数据"""
    raster_files = []
    for filename in os.listdir(input_folder):
        if filename.endswith(".asc"):
            file_path = os.path.join(input_folder, filename)
            with rasterio.open(file_path) as src:
                bounds = src.bounds
                transform = src.transform
                nodata = src.nodata
                shape = src.shape

                # 检查文件是否包含有效的地理变换信息
                if transform.is_identity:
                    print(
                        f"Skipping file {file_path} due to missing geotransform.")
                    continue

                raster_files.append({
                    "path": file_path,
                    "bounds": box(bounds.left, bounds.bottom, bounds.right, bounds.top),
                    "transform": transform,
                    "nodata": nodata,
                    "shape": shape
                })
    return raster_files


raster_files = load_raster_files()


def generate_grid():
    """生成全球5°x5°的经纬度网格"""
    grid = []
    lon_min, lon_max = -180, 180
    lat_min, lat_max = -90, 90
    for lon in np.arange(lon_min, lon_max, GRID_SIZE):
        for lat in np.arange(lat_min, lat_max, GRID_SIZE):
            grid.append(box(lon, lat, lon + GRID_SIZE, lat + GRID_SIZE))
    return grid


# 创建全局网格
global_grid = generate_grid()


def calculate_population(grid_cell, raster_files):
    """计算网格内的总人口数"""
    total_population = 0
    for raster_file in raster_files:
        if not grid_cell.intersects(raster_file["bounds"]):
            continue
        with rasterio.open(raster_file["path"]) as src:
            mask = geometry_mask(
                [grid_cell], transform=src.transform, invert=True, out_shape=src.shape)
            data = src.read(1)  # 读取第一个波段
            if src.nodata is not None:
                data[data == src.nodata] = 0

            total_population += data[mask].sum()

    # 返回整数人口数
    return int(total_population) if total_population > 0 else 0


def process_grid_cell(grid_cell):
    """处理单个网格的任务：计算该网格的总人口"""
    grid_coords = tuple(grid_cell.bounds)
    population = calculate_population(grid_cell, raster_files)
    return grid_coords, population


def preprocess_population_data():
    """预处理并计算所有网格的总人口，并将结果保存为JSON格式"""
    print("Starting grid population data processing...")
    total_grids = len(global_grid)
    processed_count = 0

    # 使用多线程处理每个网格的任务
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = {executor.submit(
            process_grid_cell, grid_cell): grid_cell for grid_cell in global_grid}

        for future in concurrent.futures.as_completed(futures):
            grid_coords, population = future.result()
            grid_population_data[grid_coords] = population

            processed_count += 1
            if processed_count % 10 == 0 or processed_count == total_grids:
                print(f"Progress: {processed_count / total_grids * 100:.2f}%")

    print("Grid population data processing completed.")
    print(f"Saving processed data to {output_file}...")

    # 转换键为字符串以兼容JSON格式
    json_compatible_data = {str(k): v for k, v in grid_population_data.items()}

    # 将处理结果保存为JSON文件
    with open(output_file, 'w') as f:
        json.dump(json_compatible_data, f, indent=4)
    print("Data successfully saved.")


if __name__ == '__main__':
    preprocess_population_data()
