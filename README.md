# Word_Composition_solution_impledge

Input Files: The program expects two input files Input_01.txt and Input_02.txt containing alphabetically sorted words list (one word per line, all lower case).

Output: The program will display the following information:

Longest compounded word
Second longest compounded word
Time taken to process the input files

# Design Approach:

The program uses a Trie (prefix tree) data structure to efficiently store and search for words.

It reads the words from the input file and inserts them into the Trie, ensuring all words are in lowercase and without any special characters.

It then traverses the Trie to identify compound words by checking if a word can be constructed by concatenating shorter words from the Trie. 
It does this by recursively breaking down each word character by character.

The program calculates the time taken for processing using the GetProcessTimes function, measuring CPU execution time.

   
