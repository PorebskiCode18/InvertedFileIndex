#include <iostream>
#include <fstream>
#include <string>

#include "src/factorial.hpp"

using namespace std;

int main() {
    string text = "The brown cat and the blue rat live in the brown house. "
                  "They enjoy live music concerts. ";

    InvertedIndex invIndex;
    invIndex.addText(text);

    if (!invIndex.writeToFile("index.json")) {
        cout << "Error: could not write index.json" << endl;
        return 1;
    }

    cout << "Indexed " << invIndex.totalWords() << " words ("
         << invIndex.uniqueWords() << " unique terms)\n" << endl;

    ifstream input("index.json");
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }

    return 0;
}
