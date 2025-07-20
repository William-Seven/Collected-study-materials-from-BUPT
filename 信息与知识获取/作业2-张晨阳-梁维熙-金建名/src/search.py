import os
import json
import pickle
import numpy as np
import spacy
import nltk
from nltk.corpus import stopwords
from bs4 import BeautifulSoup
from sklearn.metrics.pairwise import cosine_similarity

BASE_DIR = r"E:\WILLIAMZHANG\InfoKnowAcq\Information-Search-Engine\homework2"
nltk.download('stopwords')
STOP_WORDS = set(stopwords.words('english'))
nlp = spacy.load("en_core_web_sm")


def preprocess_query(text):
    text = BeautifulSoup(text, "html.parser").get_text()
    text = text.lower()
    doc = nlp(text)
    tokens = [
        token.lemma_.lower() for token in doc
        if token.is_alpha and token.lemma_.lower() not in STOP_WORDS
    ]
    return tokens


def load_index_data():
    with open(os.path.join(BASE_DIR, 'keys.json'), 'r', encoding='utf-8') as f:
        keywords = json.load(f)
    with open(os.path.join(BASE_DIR, 'doc_vectors.json'), 'r', encoding='utf-8') as f:
        doc_vectors = json.load(f)
    with open(os.path.join(BASE_DIR, 'processed_docs.json'), 'r', encoding='utf-8') as f:
        docs = json.load(f)
    with open(os.path.join(BASE_DIR, 'inverted_index.json'), 'r', encoding='utf-8') as f:
        inverted_index = json.load(f)
    with open(os.path.join(BASE_DIR, 'vectorizer.pkl'), 'rb') as f:
        vectorizer = pickle.load(f)
    return keywords, doc_vectors, docs, inverted_index, vectorizer


def run_search(query, top_n=5):
    keywords, doc_vectors, docs, inverted_index, vectorizer = load_index_data()
    doc_vectors_matrix = np.array(list(doc_vectors.values()))
    doc_ids = list(doc_vectors.keys())

    query_tokens = preprocess_query(query)
    query_text = " ".join(query_tokens)
    raw_query_vector = vectorizer.transform([query_text])
    query_vector = np.zeros(len(keywords))

    vectorizer_vocab = vectorizer.get_feature_names_out()
    vocab_index = {word: i for i, word in enumerate(vectorizer_vocab)}
    for i, word in enumerate(keywords):
        if word in vocab_index:
            query_vector[i] = raw_query_vector[0, vocab_index[word]]

    # ✨ 读取反馈关键词
    feedback_path = os.path.join(BASE_DIR, "feedback_keywords.json")
    lowered_query = query.strip().lower()
    if os.path.exists(feedback_path):
        with open(feedback_path, 'r', encoding='utf-8') as f:
            feedback_data = json.load(f)
        if lowered_query in feedback_data:
            for token, count in feedback_data[lowered_query].get("positive", {}).items():
                if token in keywords:
                    idx = keywords.index(token)
                    query_vector[idx] += 0.3 * count  # 正向增强
            for token, count in feedback_data[lowered_query].get("negative", {}).items():
                if token in keywords:
                    idx = keywords.index(token)
                    query_vector[idx] -= 0.2 * count  # 负向抑制
                    if query_vector[idx] < 0:
                        query_vector[idx] = 0.0  # 防止变成负值

    if np.linalg.norm(query_vector) == 0:
        return {"query": query, "results": []}

    sims = cosine_similarity([query_vector], doc_vectors_matrix)[0]
    ranked = sorted(zip(doc_ids, sims), key=lambda x: -x[1])[:top_n]

    doc_map = {doc["filename"]: doc for doc in docs}
    results = []

    for doc_id, sim in ranked:
        doc = doc_map.get(doc_id)
        if not doc:
            continue

        matched_words = [
            token for token in query_tokens
            if token in inverted_index and doc_id in inverted_index[token]
        ]

        desc = doc['raw_description'].lower()
        snippet = ""
        for word in matched_words:
            idx = desc.find(word)
            if idx != -1:
                snippet = desc[max(0, idx - 60): idx + 80]
                break

        results.append({
            "doc_id": doc_id,
            "title": doc["title"],
            "authors": doc["authors"],
            "pub_date": doc["pub_date"],
            "similarity": round(sim, 4),
            "matched_keywords": matched_words,
            "snippet": snippet or "No matched snippet.",
            "url": doc.get("url", "")
        })

    return {
        "query": query,
        "results": results
    }


def save_feedback(feedback):
    """Save single or multiple user evaluation results."""
    save_path = os.path.join(BASE_DIR, "manual_eval.json")

    # 加载原始文件
    if os.path.exists(save_path):
        with open(save_path, 'r', encoding='utf-8') as f:
            all_evals = json.load(f)
    else:
        all_evals = []

    # 支持单条 results 追加（每次都是 query + results=[1项]）
    if isinstance(feedback, dict) and "query" in feedback and "results" in feedback:
        all_evals.append(feedback)
    else:
        print("Unexpected feedback format, skipping.")

    # 覆盖写入
    with open(save_path, 'w', encoding='utf-8') as f:
        json.dump(all_evals, f, indent=2, ensure_ascii=False)

        # 新增：提取关键词反馈
    keywords, *_ = load_index_data()
    update_feedback_keywords(feedback, keywords)


def update_feedback_keywords(feedback, keywords):
    """从人工评分中提取关键词，并记录为积极 / 消极反馈"""
    from collections import defaultdict

    feedback_path = os.path.join(BASE_DIR, "feedback_keywords.json")
    if os.path.exists(feedback_path):
        with open(feedback_path, 'r', encoding='utf-8') as f:
            feedback_data = json.load(f)
    else:
        feedback_data = {}

    query_text = feedback["query"].strip().lower()
    if query_text not in feedback_data:
        feedback_data[query_text] = {"positive": {}, "negative": {}}

    for result in feedback["results"]:
        label = "positive" if result["relevant"] == 1 else "negative"
        title_tokens = preprocess_query(result["title"])
        for token in title_tokens:
            if token in keywords:
                feedback_data[query_text][label][token] = (
                    feedback_data[query_text][label].get(token, 0) + 1
                )

    with open(feedback_path, 'w', encoding='utf-8') as f:
        json.dump(feedback_data, f, indent=2, ensure_ascii=False)
