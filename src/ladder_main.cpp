#include "ladder.h"

int main() {
    cout << "Enter start word: ";
    string start_word;
    cin >> start_word;

    cout << "Enter end word: ";
    string end_word;
    cin >> end_word;

    for (char &c : start_word) {
        c = (char)tolower(c);
    }
    for (char &c : end_word) {
        c = (char)tolower(c);
    }

    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words cannot be the same!");
        return 0;
    }

    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    return 0;
}

