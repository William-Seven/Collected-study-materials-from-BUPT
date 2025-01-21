import aiohttp
import asyncio
import numpy as np
import matplotlib.pyplot as plt


class QueryClient:
    def __init__(self, base_url):
        self.base_url = base_url

    async def fetch_data(self, endpoint, params):
        """
        请求服务端数据
        """
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{self.base_url}/{endpoint}", params=params) as response:
                if response.status == 200:
                    return await response.json()  # 直接解析为 JSON
                else:
                    raise Exception(f"Failed to fetch data: {response.status}")

    async def query_no_smoothing(self, start_year, end_year, order):
        """
        获取 No_Smoothing 数据
        """
        endpoint = "query/json"
        params = {
            "start_year": start_year,
            "end_year": end_year,
            "order": order
        }
        data = await self.fetch_data(endpoint, params)
        return [(entry["Year"], entry["No_Smoothing"]) for entry in data]


def simple_lowess(x, y, frac=0.1):
    """
    简单实现 LOWESS 算法
    """
    n = len(x)
    span = int(np.ceil(frac * n))  # 窗口大小
    y_smoothed = np.zeros(n)

    for i in range(n):
        distances = np.abs(x - x[i])
        weights = np.exp(-distances**2 / (2 * (distances.max() / 2)**2))

        indices = np.argsort(distances)[:span]
        x_window = x[indices]
        y_window = y[indices]
        weights_window = weights[indices]

        b = np.polyfit(x_window, y_window, 1, w=weights_window)
        y_smoothed[i] = b[0] * x[i] + b[1]

    return list(zip(x, y_smoothed))


def calculate_lowess(data, frac=0.1):
    """
    计算 LOWESS 平滑结果
    """
    years, values = zip(*data)
    return simple_lowess(np.array(years), np.array(values), frac=frac)


async def main():
    client = QueryClient("http://localhost:8000")

    # 获取 No_Smoothing 数据并按年份排序
    no_smoothing_data = sorted(await client.query_no_smoothing(1880, 2022, "asc"), key=lambda x: x[0])

    # 计算 LOWESS 平滑曲线，确保滑动窗口为 ±5 年
    lowess_result = calculate_lowess(
        no_smoothing_data, frac=11 / len(no_smoothing_data))

    # 打印对比结果
    print("\nYear    No_Smoothing   LOWESS_Calculated")
    for (year, no_smoothing), (lowess_year, lowess_value) in zip(no_smoothing_data, lowess_result):
        print(f"{year:<7} {no_smoothing:<14} {lowess_value:<16.2f}")

    # 可视化对比
    years, no_smoothing_values = zip(*no_smoothing_data)
    _, lowess_values = zip(*lowess_result)

    plt.figure(figsize=(10, 6))
    plt.plot(years, no_smoothing_values,
             label="No Smoothing (Original)", color="blue", alpha=0.6)
    plt.plot(years, lowess_values, label="LOWESS (Calculated)",
             color="red", alpha=0.8)
    plt.title("No Smoothing vs LOWESS")
    plt.xlabel("Year")
    plt.ylabel("Temperature Anomaly (°C)")
    plt.legend()
    plt.grid()
    plt.show()

if __name__ == "__main__":
    asyncio.run(main())
