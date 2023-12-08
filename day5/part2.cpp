#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <iostream>
#include <limits>
#include <algorithm>

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


int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day5/input.txt");

    // parse line by line
    std::string line;
    std::vector<long> seeds;

    typedef std::array<long, 3> arr3;
    std::map<std::string, std::vector<arr3>> maps;
    while (std::getline(input_file, line)) {
        if (line.substr(0, 5) == "seeds") {
            space_sep_string_to_vector(line.substr(7, line.size() - 7), seeds);
        }

        auto map_pos = line.find("map");
        if (map_pos != std::string::npos) {
            // string until map_pos - 1
            auto key = line.substr(0, map_pos - 1);
            std::string values_line;
            while (std::getline(input_file, values_line)) {
                if (values_line.empty())
                    break;
                std::vector<long> values;
                space_sep_string_to_vector(values_line, values);
                maps[key].push_back({values[0], values[1], values[2]});
            }
        }
    }

    long lowest_location = std::numeric_limits<long>::max();
    std::vector<std::string> order_of_iter = {"seed-to-soil",
                                              "soil-to-fertilizer",
                                              "fertilizer-to-water",
                                              "water-to-light",
                                              "light-to-temperature",
                                              "temperature-to-humidity",
                                              "humidity-to-location"};
    std::reverse(order_of_iter.begin(), order_of_iter.end());
    long location = 0;
    uint8_t found = 0;
    long step = 100000;
    while (true) {
        long pre_entity = location;
        for (const auto &map: order_of_iter) {
            long an_entity = 0;
            // map seed to soil
            for (const auto &range: maps[map]) {
                auto destination_range_start = range[1];
                auto source_range_start = range[0];
                auto distance = range[2];

                if (pre_entity >= source_range_start && pre_entity < source_range_start + distance) {
                    long diff = (destination_range_start - source_range_start);
                    an_entity = pre_entity + diff;
                    break;
                } else {
                    an_entity = pre_entity;
                }
            }
            pre_entity = an_entity;
        }

        // check if it falls in the range of seeds
        for (size_t i = 0; i < seeds.size() - 1; i += 2) {
            auto s1 = seeds[i];
            auto s2 = seeds[i + 1];
            if (pre_entity >= s1 && pre_entity <= s1 + s2) {
                found++;
            }
        }

        if (found == 1 && step != 1) {
            std::cout << "found 1: " << location << "\n";
            location -= step;
            step = 1;
        } else if (found == 2) {
            break;
        }

        location += step;
    }

    std::cout << "location: " << location << "\n";
    return 0;
}