# Installation & Execution

1. Navigate to the directory with the source and run `make` to build the code. 
2. The code can be run using the command `./a.out`. One command line argument is expected by the program. For interactive mode (where you are asked to enter points manually one by one) type 'i' and for inputting the binary tree as an array, use 'a'. Details on how the input format works will be explained in a subseuent subsection.

## Array: Input Format
1. The 0th element of the array is the root. 
2. The left and right children of element *i* in the array are *2i + 1* and *2i + 2* respectively. 
3. The first line of input must contain an integer *n*, the size of the array being inputted. 
4. The next line must contain *n* space-separated numbers denoting the value inside of the nodes. 
5. If a node isn't present, enter -1. 

## Dummy Data

You can run the program to make complete binary trees of a certain depth. 
1. Go to the `examples` directory and run `python generate_perfect_trees.py`
2. Come back to the source director. `cd ..`
3. Run `grep "^15" examples/perfect_binary_trees |  ./a.out`
4. The value 15 can be modified to `[1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 4095...]`
5. The program will report the time taken to calculate the coordinates and the time taken to plot them separatly.

# Run Time
Running it on the dummy dataset gave us these values

|          |                         |                  |
|----------|-------------------------|------------------|
| \# Nodes | Calculation Time \(μs\) | Plot Time \(μs\) |
| 1        | 1                       | 76451            |
| 3        | 2                       | 86456            |
| 7        | 5                       | 92099            |
| 15       | 5                       | 92099            |
| 31       | 9                       | 97912            |
| 63       | 15                      | 89315            |
| 127      | 27                      | 87238            |
| 255      | 51                      | 90777            |

