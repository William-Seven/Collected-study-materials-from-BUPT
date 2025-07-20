import os
import subprocess

# 获取当前脚本所在路径
current_path = os.path.dirname(os.path.abspath(__file__))

# 定义测试文件夹列表和日志文件路径
test_folders = [
    os.path.join(current_path, "../error_test_bison"),
    os.path.join(current_path, "../error_test_lex"),
    os.path.join(current_path, "../correct_test")
]
log_file_path = os.path.join(current_path, "parser_output.log")

# 检查parser.exe是否存在
parser_path = os.path.join(current_path, "parser.exe")
if not os.path.exists(parser_path):
    print(f"parser.exe 不存在于 {current_path} 目录中！")
    exit(1)

# 打开日志文件用于写入
with open(log_file_path, "w", encoding="utf-8") as log_file:
    # 遍历所有测试文件夹
    for folder in test_folders:
        # 检查文件夹是否存在
        if not os.path.exists(folder):
            print(f"测试文件夹 {folder} 不存在，跳过！")
            log_file.write(f"警告: 测试文件夹 {folder} 不存在，已跳过\n")
            continue

        log_file.write(f"=== 开始测试文件夹: {os.path.basename(folder)} ===\n\n")

        # 遍历当前文件夹中的所有文件
        for filename in sorted(os.listdir(folder)):
            # 构造完整的文件路径
            file_path = os.path.join(folder, filename)

            # 检查是否为文件
            if os.path.isfile(file_path):
                # 输出当前处理的文件信息到日志文件
                print(f"执行文件：{filename}")
                log_file.write(f"执行文件: {filename}\n")
                log_file.write("-" * 50 + "\n")

                # 构造运行parser.exe的命令
                command = [parser_path, "-i", file_path]

                # 运行命令并捕获输出
                try:
                    # 捕获原始字节输出
                    result = subprocess.run(command, capture_output=True, text=False, check=False)

                    # 尝试解码输出（优先尝试UTF-8，如果失败则尝试GBK）
                    try:
                        stdout = result.stdout.decode("utf-8")
                    except UnicodeDecodeError:
                        stdout = result.stdout.decode("gbk", errors="replace")

                    try:
                        stderr = result.stderr.decode("utf-8")
                    except UnicodeDecodeError:
                        stderr = result.stderr.decode("gbk", errors="replace")

                    # 将输出写入日志文件
                    if stdout.strip():
                        log_file.write("标准输出:\n")
                        log_file.write(stdout)

                    if stderr.strip():  # 如果有错误输出
                        log_file.write("错误输出:\n")
                        log_file.write(stderr)

                except Exception as e:
                    # 捕获其他异常
                    log_file.write(f"处理 {filename} 时发生异常: {e}\n")

                # 添加执行完成的提示
                log_file.write(f"文件 {filename} 执行完成\n")
                log_file.write("-" * 50 + "\n\n")

        log_file.write(f"=== 结束测试文件夹: {os.path.basename(folder)} ===\n\n\n")

print(f"所有文件处理完成，日志已保存到 {log_file_path}")