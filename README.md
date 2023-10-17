# Word_Composition_solution_impledge

1. This program reads provided files Input_01.txt and Input_02.txt, containing alphabetically sorted words list (one word per line, no spaces, all lower case).

2. IIt identifies and displays the following data in the console:

Longest compounded word
Second longest compounded word
Time taken to process the input file

# Approach:

To address this problem, we employed a Trie (prefix tree) data structure. A Trie allows for efficient searching of words character by character. It provides an O(m) search time for a word, where 'm' is the word length. We chose a Trie to keep track of all valid words that can be part of a compound word conveniently.

To determine if a word is a compound word, the program iterates through the characters of the word, searching for complete words in the Trie. It recursively checks whether the remaining part is also a valid word or a compound word.

The worst-case time complexity to check whether a word is a compound word is O(m^2), where 'm' is the word length. For 'n' words, the time complexity is O(n * m^2). Fortunately, the word length 'm' is generally small for a large dataset, making the program efficient for practical use.


   
