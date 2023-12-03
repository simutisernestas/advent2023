#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day3/input.txt");
    // put full file in the input string
    input_str = std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());

    // make a char table from input
    auto input_cols = input_str.find('\n');
    auto input_rows = input_str.size() / input_cols - 1;
    input_str.erase(std::remove(input_str.begin(), input_str.end(), '\n'), input_str.cend());
    char input_table[input_rows][input_cols];
    for (size_t i = 0; i < input_rows; i++) {
        for (size_t j = 0; j < input_cols; j++) {
            input_table[i][j] = input_str[i * input_cols + j];
        }
    }

    uint64_t sum_of_part_nums = 0;
    auto is_valid_index = [&](int i, int j) {
        return i >= 0 && i < input_rows && j >= 0 && j < input_cols;
    };
    std::string num_str{};
    std::pair<int, int> latest_star_idx = {-1, -1};
    std::map<std::pair<int, int>, uint64_t> star_nums;
    for (int i = 0; i < input_rows; ++i) {
        for (int j = 0; j < input_cols; ++j) {
            if (std::isdigit(input_table[i][j])) {
                num_str += input_table[i][j];
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        if (k == 0 && l == 0)
                            continue;
                        if (!is_valid_index(i + k, j + l))
                            continue;

                        char el = input_table[i + k][j + l];
                        if (el == '*') {
                            latest_star_idx = {i + k, j + l};
                        }
                    }
                }
            } else {
                if (!num_str.empty()) {
                    bool is_star_found = latest_star_idx != std::pair<int, int>{-1, -1};
                    bool is_star_seen_by_other_gear = star_nums.count(latest_star_idx) > 0;
                    if (is_star_found && is_star_seen_by_other_gear) {
                        sum_of_part_nums += std::stoi(num_str) * star_nums[latest_star_idx];
                    }
                    if (is_star_found) {
                        star_nums[latest_star_idx] = std::stoi(num_str);
                    }
                    num_str = "";
                    latest_star_idx = {-1, -1};
                }
            }
        }
    }

    std::cout << sum_of_part_nums << std::endl;
    return 0;
}