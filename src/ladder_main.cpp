#include "ladder.h"

int main(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    vector<string> word_ladder;
    word_ladder = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(word_ladder);
    //verify_word_ladder();
    return 0;
}