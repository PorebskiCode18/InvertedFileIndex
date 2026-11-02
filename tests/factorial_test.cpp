#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <string>
#include "../src/factorial.hpp"

TEST_CASE("inverted index counts words correctly", "[index]") {
    InvertedIndex idx;
    idx.addText("The brown cat and the blue rat live in the brown house.");
    REQUIRE(idx.totalWords() == 12);
}

TEST_CASE("benchmarking addText on different text sizes") {
    const string paragraph = "The brown cat and the blue rat live in the brown house. "
                             "They enjoy live music concerts. ";

    const vector<int> copyCounts = {1, 3, 10, 30, 100, 300, 1000, 3000, 10000, 14700};

    for (int copies : copyCounts) {
        string text;
        for (int i = 0; i < copies; i++) {
            text += paragraph;
        }

        BENCHMARK("words=" + to_string(copies * 17)) {
            InvertedIndex idx;
            idx.addText(text);
            return idx.uniqueWords();
        };
    }
}
