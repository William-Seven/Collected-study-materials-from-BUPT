from sanic import Sanic, response
import json
from shapely.geometry import shape, box

app = Sanic("PopulationQueryService")

# 预处理文件路径
population_file = "/mnt/new_disk/dh/zcy/final/src/population_3x3_degree.json"

# 加载人口数据
with open(population_file, "r") as f:
    population_data = json.load(f)

# 转换人口数据为更高效的字典
grid_population = {}
for key, value in population_data.items():
    # 解析 JSON 的元组字符串为浮点数元组
    key_tuple = tuple(map(float, key.strip("()").split(", ")))
    grid_population[key_tuple] = value


@app.post("/query")
async def query_population(request):
    try:
        geojson = request.json
        polygon = shape(geojson)  # 使用 shapely 解析 GeoJSON 多边形
        intersected_grids = []

        # 遍历所有网格数据，计算与多边形的交集及人口占比
        for (lon_min, lat_min, lon_max, lat_max), population in grid_population.items():
            grid_box = box(lon_min, lat_min, lon_max,
                           lat_max)  # 构造栅格的 Polygon 对象
            intersection = polygon.intersection(grid_box)  # 计算交集

            if not intersection.is_empty:  # 如果交集不为空
                # 计算交集面积与栅格面积的比例
                grid_area = grid_box.area  # 栅格面积
                intersected_area = intersection.area  # 交集面积
                proportion = intersected_area / grid_area

                # 根据交集比例调整人口数
                adjusted_population = population * proportion

                # 保存结果
                intersected_grids.append({
                    "grid": [lon_min, lat_min, lon_max, lat_max],
                    "population": adjusted_population,
                    "proportion": proportion
                })

        return response.json({"grids": intersected_grids})
    except Exception as e:
        return response.json({"error": str(e)}, status=400)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)
