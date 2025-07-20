# import sys
# import requests
# import json
# from PyQt5.QtWidgets import (
#     QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QTextEdit, QLabel,
#     QLineEdit, QComboBox, QFormLayout, QTableWidget, QTableWidgetItem, QHeaderView,
#     QMessageBox, QDialog, QCheckBox, QHBoxLayout, QScrollArea, QTextBrowser, QGridLayout
# )
# from PyQt5.QtCore import Qt


# class InfoExtractorApp(QMainWindow):
#     def __init__(self):
#         super().__init__()
#         self.setWindowTitle("信息提取工具")
#         self.setGeometry(100, 100, 800, 600)

#         self.init_ui()

#     def init_ui(self):
#         self.central_widget = QWidget()
#         self.setCentralWidget(self.central_widget)
#         self.layout = QVBoxLayout()
#         self.central_widget.setLayout(self.layout)

#         # 文本提取部分
#         self.text_edit = QTextEdit()
#         self.text_edit.setPlaceholderText("请输入文本...")
#         self.layout.addWidget(self.text_edit)

#         self.extract_button = QPushButton("提取信息")
#         self.extract_button.clicked.connect(self.extract_info)
#         self.layout.addWidget(self.extract_button)

#         # 查看反馈历史按钮
#         self.history_button = QPushButton("查看反馈历史")
#         self.history_button.clicked.connect(self.show_history)
#         self.layout.addWidget(self.history_button)

#     def extract_info(self):
#         text = self.text_edit.toPlainText()
#         if not text:
#             QMessageBox.warning(self, "警告", "请输入文本！")
#             return

#         try:
#             response = requests.post("http://127.0.0.1:5000/extract", json={"text": text})
#             response.raise_for_status()
#             data = response.json()
#             if data["status"] == "success":
#                 extracted_info = data["data"]
#                 self.show_extracted_info(extracted_info, data["uuid"])
#             else:
#                 QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
#         except requests.RequestException as e:
#             QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

#     def show_extracted_info(self, extracted_info, uuid):
#         # 创建一个新的对话框来显示提取结果
#         self.extracted_info_dialog = QDialog(self)
#         self.extracted_info_dialog.setWindowTitle("提取结果")
#         self.extracted_info_dialog.setGeometry(100, 100, 1200, 800)  # 调整对话框大小

#         # 创建滚动区域以容纳所有字段
#         scroll_area = QScrollArea()
#         scroll_area.setWidgetResizable(True)
#         self.extracted_info_dialog.layout = QVBoxLayout()
#         self.extracted_info_dialog.setLayout(self.extracted_info_dialog.layout)

#         # 创建一个 QWidget 作为滚动区域的内容
#         content_widget = QWidget()
#         content_layout = QGridLayout()  # 使用网格布局
#         content_widget.setLayout(content_layout)

#         # 遍历提取结果，为每个字段创建一个行布局
#         self.checkboxes = {}  # 用于存储每个字段的复选框
#         row = 0
#         for field, value in extracted_info.items():
#             field_label = QLabel(f"{field}:")
#             content_layout.addWidget(field_label, row, 0)

#             # 将值转换为字符串（如果值是列表，则用逗号分隔；如果值是 None，则显示 "None"）
#             if isinstance(value, list):
#                 truncated_value = ", ".join(value)
#             elif value is None:
#                 truncated_value = "None"
#             else:
#                 truncated_value = value

#             # 限制显示的文本长度，并添加“查看详细”按钮
#             if isinstance(truncated_value, str) and len(truncated_value) > 50:
#                 truncated_value = truncated_value[:50] + "..."

#             value_label = QLabel(truncated_value)
#             content_layout.addWidget(value_label, row, 1)

#             # 添加“查看详细”按钮
#             detail_button = QPushButton("查看详细")
#             detail_button.clicked.connect(lambda checked, v=value: self.show_detail(v))
#             content_layout.addWidget(detail_button, row, 2)

#             # 检查该字段是否曾被标记为不正确
#             is_incorrect = self.check_field_incorrect(uuid, field)
#             if is_incorrect:
#                 error_label = QLabel("曾被标记为错误,注意鉴别")
#                 error_label.setStyleSheet("color: red; font-weight: bold;")
#                 content_layout.addWidget(error_label, row, 4)

#             checkbox = QCheckBox("标记为不正确")
#             checkbox.setChecked(is_incorrect)
#             self.checkboxes[field] = checkbox
#             content_layout.addWidget(checkbox, row, 3)

#             row += 1

#         # 将内容添加到滚动区域
#         scroll_area.setWidget(content_widget)
#         self.extracted_info_dialog.layout.addWidget(scroll_area)

#         # 添加一个按钮来提交反馈
#         submit_button = QPushButton("提交所有反馈")
#         submit_button.clicked.connect(lambda: self.submit_extracted_feedback(uuid))
#         self.extracted_info_dialog.layout.addWidget(submit_button)

#         self.extracted_info_dialog.exec_()

#     def show_detail(self, value):
#         # 显示详细内容
#         detail_dialog = QDialog(self)
#         detail_dialog.setWindowTitle("详细内容")
#         detail_dialog.setGeometry(200, 200, 600, 400)

#         layout = QVBoxLayout()
#         detail_dialog.setLayout(layout)

#         # 将值转换为字符串（如果值是列表，则用逗号分隔；如果值是 None，则显示 "None"）
#         if isinstance(value, list):
#             value = ", ".join(value)
#         elif value is None:
#             value = "None"

#         text_browser = QTextBrowser()
#         text_browser.setText(value)
#         layout.addWidget(text_browser)

#         detail_dialog.exec_()

#     def check_field_incorrect(self, uuid, field):
#         try:
#             response = requests.post(
#                 "http://127.0.0.1:5000/feedback/check_incorrect",
#                 json={"uuid": uuid, "field": field}
#             )
#             response.raise_for_status()
#             data = response.json()
#             if data["status"] == "success":
#                 return data["was_incorrect"]
#             else:
#                 QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
#         except requests.RequestException as e:
#             QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")
#         return False

#     def submit_extracted_feedback(self, uuid):
#         feedback_data = {}
#         for field, checkbox in self.checkboxes.items():
#             feedback_data[field] = checkbox.isChecked()

#         try:
#             for field, is_incorrect in feedback_data.items():
#                 response = requests.post(
#                     "http://127.0.0.1:5000/feedback",
#                     json={"uuid": uuid, "field": field, "correct": not is_incorrect}
#                 )
#                 response.raise_for_status()
#                 data = response.json()
#                 if data["status"] != "success":
#                     QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
#             QMessageBox.information(self, "成功", "反馈已保存！")
#             self.extracted_info_dialog.close()
#         except requests.RequestException as e:
#             QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

#     def show_history(self):
#         # 创建一个新的对话框来显示历史记录
#         self.history_dialog = QDialog(self)
#         self.history_dialog.setWindowTitle("历史记录")
#         self.history_dialog.setGeometry(100, 100, 800, 600)

#         # 创建表格来显示历史记录
#         self.history_table = QTableWidget()
#         self.history_table.setRowCount(0)
#         self.history_table.setColumnCount(3)
#         self.history_table.setHorizontalHeaderLabels(["UUID", "字段名", "准确率"])
#         self.history_table.horizontalHeader().setStretchLastSection(True)
#         self.history_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

#         # 加载历史记录
#         self.load_history()

#         # 创建布局并添加表格
#         layout = QVBoxLayout()
#         layout.addWidget(self.history_table)

#         # 添加关闭按钮
#         close_button = QPushButton("关闭")
#         close_button.clicked.connect(self.history_dialog.close)
#         layout.addWidget(close_button)

#         self.history_dialog.setLayout(layout)
#         self.history_dialog.exec_()

#     def load_history(self):
#         try:
#             response = requests.post("http://127.0.0.1:5000/feedback/history", json={"Num": 10})
#             response.raise_for_status()
#             data = response.json()
#             if data["status"] == "success":
#                 self.update_history_table(data["history"], data["correct_history"])
#             else:
#                 QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
#         except requests.RequestException as e:
#             QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

#     def update_history_table(self, history, correct_history):
#         self.history_table.setRowCount(0)
#         for uuid, data in history.items():
#             row_position = self.history_table.rowCount()
#             self.history_table.insertRow(row_position)
#             self.history_table.setItem(row_position, 0, QTableWidgetItem(uuid))
#             for field, correct in correct_history[uuid].items():
#                 self.history_table.setItem(row_position, 1, QTableWidgetItem(field))
#                 self.history_table.setItem(row_position, 2, QTableWidgetItem(str(correct)))


# if __name__ == "__main__":
#     app = QApplication(sys.argv)
#     window = InfoExtractorApp()
#     window.show()
#     sys.exit(app.exec_())

import sys
import requests
import json
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QTextEdit, QLabel,
    QLineEdit, QComboBox, QFormLayout, QTableWidget, QTableWidgetItem, QHeaderView,
    QMessageBox, QDialog, QCheckBox, QHBoxLayout, QScrollArea, QTextBrowser, QGridLayout
)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont, QColor


class InfoExtractorApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("信息提取工具")
        self.setGeometry(100, 100, 800, 600)
        self.init_ui()

    def init_ui(self):
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QVBoxLayout()
        self.central_widget.setLayout(self.layout)

        # 设置字体和样式
        font = QFont("Arial", 12)
        self.setFont(font)
        self.setStyleSheet("""
            QMainWindow {
                background-color: #f0f0f0;
            }
            QPushButton {
                background-color: #0078d7;
                color: white;
                border-radius: 5px;
                padding: 5px 10px;
            }
            QPushButton:hover {
                background-color: #005ea6;
            }
            QTextEdit, QLineEdit, QComboBox {
                padding: 5px;
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QLabel {
                color: #333;
            }
            QTableWidget {
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QHeaderView::section {
                background-color: #e0e0e0;
            }
        """)

        # 文本输入区域
        self.text_edit = QTextEdit()
        self.text_edit.setPlaceholderText("请输入文本...")
        self.layout.addWidget(self.text_edit)

        # 提取信息按钮
        self.extract_button = QPushButton("提取信息")
        self.extract_button.clicked.connect(self.extract_info)
        self.layout.addWidget(self.extract_button)

        # 查看反馈历史按钮
        self.history_button = QPushButton("查看反馈历史")
        self.history_button.clicked.connect(self.show_history)
        self.layout.addWidget(self.history_button)

    def extract_info(self):
        text = self.text_edit.toPlainText()
        if not text:
            QMessageBox.warning(self, "警告", "请输入文本！")
            return

        try:
            response = requests.post("http://127.0.0.1:5000/extract", json={"text": text})
            response.raise_for_status()
            data = response.json()
            if data["status"] == "success":
                extracted_info = data["data"]
                self.show_extracted_info(extracted_info, data["uuid"])
            else:
                QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
        except requests.RequestException as e:
            QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

    def show_extracted_info(self, extracted_info, uuid):
        self.extracted_info_dialog = QDialog(self)
        self.extracted_info_dialog.setWindowTitle("提取结果")
        self.extracted_info_dialog.setGeometry(100, 100, 1200, 800)

        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        self.extracted_info_dialog.layout = QVBoxLayout()
        self.extracted_info_dialog.setLayout(self.extracted_info_dialog.layout)

        content_widget = QWidget()
        content_layout = QGridLayout()
        content_widget.setLayout(content_layout)

        self.checkboxes = {}
        row = 0
        for field, value in extracted_info.items():
            field_label = QLabel(f"{field}:")
            field_label.setStyleSheet("font-weight: bold;")
            content_layout.addWidget(field_label, row, 0)

            if isinstance(value, list):
                truncated_value = ", ".join(value)
            elif value is None:
                truncated_value = "None"
            else:
                truncated_value = value

            if isinstance(truncated_value, str) and len(truncated_value) > 50:
                truncated_value = truncated_value[:50] + "..."

            value_label = QLabel(truncated_value)
            content_layout.addWidget(value_label, row, 1)

            detail_button = QPushButton("查看详细")
            detail_button.clicked.connect(lambda checked, v=value: self.show_detail(v))
            content_layout.addWidget(detail_button, row, 2)

            is_incorrect = self.check_field_incorrect(uuid, field)
            if is_incorrect:
                error_label = QLabel("曾被标记为错误, 注意鉴别")
                error_label.setStyleSheet("color: red; font-weight: bold;")
                content_layout.addWidget(error_label, row, 4)

            checkbox = QCheckBox("标记为不正确")
            checkbox.setChecked(is_incorrect)
            self.checkboxes[field] = checkbox
            content_layout.addWidget(checkbox, row, 3)

            row += 1

        scroll_area.setWidget(content_widget)
        self.extracted_info_dialog.layout.addWidget(scroll_area)

        submit_button = QPushButton("提交所有反馈")
        submit_button.clicked.connect(lambda: self.submit_extracted_feedback(uuid))
        self.extracted_info_dialog.layout.addWidget(submit_button)

        self.extracted_info_dialog.setStyleSheet("""
            QDialog {
                background-color: #ffffff;
            }
            QPushButton {
                background-color: #0078d7;
                color: white;
                border-radius: 5px;
                padding: 5px 10px;
            }
            QPushButton:hover {
                background-color: #005ea6;
            }
            QLabel {
                color: #333;
            }
        """)
        self.extracted_info_dialog.exec_()

    def show_detail(self, value):
        detail_dialog = QDialog(self)
        detail_dialog.setWindowTitle("详细内容")
        detail_dialog.setGeometry(200, 200, 600, 400)

        layout = QVBoxLayout()
        detail_dialog.setLayout(layout)

        if isinstance(value, list):
            value = ", ".join(value)
        elif value is None:
            value = "None"

        text_browser = QTextBrowser()
        text_browser.setText(value)
        layout.addWidget(text_browser)

        detail_dialog.setStyleSheet("""
            QDialog {
                background-color: #ffffff;
            }
            QTextBrowser {
                border: 1px solid #ccc;
                border-radius: 5px;
                padding: 5px;
            }
        """)
        detail_dialog.exec_()

    def check_field_incorrect(self, uuid, field):
        try:
            response = requests.post(
                "http://127.0.0.1:5000/feedback/check_incorrect",
                json={"uuid": uuid, "field": field}
            )
            response.raise_for_status()
            data = response.json()
            if data["status"] == "success":
                return data["was_incorrect"]
            else:
                QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
        except requests.RequestException as e:
            QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")
        return False

    def submit_extracted_feedback(self, uuid):
        feedback_data = {field: checkbox.isChecked() for field, checkbox in self.checkboxes.items()}

        try:
            for field, is_incorrect in feedback_data.items():
                response = requests.post(
                    "http://127.0.0.1:5000/feedback",
                    json={"uuid": uuid, "field": field, "correct": not is_incorrect}
                )
                response.raise_for_status()
                data = response.json()
                if data["status"] != "success":
                    QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
            QMessageBox.information(self, "成功", "反馈已保存！")
            self.extracted_info_dialog.close()
        except requests.RequestException as e:
            QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

    def show_history(self):
        self.history_dialog = QDialog(self)
        self.history_dialog.setWindowTitle("历史记录")
        self.history_dialog.setGeometry(100, 100, 800, 600)

        self.history_table = QTableWidget()
        self.history_table.setRowCount(0)
        self.history_table.setColumnCount(3)
        self.history_table.setHorizontalHeaderLabels(["UUID", "字段名", "准确率"])
        self.history_table.horizontalHeader().setStretchLastSection(True)
        self.history_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        self.load_history()

        layout = QVBoxLayout()
        layout.addWidget(self.history_table)

        close_button = QPushButton("关闭")
        close_button.clicked.connect(self.history_dialog.close)
        layout.addWidget(close_button)

        self.history_dialog.setStyleSheet("""
            QDialog {
                background-color: #ffffff;
            }
            QPushButton {
                background-color: #0078d7;
                color: white;
                border-radius: 5px;
                padding: 5px 10px;
            }
            QPushButton:hover {
                background-color: #005ea6;
            }
            QTableWidget {
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QHeaderView::section {
                background-color: #e0e0e0;
            }
        """)
        self.history_dialog.setLayout(layout)
        self.history_dialog.exec_()

    def load_history(self):
        try:
            response = requests.post("http://127.0.0.1:5000/feedback/history", json={"Num": 10})
            response.raise_for_status()
            data = response.json()
            if data["status"] == "success":
                self.update_history_table(data["history"], data["correct_history"])
            else:
                QMessageBox.warning(self, "错误", data.get("error", "未知错误"))
        except requests.RequestException as e:
            QMessageBox.warning(self, "错误", f"请求失败: {str(e)}")

    def update_history_table(self, history, correct_history):
        self.history_table.setRowCount(0)
        for uuid, data in history.items():
            row_position = self.history_table.rowCount()
            self.history_table.insertRow(row_position)
            self.history_table.setItem(row_position, 0, QTableWidgetItem(uuid))
            for field, correct in correct_history[uuid].items():
                self.history_table.setItem(row_position, 1, QTableWidgetItem(field))
                self.history_table.setItem(row_position, 2, QTableWidgetItem(str(correct)))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = InfoExtractorApp()
    window.show()
    sys.exit(app.exec_())