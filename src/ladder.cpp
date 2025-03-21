#include "ladder.h"
#include <algorithm>

using namespace std;

static int simple_edit_distance(const string& s1, const string& s2) {
    int len1 = (int)s1.size(), len2 = (int)s2.size();
    if (abs(len1 - len2) > 1) return 99;
    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (s1[i] != s2[i]) {
                diffCount++;
                if (diffCount > 1) return 99;
            }
        }
        return diffCount;
    }
    const string &longer = (len1 > len2) ? s1 : s2;
    const string &shorter = (len1 > len2) ? s2 : s1;
    int i = 0, j = 0, mismatch = 0;
    while (i < (int)longer.size() && j < (int)shorter.size()) {
        if (longer[i] != shorter[j]) {
            mismatch++;
            if (mismatch > 1) return 99;
            i++;
        } else {
            i++; j++;
        }
    }
    return mismatch;
}

void error(string word1, string word2, string msg) {
    cerr << "Error with \"" << word1 << "\" and \"" << word2 << "\": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int dist = simple_edit_distance(str1, str2);
    if (dist == 0) return false;
    return dist <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word,
                                    const string& end_word,
                                    const set<string>& word_list) {
    if (begin_word == end_word) return {};
    if (word_list.find(end_word) == word_list.end()) return {};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_path = ladder_queue.front();
        ladder_queue.pop();
        const string &last_word = current_path.back();

        for (auto &dict_word : word_list) {
            if (visited.find(dict_word) == visited.end() &&
                is_adjacent(last_word, dict_word)) {
                visited.insert(dict_word);
                vector<string> new_path = current_path;
                new_path.push_back(dict_word);
                if (dict_word == end_word) {
                    return new_path;
                }
                ladder_queue.push(new_path);
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
            c = (char)tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (auto &w : ladder) {
        cout << w << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    cout << generate_word_ladder("cat", "dog", word_list).size() << endl;
    cout << generate_word_ladder("marty", "curls", word_list).size() << endl;
    cout << generate_word_ladder("code", "data", word_list).size() << endl;
    cout << generate_word_ladder("work", "play", word_list).size() << endl;
    cout << generate_word_ladder("sleep", "awake", word_list).size() << endl;
    cout << generate_word_ladder("car", "cheat", word_list).size() << endl;
}
