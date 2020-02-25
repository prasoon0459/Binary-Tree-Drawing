## @package runtimes
# Run the binary tree drawing algorithm for different sizes of inputs
# of perfect binary trees multiple times and plot the average time
# taken to draw each of them. Also, save all runtime data to file at a 
# user specified location

import numpy as np
import os
import matplotlib.pyplot as plt

## @var values
# set of number of nodes to test the program with 
values = [1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767]
template = "grep '{} ' examples/perfect_binary_trees |  ./a.out a"

## @var all_plot_times
# an array of arrays storing all the runtimes for plotting
all_plot_times = []
## @var all_calculate_times
# an array of arrays storing all the runtimes for calculation of node positions
all_calculate_times = []
average_plot_times = []
average_calculate_times = []


## @remark
# make sure to remove the glutMainLoop() function call in main.cpp before running this
# code - not doing so will cause the program to wait till one window is closed before moving
# to the next round of execution
for value in values:
	print("Doing value: ", value)
	plot_times = []
	calculate_times = []
	for i in range(0,5):
		command = template.format(value)
		output = os.popen(command).read()
		output = output.split(',')
		print(output)
		calculate_times.append(int(output[0]))
		plot_times.append(int(output[1]))
	all_plot_times.append(plot_times)
	all_calculate_times.append(calculate_times)
	average_plot_times.append(sum(plot_times)/len(plot_times))
	average_calculate_times.append(sum(calculate_times)/len(calculate_times))

all_plot_times = np.asarray(all_plot_times)
all_calculate_times = np.asarray(all_calculate_times)
np.savetxt("all_plot_times.csv", all_plot_times, delimiter=",")
np.savetxt("all_calculate_times.csv", all_calculate_times, delimiter=",")

# Test Plotting
# average_plot_times = np.asarray([1, 3, 7, 15, 31, 63, 127, 255, 511, 1023]) * 94 + 23
# average_calculate_times = np.asarray([1, 3, 7, 15, 31, 63, 127, 255, 511, 1023]) * 2

plt.plot(values, average_plot_times, linestyle = '-', color='r', marker='o', label='Average Plot Times')
plt.plot(values, average_calculate_times, linestyle = '-', color = 'b', marker='o', label='Average Calculation Times')
plt.grid(b=True)
plt.title('Runtimes')
plt.ylabel('Time')
plt.xlabel('Nodes')
plt.legend()
plt.show()