#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day4/input.txt");

    // parse line by line
    std::string line;
    uint32_t g_points = 0;
    while (std::getline(input_file, line)) {
        // discard everything after the first colon
        auto col_pos = line.find(':') + 2;
        line = line.substr(col_pos, line.size() - col_pos);
        std::cout << line << std::endl;

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
            if (found) points = points == 0 ? 1 : points * 2;
        }

        g_points += points;
    }

    std::cout << g_points << std::endl;
    return 0;
}