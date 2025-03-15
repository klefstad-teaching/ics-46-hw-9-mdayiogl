#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error with \"" << word1 << "\" and \"" << word2 << "\": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }
    if (str1.size() == str2.size()) {
        int diffCount = 0;
        for (size_t i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                diffCount++;
                if (diffCount > d) return false;
            }
        }
        return (diffCount == 1);
    }

    const string& longer = (str1.size() > str2.size()) ? str1 : str2;
    const string& shorter = (str1.size() > str2.size()) ? str2 : str1;

    size_t i = 0, j = 0;
    int mismatchCount = 0;
    while (i < longer.size() && j < shorter.size()) {
        if (longer[i] != shorter[j]) {
            mismatchCount++;
            if (mismatchCount > 1) return false;
            i++;
        } else {
            i++;
            j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        const string& last_word = current_ladder.back();

        for (auto const & dict_word : word_list) {
            if (visited.find(dict_word) == visited.end() && is_adjacent(last_word, dict_word)) {
                visited.insert(dict_word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(dict_word);
                if (dict_word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Could not open file: " << file_name << endl;
        return;
    }
    string word;
    while (in >> word) {
        for (char &c : word) {
            c = (char) tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    cout << "cat -> dog: "    << generate_word_ladder("cat",   "dog",   word_list).size() << endl;
    cout << "marty -> curls: "<< generate_word_ladder("marty", "curls", word_list).size() << endl;
    cout << "code -> data: "  << generate_word_ladder("code",  "data",  word_list).size() << endl;
    cout << "work -> play: "  << generate_word_ladder("work",  "play",  word_list).size() << endl;
    cout << "sleep -> awake: "<< generate_word_ladder("sleep", "awake", word_list).size() << endl;
    cout << "car -> cheat: "  << generate_word_ladder("car",   "cheat", word_list).size() << endl;
}
