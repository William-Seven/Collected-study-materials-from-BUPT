import os
import json
import pickle
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from collections import defaultdict

# 修改为相对路径
INPUT_JSON = os.path.join(os.path.dirname(__file__), '..', 'processed_docs.json')
OUTPUT_DIR = os.path.join(os.path.dirname(__file__), '..')
TOP_K = 800  # 关键词数量


def load_documents():
    with open(INPUT_JSON, 'r', encoding='utf-8') as f:
        docs = json.load(f)
    return docs


def build_tfidf(docs):
    def apply_weighted_text(doc, w_title=8.0, w_keywords=4.0, w_description=1.0):
        def repeat_text(text, weight):
            repeat_count = int(weight)
            partial = int((weight - repeat_count) * 10)
            return (" ".join([text] * repeat_count)) + (" " + text) * (partial // 10)

        title_text = repeat_text(doc['clean_title'], w_title)
        keyword_text = repeat_text(doc['keywords'], w_keywords)
        desc_text = repeat_text(doc['clean_description'], w_description)
        return f"{title_text} {keyword_text} {desc_text}"

    corpus = [apply_weighted_text(doc) for doc in docs]
    doc_ids = [doc["filename"] for doc in docs]

    vectorizer = TfidfVectorizer(max_df=0.9, min_df=2)
    tfidf_matrix = vectorizer.fit_transform(corpus)
    feature_names = vectorizer.get_feature_names_out()

    tfidf_sums = np.asarray(tfidf_matrix.sum(axis=0)).flatten()
    top_indices = tfidf_sums.argsort()[::-1][:TOP_K]
    top_keywords = [feature_names[i] for i in top_indices]

    return tfidf_matrix, doc_ids, top_keywords, vectorizer


def build_inverted_index(tfidf_matrix, doc_ids, top_keywords, vectorizer):
    inverted_index = defaultdict(dict)
    keyword_set = set(top_keywords)
    feature_names = vectorizer.get_feature_names_out()

    for doc_idx, doc_id in enumerate(doc_ids):
        row = tfidf_matrix[doc_idx].tocoo()
        for i, j, v in zip(row.row, row.col, row.data):
            word = feature_names[j]
            if word in keyword_set:
                inverted_index[word][doc_id] = round(v, 6)
    return inverted_index


def build_doc_vectors(tfidf_matrix, doc_ids, top_keywords, vectorizer):
    feature_names = vectorizer.get_feature_names_out()
    vocab_index = {word: idx for idx, word in enumerate(feature_names)}
    top_indices = [vocab_index[word]
                   for word in top_keywords if word in vocab_index]
    top_index_to_pos = {idx: pos for pos, idx in enumerate(top_indices)}

    doc_vectors = {}
    for doc_idx, doc_id in enumerate(doc_ids):
        row = tfidf_matrix[doc_idx]
        vector = np.zeros(len(top_keywords))
        for j in row.indices:
            if j in top_index_to_pos:
                vector[top_index_to_pos[j]] = round(row[0, j], 6)
        doc_vectors[doc_id] = vector.tolist()
    return doc_vectors


def save_json(obj, path):
    # 确保目录存在
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(obj, f, indent=2, ensure_ascii=False)


def main():
    docs = load_documents()
    print(f"Load {len(docs)} docs")

    tfidf_matrix, doc_ids, top_keywords, vectorizer = build_tfidf(docs)
    save_json(top_keywords, os.path.join(OUTPUT_DIR, "keys.json"))
    with open(os.path.join(OUTPUT_DIR, "vectorizer.pkl"), "wb") as f:
        pickle.dump(vectorizer, f)

    print("Build inverted index...")
    inverted_index = build_inverted_index(
        tfidf_matrix, doc_ids, top_keywords, vectorizer)
    save_json(inverted_index, os.path.join(OUTPUT_DIR, "inverted_index.json"))

    print("Build doc vectors...")
    doc_vectors = build_doc_vectors(
        tfidf_matrix.tocsr(), doc_ids, top_keywords, vectorizer)
    save_json(doc_vectors, os.path.join(OUTPUT_DIR, "doc_vectors.json"))

    print("Finished!")


if __name__ == "__main__":
    main()