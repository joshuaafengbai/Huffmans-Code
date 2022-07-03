# Huffmans-Code
Huffman coding is a lossless data compression algorithm. In this algorithm, a variable-length code is assigned to input different characters. The code length is related to how frequently characters are used. Most frequent characters have the smallest codes and longer codes for least frequent characters.

To encode, there are mainly two parts. First one to create a Huffman tree, and another one to traverse the tree to find codes.

For an example, consider some strings “YYYZXXYYX”, the frequency of character Y is larger than X and the character Z has the least frequency. So the length of the code for Y is smaller than X, and code for X will be smaller than Z.

Complexity for assigning the code for each character according to their frequency is O(n log n)

# Getting Started
Open a new terminal window or cmd if you are on windows

Change the directory to the directory in which you have your source.cpp file. For example, if it is in C:/Users/Dell/Documents, enter your command line − `$ cd 'C:/Users/Dell/Documents'`

Enter the following command to compile the source file using g++ `$ g++ -o <name-you-want-to-give> source.cpp`

Run it! Now you can run the program using − `$ ./myprogram`
