#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <iostream>
#include <limits>

void print_vector(const std::vector<long> &vec) {
    for (auto &item: vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day6/input.txt");

    auto parse_line_as_one_number = [](const std::string &line) {
        std::string num_str{};
        for (auto &ch: line) {
            if (!std::isdigit(ch)) {
                continue;
            }
            num_str += ch;
        }
        return static_cast<long>(std::stol(num_str));
    };

    std::getline(input_file, input_str);
    long race_time = parse_line_as_one_number(input_str);
    std::getline(input_file, input_str);
    long race_distance = parse_line_as_one_number(input_str);

    long ways_to_win = 0;
    for (long j = 0; j < race_time + 1; ++j) {
        auto hold_time = j;
        auto distance_traveled = hold_time * (race_time - hold_time);
        if (distance_traveled > race_distance) {
            ways_to_win++;
        }
    }

    std::cout << ways_to_win << std::endl;
    return 0;
}