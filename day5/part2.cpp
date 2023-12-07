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
    for (size_t i = 0; i < seeds.size() - 1; i += 2) {
        auto s1 = seeds[i];
        auto s2 = seeds[i + 1];

        for (long seed = s1; seed <= s1 + s2; ++seed) {
            long pre_entity = seed;
            for (const auto &map: order_of_iter) {
                long an_entity = 0;
                // map seed to soil
                for (const auto &range: maps[map]) {
                    auto destination_range_start = range[0];
                    auto source_range_start = range[1];
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

            if (pre_entity < lowest_location) {
                lowest_location = pre_entity;
            }
        }

        std::cout << "iter" << i << "\n";
    }

    std::cout << "\nlocation: " << lowest_location << "\n";
    return 0;
}