import numpy as np
import matplotlib.pyplot as plt
import os

def draw_pyramid(path_file_name, pyramid_file_name, fig_name):
    # 读取文件
    # with open('pyramid_map.txt', 'r') as file:
    with open(pyramid_file_name, 'r') as file:
        lines = file.readlines()

    # 将每一行转换为整数列表，并去掉可能存在的换行符
    pyramid_data = [list(map(int, line.strip().split(','))) for line in lines]

    # 创建一个空的矩阵，用于存放金字塔的数据
    max_width = max(len(row) for row in pyramid_data)
    matrix = np.zeros((len(pyramid_data), max_width))

    # 填充矩阵
    for i, row in enumerate(pyramid_data):
        matrix[i, :len(row)] = row

    # 路径数据读取
    # path_dir = f'path_dp_x_{k}.txt'
    path_dir = path_file_name
    try:
        with open(path_dir, 'r') as file:
            lines = file.readlines()
            path_data = [tuple(map(int, line.strip().split(' '))) for line in lines]
    except FileNotFoundError:
        print(f"File {path_dir} not found.")
        return

    # 标记路径点
    for row, col in path_data:
        if 0 <= row < matrix.shape[0] and 0 <= col < matrix.shape[1]:
            matrix[row, col] = 110

    # 绘制原始金字塔热力图
    plt.figure(figsize=(10, 8))
    plt.imshow(matrix, cmap='Reds', interpolation='nearest')
    plt.colorbar()
    plt.title('Original Pyramid Heatmap')
    plt.xlabel('Position in Row')
    plt.ylabel('Row Number')

    # 确保保存路径目录存在
    # save_dir = './screenshot/dp_x_' + str(k) + '.png'
    save_dir = fig_name
    os.makedirs(os.path.dirname(save_dir), exist_ok=True)
    plt.savefig(save_dir)
    plt.close()  # 关闭图形以释放内存

if __name__ == '__main__':
    # for i in range(1, 100):
        # draw_pyramid('./data/path_dp_x_' + str(i) + '_right.txt', './data/pyramid_map.txt', 'screenshot/dp_x_' + str(i) + '_right.png')
    draw_pyramid('./data/path_greedy.txt','./data/pyramid_map.txt','./screenshot/greedy.png')
    draw_pyramid('./data/path_dp.txt','./data/pyramid_map.txt','./screenshot/dp.png')


