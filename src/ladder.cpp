#include "ladder.h"
#include <vector>

void error(string word1, string word2, string msg){
    cout << "Error with the following: " << word1 << " and " << word2 << " " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (abs(d) > 1) 
        return 0;
    else
        return 1;
}

bool is_adjacent(const string& word1, const string& word2){
    int d = word1.length() - word2.length();
    if (abs(d) > 1) 
        return 0;
    else
        return edit_distance_within(word1, word2, d) == 1;
}

//Never reuse words -- visited??
//Allow word ladder start words to be outside the dictionary -- 
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    vector<string> first_stack;
    first_stack.push_back(begin_word);
    ladder_queue.push(first_stack);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()){
        vector<string> ladder = std::move(ladder_queue.front());
        ladder_queue.pop();
        string& last_word = ladder.back();
        for(const string& word: word_list){
            if (is_adjacent(last_word, word)){
                if (!visited.contains(word)){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(std::move(word));
                    if (word == end_word){
                        return new_ladder;
                    }    
                    visited.insert(word);
                    ladder_queue.push(new_ladder);
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
    string s;
    while(getline(in,s)){
    word_list.emplace(std::move(s));
    }
    in.close();
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
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
