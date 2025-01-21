import subprocess
import matplotlib.pyplot as plt
import time

# 存储缺页率的列表
fifo_fault_rates = []
lru_fault_rates = []
optimal_fault_rates = []

# 运行次数
iterations = 100

# 循环执行 C 程序 100 次，并记录不同算法的缺页率
for _ in range(iterations):
    result = subprocess.run(
        ['./main_hund'], capture_output=True, text=True)

    # 获取 C 程序的输出，格式为 "fifo_rate,lru_rate,optimal_rate"
    output = result.stdout.strip().split(',')

    # 解析输出结果
    fifo_rate = float(output[0])
    lru_rate = float(output[1])
    optimal_rate = float(output[2])

    # 将缺页率添加到列表
    fifo_fault_rates.append(fifo_rate)
    lru_fault_rates.append(lru_rate)
    optimal_fault_rates.append(optimal_rate)
    time.sleep(0.5)

# 绘制折线图
plt.plot(range(1, iterations + 1), fifo_fault_rates, label='FIFO',
         marker='o', linestyle='-', color='b')  # 圆点表示 FIFO，蓝色
plt.plot(range(1, iterations + 1), lru_fault_rates, label='LRU',
         marker='s', linestyle='-', color='g')  # 方块表示 LRU，绿色
plt.plot(range(1, iterations + 1), optimal_fault_rates, label='Optimal',
         marker='^', linestyle='-', color='r')  # 三角形表示 Optimal，红色

# 添加图表标题和标签
plt.title('Page Fault Rate for Different Algorithms (100 Iterations)', fontsize=14)
plt.xlabel('Iteration', fontsize=12)
plt.ylabel('Page Fault Rate', fontsize=12)

# 显示图表
plt.grid(True)
plt.legend()
plt.show()
