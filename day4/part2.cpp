#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    std::string input_str;
    // parse from file input.txt
    long num_of_lines{};
    {
        std::ifstream input_file("../day4/input.txt");
        num_of_lines = std::count(std::istreambuf_iterator<char>(input_file),
                                  std::istreambuf_iterator<char>(), '\n');
    }
    std::ifstream input_file("../day4/input.txt");
    std::vector<uint32_t> cards(num_of_lines);
    std::fill(cards.begin(), cards.end(), 1);

    // parse line by line
    std::string line;
    uint32_t line_idx = 0;
    while (std::getline(input_file, line)) {
        // discard everything after the first colon
        auto col_pos = line.find(':') + 2;
        line = line.substr(col_pos, line.size() - col_pos);

        std::vector<uint32_t> winner_nums;
        std::vector<uint32_t> drawn_nums;
        std::string num_str;
        auto vec_to_use = &winner_nums;
        for (auto &ch: line) {
            switch (ch) {
                case ' ': {
                    if (num_str.empty())
                        break;
                    uint32_t num = std::stoi(num_str);
                    vec_to_use->push_back(num);
                    num_str = "";
                    break;
                }
                case '|':
                    vec_to_use = &drawn_nums;
                    break;
                default:
                    num_str += ch;
                    break;
            }
        }
        uint32_t num = std::stoi(num_str);
        vec_to_use->push_back(num);

        std::sort(winner_nums.begin(), winner_nums.end());
        std::sort(drawn_nums.begin(), drawn_nums.end());

        uint32_t points{0};
        for (const auto &wn: winner_nums) {
            bool found = std::binary_search(drawn_nums.begin(), drawn_nums.end(), wn);
            if (found) ++points;
        }

        auto current_card_count = cards[line_idx];
        line_idx++;
        for (size_t i = line_idx; i < points + line_idx; ++i) {
            cards[i] += current_card_count;
        }
    }

    std::cout << std::accumulate(cards.begin(),
                                 cards.end(),
                                 static_cast<unsigned long>(0)) << std::endl;
    return 0;
}