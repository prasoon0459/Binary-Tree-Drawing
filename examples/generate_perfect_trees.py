## @package generate_perfect_trees
# Generate complete and perfect binary trees of different sizes and save them
# to file to enable testing the binary tree drawing program with inputs of
# various sizes. 


## @brief return the number of nodes in a binary tree of depth m
# for depth 0, we have only one node, the root node 
# @param m depth of binary tree (max path length possible)
def num_nodes(m):
	return 2 ** (m+1) - 1

for m in range(0, 17):
	n = num_nodes(m)
	with open("perfect_binary_trees", "a") as file:
		file.write(str(n))
		for item in list(range(1, n+1)):
			file.write(" ")
			file.write(str(item))
		file.write("\n")
	print(2**m - 1)