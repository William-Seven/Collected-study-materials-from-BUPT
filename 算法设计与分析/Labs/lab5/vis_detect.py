import numpy as np
import matplotlib.pyplot as plt

x_values = []
count = []

with open('data/val_results_x_left.txt', 'r') as values:
    line_number = 0
    for value in values:
        x_values.append(float(value))
        count.append(line_number)
        line_number += 1

plt.plot(count, x_values, label='ranges vs. values')
plt.xlabel('ranges')
plt.ylabel('values')
plt.title('ranges vs. values')
plt.legend()
# plt.show()
plt.savefig('detect_range_value_left.png')