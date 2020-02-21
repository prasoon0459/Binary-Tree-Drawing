def num_nodes(m):
	return 2 ** (m+1) - 1

for m in range(0, 15):
	n = num_nodes(m)
	with open("perfect_binary_trees", "a") as file:
		file.write(str(n))
		for item in list(range(1, n+1)):
			file.write(" ")
			file.write(str(item))
		file.write("\n")