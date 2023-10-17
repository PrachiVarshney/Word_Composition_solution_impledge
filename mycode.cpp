#include <processthreadsapi.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;


/* Function for execution time */
double getExecutionTime(){
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }else{
        
        return 0;
    }
}

const int MAX = 32;

class Tries {
public:
        bool end;
        vector<Tries *> children;
        Tries(int arity);
        ~Tries();
};

Tries :: Tries(int arity) {
        end = false;
        for (int i = 0; i < arity; i++) {
                children.push_back(NULL);
        }
}

Tries :: ~Tries() {
        vector<Tries *> :: iterator i = children.begin();
        for (; i != children.end(); ++i)
                if (*i != NULL)
                        delete(*i);
}


class Trie {
        Tries *root;
        int arity;
public:
        Trie(int value);
        ~Trie();
        void stripWord(string &word);
        void insertWord(string word);
        bool CheckCompund(string word, int);
};

Trie :: Trie(int value) {
        arity = value;
        root = new Tries(arity);
}

Trie :: ~Trie() {
        delete(root);
}

inline void Trie :: stripWord(string &word) {
        if (*word.rbegin() == '\r') {
                word.erase(word.length() - 1);
        }
}

/* Function to insert a word in the Trie tree */
void Trie :: insertWord(string word) {
        Tries *r = root;

        for (string :: iterator i = word.begin(); i != word.end(); ++i) {
                char chr = *i;
                int index = chr - 'a';

                if (r -> children[index] == NULL) {
                        r -> children[index] = new Tries(arity);
                }
                r = (Tries *)r -> children[index];
        }
        if (!r -> end)
                r -> end = true;
}

/* checking for compoundwords */
bool Trie :: CheckCompund(string word, int word_length) {
        Tries *r = root;
        int cnt = 0;
        if (word.empty())
                return true;

        string :: iterator i = word.begin();
        while (i != word.end()) {
                char chr = *i;
                int index = chr - 'a';
                r = r -> children[index];
                if (r != NULL) {
                        if (r -> end) {
                                string suffix = string(word, cnt + 1);
                                if (CheckCompund(suffix, word_length)) {
                                        if (word.length() != word_length) {
                                                return true;
                                        } else if (suffix.length() == 0) {
                                                return false;
                                        } else {
                                                return true;
                                        }
                                }
                        }
                }
                else {
                        return false;
                }
                i++;
                cnt++;
        }
        if (!(r -> end)) {
                return false;
        }
}

/* Function for file parsing from user */
void getFile(char filename[]) {
        ifstream file;
        cout << "Enter filename: ";
        cin >> filename;
        file.open(filename);
        while(!file) {
                cout << "Enter filename: ";
                cin >> filename;
                file.open(filename);
        }
        file.close();
}

/* Function to load all the words from the given file in the Trie tree */
void load(Trie &T, char *filename) {
        ifstream file;
        file.open(filename);
        for (string word; getline(file, word);) {
                T.stripWord(word);
                T.insertWord(word);
        }
        file.close();
}

/* 
   It identifies and displays the first and second longest compound words.
 */
void Find_Cmp_Words(Trie &T, char *filename) {
        string word, longest_word, second_longest_word;
        int count = 0, max_length = 0, second_max_length = 0;

        ifstream file;
        file.open(filename);

        for (string word; getline(file, word);) {
                T.stripWord(word);
                if (T.CheckCompund(word, word.length())) {
                        count++;
                        if (max_length < word.length()) {
                                second_max_length = max_length;
                                second_longest_word = longest_word;

                                max_length = word.length();
                                longest_word = word;
                        }
                        else {
                                if (second_max_length <= word.length()) {
                                        second_max_length = word.length();
                                        second_longest_word = word;
                                }
                        }
                }
        }
        file.close();
        cout << "Longest Compound Word: " << setw(30) << longest_word << endl;
        cout << "Second Longest Compounded Word: " << setw(30) << second_longest_word << endl;
}

int main(int argc, char *argv[]) {
        Trie T(26);
        char filename[MAX];
        
        // execution time
	double begin = getExecutionTime();

        getFile(filename);
        load(T, filename);
        Find_Cmp_Words(T, filename);
        
        //  processing_time 
    	double end = getExecutionTime();
    	double processing_time = (end - begin);
    	printf("Time measured: %.3f seconds.\n", processing_time);
        return 0;
}