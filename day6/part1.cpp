#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <iostream>
#include <limits>

void space_sep_string_to_vector(const std::string str, std::vector<long> &vec) {
    std::string num_str;
    for (auto &ch: str) {
        if (ch == ' ') {
            vec.push_back(static_cast<long>(std::stol(num_str)));
            num_str = "";
        } else {
            num_str += ch;
        }
    }
    vec.push_back(static_cast<long>(std::stol(num_str)));
}

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

    auto parse_line = [](const std::string &line) {
        std::vector<long> vec;
        auto index_of_first_digit = line.find_first_of("0123456789");
        while (index_of_first_digit != std::string::npos) {
            auto index_of_space = line.find_first_of(' ', index_of_first_digit);
            vec.push_back(static_cast<long>(std::stol(
                    line.substr(index_of_first_digit, index_of_space - index_of_first_digit))));
            index_of_first_digit = line.find_first_of("0123456789", index_of_space);
        }
        return vec;
    };

    std::getline(input_file, input_str);
    std::vector<long> times = parse_line(input_str);
    std::getline(input_file, input_str);
    std::vector<long> distances = parse_line(input_str);

    print_vector(times);
    print_vector(distances);

    long ways_to_win_race_product = 1;
    for (long i = 0; i < times.size(); ++i) {
        auto race_time = times[i];
        auto race_distance = distances[i];

        long ways_to_win = 0;
        for (long j = 0; j < race_time + 1; ++j) {
            auto hold_time = j;
            auto distance_traveled = hold_time * (race_time - hold_time);
            if (distance_traveled > race_distance) {
                ways_to_win++;
            }
        }

        if (ways_to_win != 0)
            ways_to_win_race_product *= ways_to_win;
        std::cout << ways_to_win << std::endl;
    }

    std::cout << ways_to_win_race_product << std::endl;
    return 0;
}