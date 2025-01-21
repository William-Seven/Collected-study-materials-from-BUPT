from sanic import Sanic, response
from sanic.response import json, html
import xmltodict

app = Sanic("TemperatureHistory")


# 数据加载函数
def load_data(file_path="E:/WILLIAMZHANG/Python程设/Homeworks/homework2/graph.txt"):
    data = []
    with open(file_path, "r") as file:
        for line in file:
            if line.strip() and not line.startswith("#"):
                parts = line.split()
                year = int(parts[0])
                no_smoothing = float(parts[1])
                lowess = float(parts[2])
                data.append(
                    {"Year": year, "No_Smoothing": no_smoothing, "Lowess": lowess})
    return data


# 加载数据
temperature_data = load_data()


# 数据查询函数
def query_data(start_year, end_year, order=None):
    filtered_data = [
        item for item in temperature_data if start_year <= item["Year"] <= end_year]
    if order == "asc":
        filtered_data.sort(key=lambda x: x["No_Smoothing"])
    elif order == "desc":
        filtered_data.sort(key=lambda x: x["No_Smoothing"], reverse=True)
    return filtered_data


# 主查询页面，带表单
@app.route("/")
async def index(request):
    html_content = """
    <html>
    <body>
        <h2>Temperature Data Query</h2>
        <form action="/query" method="POST">
            <label for="start_year">Start Year:</label>
            <input type="number" id="start_year" name="start_year" value="1880"><br><br>
            <label for="end_year">End Year:</label>
            <input type="number" id="end_year" name="end_year" value="2022"><br><br>
            <label for="order">Order:</label>
            <select id="order" name="order">
                <option value="asc">Ascending</option>
                <option value="desc">Descending</option>
            </select><br><br>
            <label for="format">Format:</label>
            <select id="format" name="format">
                <option value="json">JSON</option>
                <option value="xml">XML</option>
                <option value="csv">CSV</option>
            </select><br><br>
            <input type="submit" value="Submit">
        </form>
    </body>
    </html>
    """
    return html(html_content)


# JSON 路由
@app.route("/query/json", methods=["GET"])
async def query_json(request):
    start_year = int(request.args.get("start_year", 1880))
    end_year = int(request.args.get("end_year", 2022))
    order = request.args.get("order", None)
    data = query_data(start_year, end_year, order)
    return json(data)


# XML 路由
@app.route("/query/xml", methods=["GET"])
async def query_xml(request):
    start_year = int(request.args.get("start_year", 1880))
    end_year = int(request.args.get("end_year", 2022))
    order = request.args.get("order", None)
    data = query_data(start_year, end_year, order)
    xml_data = xmltodict.unparse({"data": {"entry": data}})
    return response.text(xml_data, content_type="application/xml")


# CSV 路由
@app.route("/query/csv", methods=["GET"])
async def query_csv(request):
    start_year = int(request.args.get("start_year", 1880))
    end_year = int(request.args.get("end_year", 2022))
    order = request.args.get("order", None)
    data = query_data(start_year, end_year, order)
    csv_data = "Year,No_Smoothing,Lowess\n"
    csv_data += "\n".join([f"{item['Year']},{item['No_Smoothing']
                                             },{item['Lowess']}" for item in data])
    return response.text(csv_data, content_type="text/csv")


# POST 路由（保留原始功能）
@app.route("/query", methods=["POST"])
async def query(request):
    start_year = int(request.form.get("start_year", 1880))
    end_year = int(request.form.get("end_year", 2022))
    order = request.form.get("order", None)
    data_format = request.form.get("format", "json")

    data = query_data(start_year, end_year, order)

    if data_format == "json":
        return json(data)
    elif data_format == "xml":
        xml_data = xmltodict.unparse({"data": {"entry": data}})
        return response.text(xml_data, content_type="application/xml")
    elif data_format == "csv":
        csv_data = "Year,No_Smoothing,Lowess\n"
        csv_data += "\n".join([f"{item['Year']},{item['No_Smoothing']
                                                 },{item['Lowess']}" for item in data])
        return response.text(csv_data, content_type="text/csv")
    else:
        return response.text("Unsupported format", status=400)


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8000)
