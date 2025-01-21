import requests
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import matplotlib.colors as mcolors
import numpy as np

# 服务端地址
server_url = "http://localhost:8000/query"

# 构造查询的 GeoJSON 多边形（完整地图查询范围）
geojson_polygon = {
    "type": "Polygon",
    "coordinates": [[
        [-180.0, -90.0], [180.0, -90.0], [180.0, 90.0], [-180.0, 90.0], [-180.0, -90.0]
    ]]
}

# 发送请求到服务端
response = requests.post(server_url, json=geojson_polygon)
if response.status_code == 200:
    data = response.json()
    grids = data.get("grids", [])
    print(f"Received {len(grids)} grids from server.")
else:
    print(f"Error: {response.json()}")
    grids = []

# 如果没有数据则退出
if not grids:
    print("No data to plot.")
    exit()

# 获取人口的最大值，过滤掉人口为 0 的格子
valid_populations = [g["population"] for g in grids if g["population"] > 0]
if valid_populations:
    max_population = max(valid_populations)
else:
    max_population = 1  # 防止除以 0

# 自定义颜色映射：从白色到红色，再到黑色
colors = [(1, 1, 1), (1, 0, 0), (0, 0, 0)]  # RGB: 白色 -> 红色 -> 黑色
cmap = mcolors.LinearSegmentedColormap.from_list("custom_cmap", colors)

# 创建绘图
fig, ax = plt.subplots(figsize=(16, 8))  # 调整比例适配 3°×3° 的网格密度
ax.set_xlim(-180, 180)  # 设置经度范围
ax.set_ylim(-90, 90)    # 设置纬度范围
ax.set_aspect('equal', adjustable='box')  # 保持正方形格子

# 绘制每个格子
for grid in grids:
    lon_min, lat_min, lon_max, lat_max = grid["grid"]
    population = grid["population"]

    # 计算颜色深度（根据人口数量）
    if population > 0:
        color_intensity = population / max_population
    else:
        color_intensity = 0  # 人口为 0 的格子颜色设为白色

    # 绘制矩形格子（无边框）
    rect = Rectangle((lon_min, lat_min), lon_max - lon_min, lat_max - lat_min,
                     color=cmap(color_intensity), lw=0)  # 自定义颜色映射
    ax.add_patch(rect)

# 添加自定义颜色图
norm = mcolors.Normalize(vmin=0, vmax=max_population)
sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])  # 添加空数组以支持 colorbar
cbar = plt.colorbar(sm, ax=ax, orientation='vertical', pad=0.02)
cbar.set_label("Population", fontsize=12)

# 设置标题和坐标轴
plt.title("Population Distribution (3°×3° Grids)", fontsize=14)
plt.xlabel("Longitude", fontsize=12)
plt.ylabel("Latitude", fontsize=12)

# 保存图片
save_path = "population_distribution_3x3.png"
plt.savefig(save_path, dpi=300, bbox_inches="tight")
plt.show()

print(f"Heatmap saved to {save_path}")
