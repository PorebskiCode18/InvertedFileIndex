#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class InvertedIndex {
public:
    bool buildFromFile(const string& inputPath);

    bool writeToFile(const string& outputPath) const;

    void addText(const string& text);

    size_t totalWords() const { return position; }
    size_t uniqueWords() const { return index.size(); }

private:
    static const unordered_set<string>& commonWords();

    unordered_map<string, vector<size_t>> index;
    size_t position = 0; 
};
