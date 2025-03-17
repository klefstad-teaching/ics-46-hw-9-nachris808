#include "ladder.h"
#include <unordered_set>
#include <vector>

void error(string word1, string word2, string msg){
    cout << "Error with the following: " << word1 << " and " << word2 << " " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
   //Damerau–Levenshtein distance w/ optimization
    int s1 = str1.length(), s2 = str2.length(), prev;
    if (abs(d) > 1) return 0;
    if (s1 > s2) return edit_distance_within(str2, str1, d);
    vector<int> curr(s2 + 1,0);
    for (int j = 0; j <= s2; ++j){
        curr[j] = j;
    }
    for (int i = 1; i <= s1; ++i){
        prev = curr[0];
        curr[0] = i;
        for (int j = 1; j <= s2; ++j){
            if (curr[s2] < 2) return curr[s2] < 2;
            int temp = curr[j];
            if (str1[i-1] == str2[j-1])
                curr[j] = prev;
            else
                curr[j] = min(prev, min(curr[j-1], curr[j])) + 1;
            prev = temp;
        }
    }
return curr[s2] < 2;
}


bool is_adjacent(const string& word1, const string& word2){
    int d = word1.length() - word2.length();
    return edit_distance_within(word1, word2, d);
}

//Never reuse words -- visited??
//Allow word ladder start words to be outside the dictionary -- 
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) return {};
    queue<vector<string>> ladder_queue;
    vector<string> first_stack;
    first_stack.push_back(begin_word);
    ladder_queue.push(first_stack);
    unordered_set<string> visited{begin_word};
    while (!ladder_queue.empty()){
        vector<string> ladder = std::move(ladder_queue.front());
        ladder_queue.pop();
        string& last_word = ladder.back();
        for(const string& word: word_list){
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word){
                        return new_ladder;
                    }    
                    visited.insert(word);
                    ladder_queue.push(std::move(new_ladder));
                }
            }
        }
    }
return {};    
}


void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in.is_open()){
        error("load", "words", "can't open");
        return;
    }
    for (string s; in >> s;)
        word_list.insert(s);
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) 
        cout << "No word ladder found.";
    else{
        cout << "Word ladder found: ";
        for(auto i: ladder)
            cout << i << " ";
    }    
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
