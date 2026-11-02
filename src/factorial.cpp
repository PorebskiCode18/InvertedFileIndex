#include "factorial.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <map>

using namespace std;

//this function name set up was a way I found online to utilize classes and
//still have a dedicated hpp file by defining the class in hpp and stating
//which class the function comes from in cpp
const unordered_set<string>& InvertedIndex::commonWords() {
    static const unordered_set<string> words = {
        "a", "an", "and", "are", "as", "at", "be", "but", "by", "for", "from",
        "had", "has", "have", "he", "her", "his", "i", "if", "in", "into", "is",
        "it", "its", "me", "my", "of", "on", "or", "our", "she", "so", "that",
        "the", "their", "them", "then", "there", "these", "they", "this", "to",
        "was", "we", "were", "will", "with", "you", "your"
    };
    return words;
}

bool InvertedIndex::buildFromFile(const string& inputPath) {
    ifstream input(inputPath);
    if (!input) return false;

    string line;
    while (getline(input, line)) {
        addText(line);
    }
    return true;
}

void InvertedIndex::addText(const string& text) {
    // Ignore common words
    const auto& stop = commonWords();
    string word;
    
    // Lambda function to handle the end of a word for any type
    auto endWord = [&]() {
        if (word.empty()) return;
        if (stop.find(word) == stop.end()) {
            index[word].push_back(position);
        }
        ++position;
        word.clear();
    };

    const size_t n = text.size();
    for (size_t i = 0; i < n; ++i) {
        const char c = text[i];
        const bool nextIsAlnum = (i + 1 < n) && isalnum(static_cast<unsigned char>(text[i + 1]));

        if (isalnum(static_cast<unsigned char>(c))) {
            word += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        } else if (c == '-' && !word.empty() && nextIsAlnum) {
            word += '-'; 
        } else if (c == '\'' && !word.empty() && nextIsAlnum) {
            //if work has '
            continue; 
        } else {
            endWord();
        }
    }
    endWord();
}
bool InvertedIndex::writeToFile(const string& outputPath) const {
    ofstream out(outputPath);
    if (!out) return false;

    map<string, vector<size_t>> sorted(index.begin(), index.end());

    out << "{\n";
    bool first = true;
    for (const auto& entry : sorted) {
        if (!first) out << ",\n";
        first = false;

        out << "  \"" << entry.first << "\": [";
        for (size_t i = 0; i < entry.second.size(); i++) {
            if (i > 0) out << ", ";
            out << entry.second[i];
        }
        out << "]";
    }
    out << "\n}\n";
    return true;
}
