import aiohttp
import asyncio
import xmltodict

# 服务查询客户端类


class QueryClient:
    def __init__(self, base_url):
        self.base_url = base_url

    async def fetch_data(self, endpoint, params):
        """
        请求服务端数据
        :param endpoint: 服务端的API路径
        :param params: 查询参数
        :return: 服务端返回的原始数据
        """
        async with aiohttp.ClientSession() as session:
            async with session.get(f"{self.base_url}/{endpoint}", params=params) as response:
                if response.status == 200:
                    return await response.text()
                else:
                    raise Exception(f"Failed to fetch data: {response.status}")

    def json_to_text(self, json_data):
        """
        将JSON数据转换为TEXT格式
        :param json_data: JSON格式数据
        :return: TEXT格式数据
        """
        import json
        data = json.loads(json_data)
        return "\n".join(f"{entry['Year']} {entry['No_Smoothing']} {entry['Lowess']}" for entry in data)

    def xml_to_text(self, xml_data):
        """
        将XML数据转换为TEXT格式
        :param xml_data: XML格式数据
        :return: TEXT格式数据
        """
        parsed_data = xmltodict.parse(xml_data)
        entries = parsed_data["data"]["entry"]
        if not isinstance(entries, list):
            entries = [entries]  # 确保单个数据也能正常处理
        return "\n".join(f"{entry['Year']} {entry['No_Smoothing']} {entry['Lowess']}" for entry in entries)

    def csv_to_text(self, csv_data):
        """
        将CSV数据转换为TEXT格式
        :param csv_data: CSV格式数据
        :return: TEXT格式数据
        """
        lines = csv_data.strip().split("\n")
        # 忽略CSV头部
        return "\n".join(" ".join(line.split(",")) for line in lines[1:])

    async def query(self, format, start_year, end_year, order):
        """
        查询服务端数据并转换为指定的TEXT格式
        :param format: 数据格式（json, xml, csv）
        :param start_year: 查询的起始年份
        :param end_year: 查询的结束年份
        :param order: 排序方式
        :return: TEXT格式数据
        """
        endpoint = f"query/{format}"
        params = {
            "start_year": start_year,
            "end_year": end_year,
            "order": order
        }
        raw_data = await self.fetch_data(endpoint, params)

        # 根据格式转换为TEXT
        if format == "json":
            return self.json_to_text(raw_data)
        elif format == "xml":
            return self.xml_to_text(raw_data)
        elif format == "csv":
            return self.csv_to_text(raw_data)
        else:
            raise ValueError(f"Unsupported format: {format}")


# 测试客户端
async def main():
    # 替换为你服务的实际地址
    client = QueryClient("http://localhost:8000")

    # JSON格式查询并转换
    print("JSON -> TEXT")
    json_text = await client.query("json", 1990, 2000, "asc")
    print(json_text)

    # XML格式查询并转换
    print("\nXML -> TEXT")
    xml_text = await client.query("xml", 2000, 2010, "asc")
    print(xml_text)

    # CSV格式查询并转换
    print("\nCSV -> TEXT")
    csv_text = await client.query("csv", 2010, 2020, "asc")
    print(csv_text)

# 启动客户端
if __name__ == "__main__":
    asyncio.run(main())
