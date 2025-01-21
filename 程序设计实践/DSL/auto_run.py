import subprocess
import time


def run_script_with_input():
    """
    运行指定的脚本并自动输入模拟数据
    """
    script_path = 'scripts/script1.txt'
    inputs = [
        '我要投诉你们',
        '我觉得你们协会的任务太简单了',
        '没有了',
        '查询一下我的账户金额',
        '我想存钱',
        '2025',
        '我要卖东西',
        '我要卖一些武器',
        '我还要买一些物品',
        '来一瓶生命药水',
        '再查询一下我的账户',
        '这句话是我说给别人听的',
        '',
        '我离开了'
    ]

    # 通过 subprocess 启动 run.py
    process = subprocess.Popen(
        ['E:\WILLIAMZHANG\PracticeProgramming\DSL\DSL\.venv\Scripts\python.exe', 'run.py', script_path],
        stdin=subprocess.PIPE,  # 模拟用户输入
        stdout=subprocess.PIPE,  # 捕获输出
        stderr=subprocess.PIPE,
        text=True
    )

    # 捕获并打印实时输出
    while True:
        output = process.stdout.readline()

        # 输出结束标志
        if output == '' and process.poll() is not None:
            break

        # 打印标准输出
        if output:
            print(f"Bot: {output.strip()}")

        # 等待用户输入并模拟输入
        if "请回复" in output and inputs:
            user_input = inputs.pop(0)  # 从输入列表中获取一个用户输入
            print(f"User: {user_input}")  # 打印模拟输入到终端
            # time.sleep(3)  # 等待一段时间以便脚本处理
            process.stdin.write(user_input + '\n')  # 写入模拟输入
            process.stdin.flush()  # 确保输入被刷新到 stdin
            time.sleep(1)  # 等待一段时间以便脚本处理

    # 关闭所有的流
    process.stdout.close()
    process.stderr.close()
    process.stdin.close()


# 示例：自动运行脚本并模拟输入
if __name__ == '__main__':
    run_script_with_input()
