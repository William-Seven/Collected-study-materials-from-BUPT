from flask import Flask, request, render_template, jsonify
from src.search import run_search, save_feedback
import pytesseract
from PIL import Image
import tempfile

app = Flask(__name__)

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search", methods=["POST"])
def search():
    query = request.form.get("query", "")
    topn = int(request.form.get("topn", 5))
    image_file = request.files.get("image", None)

    # 提取图像中的文本并追加到 query
    if image_file:
        try:
            with tempfile.NamedTemporaryFile(delete=False, suffix=".png") as temp_file:
                image_file.save(temp_file.name)
                ocr_text = pytesseract.image_to_string(
                    Image.open(temp_file.name))
                print(f"OCR extracted text: {ocr_text.strip()}")
                query += " " + ocr_text
        except Exception as e:
            print(f"Error processing image: {e}")

    if not query.strip():
        return jsonify({"error": "Empty query"}), 400

    results = run_search(query, top_n=topn)
    return jsonify(results)


@app.route("/feedback", methods=["POST"])
def feedback():
    data = request.get_json()

    if not data or "query" not in data or "results" not in data:
        return jsonify({"error": "Invalid feedback format"}), 400

    save_feedback(data)
    return jsonify({"status": "ok"})


if __name__ == "__main__":
    app.run(debug=True)
