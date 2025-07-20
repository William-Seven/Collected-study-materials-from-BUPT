import re
import json
import os
from flask import Flask, request, jsonify
from settings import FEEDBACK_FILE, OUTPUT_JSON_FILE

app = Flask(__name__)


def generalize_key(uuid, field):
    return "uuid:" + uuid + "field" + field


def save_feedback(uuid, field, correct):
    """
    保存用户对提取结果的反馈。
    """
    entry = {"correct": correct}
    key = generalize_key(uuid, field)
    feedback_data = []
    if os.path.exists(FEEDBACK_FILE):
        try:
            with open(FEEDBACK_FILE, "r", encoding="utf-8") as feedback_file:
                feedback_data = json.load(feedback_file)
        except json.JSONDecodeError:
            # 如果文件为空或损坏，则重新初始化
            feedback_data = {}
    feedback_data[key] = entry
    with open(FEEDBACK_FILE, "w", encoding="utf-8") as feedback_file:
        json.dump(feedback_data, feedback_file, indent=2, ensure_ascii=False)


def was_incorrect(key):
    """
    检查某个字段值之前是否曾被标记为不正确。
    """
    if not os.path.exists(FEEDBACK_FILE):
        return False
    try:
        with open(FEEDBACK_FILE, "r", encoding="utf-8") as f:
            feedback_data = json.load(f)
    except json.JSONDecodeError:
        return False  # 文件损坏或为空
    # for entry in feedback_data:
    #     if entry["field"] == field and entry["value"] == value and not entry["correct"]:
    if key not in feedback_data:
        return True
    if feedback_data[key]["correct"] is True:
        return True
    return False


def extract_info_regex(text):
    """
    使用正则表达式从文本中提取信息。
    """
    info = {}

    match = re.search(r"Title:\s*(.+)", text)
    if match:
        info["Title"] = match.group(1).strip()
    else:
        info["Title"] = None  # 明确表示未找到

    match = re.search(r"Authors:\s*(.+)", text)
    if match:
        info["Authors"] = [a.strip() for a in match.group(1).split(",")]
    else:
        info["Authors"] = []

    match = re.search(r"Keywords:\s*(.+)", text)
    if match:
        info["Keywords"] = [k.strip() for k in match.group(1).split(",")]
    else:
        info["Keywords"] = []

    match = re.search(r"Publication date:\s*([\d-]+)", text)
    if match:
        info["Publication Date"] = match.group(1)
    else:
        info["Publication Date"] = None

    description_match = re.search(r"Description:\s*(.*?)(?:\Z)", text, re.DOTALL)
    if description_match:
        info["Description"] = description_match.group(1).strip()
    else:
        info["Description"] = ""

    url_pattern = re.compile(r'https?://[^\s"<]+|www\.[^\s"<]+')
    urls_found = url_pattern.findall(text)
    info["URLs"] = list(set(urls_found))

    doi_pattern = re.compile(r'10\.\d{4,9}/[^\s"<]+')
    dois_found = doi_pattern.findall(text)
    info["DOIs"] = list(set(dois_found))

    info["GitHub Link"] = None
    for url in info["URLs"]:
        if "github.com" in url:
            info["GitHub Link"] = url
            break

    info["DOI"] = None
    for doi in info["DOIs"]:
        if "doi.org" in doi:
            info["DOI"] = doi
            break

    # 移除 URLs 和 DOIs 列表，因为我们已经提取了 GitHub Link 和 DOI 字段
    if "URLs" in info and "GitHub Link" in info and info["GitHub Link"]:
        info["URLs"] = [url for url in info["URLs"] if url != info["GitHub Link"]]
    if "DOIs" in info and "DOI" in info and info["DOI"]:
        info["DOIs"] = [doi for doi in info["DOIs"] if doi != info["DOI"]]

    return info


# --- API 路由定义 ---

@app.route('/extract', methods=['POST'])
def extract_data():
    """
    API 接口用于从文本中提取信息。
    @request:
        - Content-Type: application/json
        - Body: {"text": "文本内容"}
    @response:
        - 200 OK: {"status": "success", "data": {"Title": "标题", "Authors": ["作者1", "作者2"], ...}, "uuid": uuid}
        - 400 Bad Request: {"error": "请求必须是 JSON 格式"}
        - 400 Bad Request: {"error": "请求体中缺少 'text' 字段"}
        - 500 Internal Server Error: {"error": "服务器内部错误: 错误信息"}
    """
    if not request.is_json:
        return jsonify({"error": "请求必须是 JSON 格式"}), 400

    data = request.get_json()
    raw_text = data.get('text')

    if not raw_text:
        return jsonify({"error": "请求体中缺少 'text' 字段"}), 400

    try:
        extracted_info = extract_info_regex(raw_text)

        # 将提取结果保存到 OUTPUT_JSON_FILE
        all_extracted_data = {}
        if os.path.exists(OUTPUT_JSON_FILE):
            try:
                with open(OUTPUT_JSON_FILE, "r", encoding="utf-8") as f:
                    all_extracted_data = json.load(f)
            except json.JSONDecodeError:
                all_extracted_data = {}  # 文件损坏或为空

        # 使用一个唯一的ID或时间戳作为键，避免覆盖
        import uuid
        entry_id = str(uuid.uuid4())
        all_extracted_data[entry_id] = extracted_info

        with open(OUTPUT_JSON_FILE, "w", encoding="utf-8") as f:
            json.dump(all_extracted_data, f, indent=2, ensure_ascii=False)

        return jsonify({"status": "success", "data": extracted_info, "uuid": entry_id}), 200
    except Exception as e:
        app.logger.error(f"提取过程中发生错误: {e}", exc_info=True)
        return jsonify({"error": f"服务器内部错误: {str(e)}"}), 500


@app.route('/feedback', methods=['POST'])
def submit_feedback():
    """
    API 接口用于接收用户对提取结果的反馈。
    @request:
        - Content-Type: application/json
        - Body: {"uuid": uuid, "field": "字段名", "correct": true/false}
    @response:
        - 200 OK: {"status": "success", "message": "反馈已保存"}
        - 400 Bad Request: {"error": "请求必须是 JSON 格式"}
        - 400 Bad Request: {"error": "请求体中缺少 'field', 'value' 或 'correct' 字段"}
        - 400 Bad Request: {"error": "'correct' 字段必须是布尔值 (true/false)"}
        - 500 Internal Server Error: {"error": "服务器内部错误: 错误信息"}
    """
    if not request.is_json:
        return jsonify({"error": "请求必须是 JSON 格式"}), 400

    data = request.get_json()
    uuid = data.get('uuid')
    field = data.get('field')
    correct = data.get('correct')

    if field is None or correct is None:
        return jsonify({"error": "请求体中缺少 'field' 或 'correct' 字段"}), 400

    if not isinstance(correct, bool):
        return jsonify({"error": "'correct' 字段必须是布尔值 (true/false)"}), 400

    try:
        save_feedback(uuid, field, correct)  # 确保value是字符串以便保存
        return jsonify({"status": "success", "message": "反馈已保存"}), 200
    except Exception as e:
        app.logger.error(f"保存反馈时发生错误: {e}", exc_info=True)
        return jsonify({"error": f"服务器内部错误: {str(e)}"}), 500


@app.route('/feedback/check_incorrect', methods=['POST'])
def check_feedback_incorrect():
    """
    API 接口用于检查某个字段值是否曾被标记为不正确。
    @request:
        - Content-Type: application/json
        - Body: {"uuid": uuid, "field": "字段名"}
    @response:
        - 200 OK: {"status": "success", "was_incorrect": true/false}
        - 400 Bad Request: {"error": "请求必须是 JSON 格式"}
        - 400 Bad Request: {"error": "请求体中缺少 'field' 或 'value' 字段"}
        - 500 Internal Server Error: {"error": "服务器内部错误: 错误信息"}
    """
    if not request.is_json:
        return jsonify({"error": "请求必须是 JSON 格式"}), 400

    data = request.get_json()
    uuid = data.get('uuid')
    field = data.get('field')

    if field is None:
        return jsonify({"error": "请求体中缺少 'field'"}), 400

    try:
        key = generalize_key(uuid, field)
        incorrect = was_incorrect(key)
        return jsonify({"status": "success", "was_incorrect": incorrect}), 200
    except Exception as e:
        app.logger.error(f"检查反馈时发生错误: {e}", exc_info=True)
        return jsonify({"error": f"服务器内部错误: {str(e)}"}), 500


@app.route('/feedback/history', methods=['POST'])
def get_history():
    """
    API接口用于查看程序的文本提取记录与相对应的人工评价
    @request
        - Content-Type: application/json
        - Body: {"Num": num}
    @response:
        - 200 OK: {"status": "success", "history": [uuid1: data, uuid2: data, ...], "correct_history": [uuid1: data, uuid2: data, ...]}
        - 400 Bad Request: {"error": "请求体中缺少 'Num' 字段"}
        - 400 Bad Request: {"error": "'Num' 字段必须是正整数"}
        - 500 Internal Server Error: {"error": "服务器内部错误: 错误信息"}
    """
    try:
        # 检查请求是否为 JSON 格式
        if not request.is_json:
            return jsonify({"error": "请求必须是 JSON 格式"}), 400

        data = request.get_json()
        num = data.get('Num')

        # 检查 Num 是否存在且为正整数
        if num is None:
            return jsonify({"error": "请求体中缺少 'Num' 字段"}), 400
        if not isinstance(num, int) or num <= 0:
            return jsonify({"error": "'Num' 字段必须是正整数"}), 400

        all_extracted_data = {}
        if os.path.exists(OUTPUT_JSON_FILE):
            with open(OUTPUT_JSON_FILE, "r", encoding="utf-8") as f:
                all_extracted_data = json.load(f)

        feedback_data = {}
        if os.path.exists(FEEDBACK_FILE):
            try:
                with open(FEEDBACK_FILE, "r", encoding="utf-8") as feedback_file:
                    feedback_data = json.load(feedback_file)
            except json.JSONDecodeError:
                feedback_data = {}

        # 获取最新的 num 条记录
        latest_records = dict(list(all_extracted_data.items())[-num:])
        correct_history = {}  # 初始化 correct_history 为一个空字典

        for uuid, data in latest_records.items():
            total_fields = 0
            correct_fields = 0
            correct_history[uuid] = {}  # 初始化 correct_history[uuid] 为一个空字典
            for field in data.keys():
                key = generalize_key(uuid, field)
                if key in feedback_data:
                    total_fields += 1
                    correct_history[uuid][field] = feedback_data[key]["correct"]
                    if feedback_data[key]["correct"]:
                        correct_fields += 1
                else:
                    correct_history[uuid][field] = None  # 如果没有反馈，则标记为 None
            if total_fields > 0:
                accuracy = correct_fields / total_fields
            else:
                accuracy = None
            correct_history[uuid]["accuracy"] = accuracy

        return jsonify({"status": "success", "history": latest_records, "correct_history": correct_history}), 200
    except Exception as e:
        app.logger.error(f"获取历史记录时发生错误: {e}", exc_info=True)
        return jsonify({"error": f"服务器内部错误: {str(e)}"}), 500


@app.route('/')
def home():
    """
    根路径，提供简单的API说明。
    @response:
        - 200 OK: {"message": "欢迎使用信息提取API！", "endpoints": {...}}
    """
    return jsonify({
        "message": "欢迎使用信息提取API！",
        "endpoints": {
            "/extract (POST)": "从文本中提取信息。需要 'text' 字段。",
            "/feedback (POST)": "提交提取结果的反馈。需要 'field', 'value', 'correct' 字段。",
            "/feedback/check_incorrect (POST)": "检查某个字段值是否曾被标记为不正确。需要 'field', 'value' 字段。",
            "/feedback/history (POST)": "获取提取记录，并获取相对应的人工评价结果"
        }
    })


if __name__ == '__main__':
    # 在生产环境中，推荐使用 Gunicorn 或 uWSGI 等 WSGI 服务器来运行 Flask 应用
    # 例如：gunicorn -w 4 app:app
    app.run(debug=True, port=5000)  # 关闭调试模式
