from src.parser import parse_script
from src.interpreter import Interpreter
import sys
import os
sys.path.insert(0, 'src')


def load_script(file_path):
    """
    加载并解析脚本文件
    """
    with open(file_path, 'r', encoding='utf-8') as file:
        script_content = file.read()

    # 解析脚本内容
    parsed_script = parse_script(script_content)
    return parsed_script


def main():
    """
    主函数，加载脚本并运行解释器
    """
    if len(sys.argv) > 1:
        script_file_path = sys.argv[1]  # 从命令行获取脚本路径
    else:
        script_file_path = 'scripts/script1.txt'  # 默认使用 script1.txt

    if not os.path.exists(script_file_path):
        print(f"脚本文件 {script_file_path} 不存在！")
        sys.exit(1)

    parsed_script = load_script(script_file_path)

    if parsed_script:
        # 初始化解释器并运行
        interpreter = Interpreter(parsed_script.script)
        interpreter.run()
    else:
        print("解析脚本失败，无法执行解释器。")


if __name__ == "__main__":
    main()
