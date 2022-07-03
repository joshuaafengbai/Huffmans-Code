# Huffman Coding Algorithm
Huffman coding is a lossless data compression algorithm. In this algorithm, a variable-length code is assigned to input different characters. The code length is related to how frequently characters are used. Most frequent characters have the smallest codes and longer codes for least frequent characters.

## To Encode
The code for a character c is obtained by tracing the path from the root of T to the leaf node where c is stored, and associating a left child with ’0’ and a right child with ’1’. For example, the code for ’g’ is 00 (left→left), and the code for ’h’ is 1101 (right→right→left→right). Finally, the compressed string M’ is obtained by concatenating all the consecutive code words for all the characters in M. For example, using the Huffman encoding table in Table 2, the 13-characters (104-bits) input string M = ”go go gophers” will be encoded as the following 37-bits compressed string: M’ = 0001100000110000011110110110111111100.

## To Decode
The Huffman encoding table constructed from the Huffman tree T has an important property called the prefix property: no code word in the encoding table is a prefix of another code word. This property simplifies the decoding of M’ in order to get back to M: by following the root-toleaf paths in the Huffman tree T. In the previous example, the compressed string M’ = 0001100000110000011110110110111111100 is decoded left→left (i.e. the character ’g’), then left→right (i.e. the character ’o’), then right→left→left (i.e. the character ’ ’) etc..., which leads finally to the output string M” = ”go go gophers” = M.

Complexity for assigning the code for each character according to their frequency is O(n log n)

# Getting Started
Open a new terminal window or cmd if you are on windows

Change the directory to the directory in which you have your source.cpp file. For example, if it is in C:/Users/Dell/Documents, enter your command line − `$ cd 'C:/Users/Dell/Documents'`

Enter the following command to compile the source file using g++ `$ g++ -o <name-you-want-to-give> source.cpp`

Run it! Now you can run the program using − `$ ./myprogram`
