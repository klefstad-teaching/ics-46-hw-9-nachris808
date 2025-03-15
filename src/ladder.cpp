#include "ladder.h"
#include <vector>

void error(string word1, string word2, string msg){
    cout << "Error with the following: " << word1 << " and " << word2 << " " << msg;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (d > 1) return 0;
    int s1 = str1.size();
    int s2 = str2.size();
    vector<vector<int>> dp(s1 + 1, vector<int>(s2 + 1, 0));
    for(int i = 1; i <= str1.size(); i++)
        dp[i][0] = i;
    for(int j = 1; j <= str2.size(); j++)
        dp[0][j] = j;

    for(int i = 1; i <= str1.size(); i++){
        for(int j = 1; j <= str2.size(); j++){
            if (str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]));
            }
        }
    }  
int dist = dp[s1][s2];    
if (dist > 1) return 0;  
return 1;
}
bool is_adjacent(const string& word1, const string& word2){
    int diff = word1.size() - word2.size();
    return edit_distance_within(word1, word2, diff);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    vector<string> first_stack;
    first_stack.push_back(begin_word);
    ladder_queue.push(first_stack);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(string word: word_list){
            if (is_adjacent(last_word, word)){
                if (!visited.contains(word)){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word){
                        return new_ladder;
                    }    
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
error(begin_word, end_word, "no word ladder possible");    
return first_stack;    
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    string s;
    while(getline(in,s)){
    word_list.insert(s);
    }
    in.close();
}
void print_word_ladder(const vector<string>& ladder){
    for(int i = 0; i < ladder.size(); ++i)
        cout << ladder.at(i) << " ";
    cout << endl;
}
void verify_word_ladder(){
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
