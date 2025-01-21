import subprocess
import matplotlib.pyplot as plt

# 定义内存大小的范围
memory_sizes = list(range(1, 61))

# 存储缺页率的字典
fifo_fault_rates = []
lru_fault_rates = []
optimal_fault_rates = []

# 循环执行C程序，并记录不同内存大小的缺页率
for memory_size in memory_sizes:
    # 调用C程序，传入memory_size
    result = subprocess.run(
        ['./main_diff', str(memory_size)], capture_output=True, text=True)

    # 获取C程序的输出，格式为 "memory_size,fifo_rate,lru_rate,optimal_rate"
    output = result.stdout.strip().split(',')
    memory_size = int(output[0])
    fifo_rate = float(output[1])
    lru_rate = float(output[2])
    optimal_rate = float(output[3])

    # 将缺页率添加到列表
    fifo_fault_rates.append(fifo_rate)
    lru_fault_rates.append(lru_rate)
    optimal_fault_rates.append(optimal_rate)

# 绘制折线图
plt.plot(memory_sizes, fifo_fault_rates, label='FIFO',
         marker='o', linestyle='-', color='b')  # 圆点表示 FIFO，蓝色
plt.plot(memory_sizes, lru_fault_rates, label='LRU',
         marker='s', linestyle='-', color='g')  # 方块表示 LRU，绿色
plt.plot(memory_sizes, optimal_fault_rates, label='Optimal',
         marker='^', linestyle='-', color='r')  # 三角形表示 Optimal，红色

# 添加图表标题和标签
plt.title('Page Fault Rate vs Memory Size', fontsize=14)
plt.xlabel('Memory Size', fontsize=12)
plt.ylabel('Page Fault Rate', fontsize=12)

# 显示图表
plt.grid(True)
plt.legend()
plt.show()
