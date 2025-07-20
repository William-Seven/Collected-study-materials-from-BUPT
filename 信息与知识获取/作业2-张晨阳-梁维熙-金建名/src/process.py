import os
import re
import json
from bs4 import BeautifulSoup
import spacy
import nltk
from nltk.corpus import stopwords

nltk.download('stopwords')
STOP_WORDS = set(stopwords.words('english'))

# 添加自定义停用词
CUSTOM_STOP_WORDS = {
    'using', 'use', 'used', 'based', 'of', 'result', 'results', 'in',
    'on', 'to', 'analysis', 'paper', 'also', 'shown', 'different', 'new',
    'and', 'the', 'example', 'provide', 'present', 'show', 'propose',
    'may', 'within', 'however', 'therefore', 'thus', 'among', 'etc', 'et', 'al',
    'including', 'respectively', 'could', 'would', 'one', 'two', 'three'
}


# 加载 spaCy 英文模型
nlp = spacy.load("en_core_web_sm")

# 输入与输出路径
# DATA_DIR = r"..\zenodo_papers"
DATA_DIR = os.path.join(os.path.dirname(__file__), '..', 'zenodo_papers')
OUTPUT_PATH = os.path.join(os.path.dirname(
    __file__), '..', 'processed_docs.json')


def clean_html(raw_html):
    """使用 BeautifulSoup 清洗 HTML"""
    soup = BeautifulSoup(raw_html, "html.parser")
    return soup.get_text(separator=" ", strip=True)


def preprocess_text(text):
    """清洗、lemmatize、去停用词、转小写"""
    text = clean_html(text)
    text = text.lower()
    doc = nlp(text)
    tokens = [
        token.lemma_.lower() for token in doc
        if token.is_alpha and token.lemma_.lower() not in STOP_WORDS and token.lemma_.lower() not in CUSTOM_STOP_WORDS
    ]
    return " ".join(tokens)


def process_documents():
    all_docs = []
    for fname in os.listdir(DATA_DIR):
        if not fname.endswith(".txt"):
            continue

        with open(os.path.join(DATA_DIR, fname), 'r', encoding='utf-8') as f:
            content = f.read()

        # 使用正则分段提取字段
        title_match = re.search(r"Title:\s*(.*?)\n", content)
        author_match = re.search(r"Authors:\s*(.*?)\n", content)
        keyword_match = re.search(r"Keywords:\s*(.*?)\n", content)
        date_match = re.search(r"Publication date:\s*(.*?)\n", content)
        description_match = re.search(
            r"Description:\s*(.+)", content, re.DOTALL)

        title = title_match.group(1).strip() if title_match else ""
        authors = author_match.group(1).strip() if author_match else ""
        keywords = keyword_match.group(1).strip() if keyword_match else ""
        pub_date = date_match.group(1).strip() if date_match else ""
        raw_description = description_match.group(
            1).strip() if description_match else ""

        # 标题不能缺失，否则跳过
        if not title or title.strip().upper() == "N/A":
            continue

        # 其他字段替代为默认值
        authors = "" if authors.strip().upper() == "N/A" else authors
        keywords = "" if keywords.strip().upper() == "N/A" else keywords
        pub_date = "" if pub_date.strip().upper() == "N/A" else pub_date

        # 没有 description（摘要）或为 N/A 时，也跳过
        if not raw_description or raw_description.strip().upper() == "N/A":
            continue

        clean_title = preprocess_text(title)
        clean_desc = preprocess_text(raw_description)

        all_docs.append({
            "filename": fname,
            "title": title,
            "clean_title": clean_title,
            "authors": authors,
            "keywords": keywords,
            "pub_date": pub_date,
            "raw_description": raw_description,
            "clean_description": clean_desc,
        })

    # 存为 JSON 格式，便于后续倒排索引构建
    with open(OUTPUT_PATH, "w", encoding='utf-8') as out_file:
        json.dump(all_docs, out_file, indent=2, ensure_ascii=False)
    print(f"已处理 {len(all_docs)} 个文档，输出保存至：{OUTPUT_PATH}")


if __name__ == "__main__":
    process_documents()
