#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <array>
#include <limits>

int main() {
    std::string input_str = "two1Xnine\n"
                            "eightwothree\n"
                            "abcone2threexyz\n"
                            "xtwone3four\n"
                            "4nineeightseven2\n"
                            "zoneight234\n"
                            "7pqrstsixteen\n";

    auto digit_strings = std::array<std::string, 9>{"one", "two", "three", "four", "five",
                                                    "six", "seven", "eight", "nine"};

    // parse from file input.txt
    std::ifstream input_file("../day1/input.txt");
    // put full file in the input string
    input_str = std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());

    long new_line_count = std::count(input_str.begin(), input_str.end(), '\n');
    std::vector<uint8_t> table_of_digits(new_line_count, 0);

    // for each line
    for (int i = 0; i < new_line_count; ++i) {
        auto substr_of_current_line = input_str.substr(0, input_str.find('\n'));

        // find first digit
        auto first_digit = std::find_if(substr_of_current_line.begin(), substr_of_current_line.end(), [](char c) {
            return std::isdigit(c);
        });
        // find last digit
        auto last_digit = std::find_if(substr_of_current_line.rbegin(), substr_of_current_line.rend(), [](char c) {
            return std::isdigit(c);
        });

        // for all string digits find their indeces
        std::array<size_t, 9> indeces_of_digits_from_the_front{};
        std::array<size_t, 9> indeces_of_digits_from_the_back{};
        for (int j = 0; j < 9; ++j) {
            std::string ds_sub = digit_strings[j];
            auto first_digit_sub = substr_of_current_line.find(ds_sub);
            if (first_digit_sub != std::string::npos) {
                indeces_of_digits_from_the_front[j] = first_digit_sub;
            } else {
                indeces_of_digits_from_the_front[j] = std::numeric_limits<size_t>::max();
            }

            auto last_digit_sub = substr_of_current_line.rfind(ds_sub);
            if (last_digit_sub != std::string::npos) {
                indeces_of_digits_from_the_back[j] = last_digit_sub;
            } else {
                indeces_of_digits_from_the_back[j] = 0;
            }
        }
        auto min_el_front = *std::min_element(indeces_of_digits_from_the_front.begin(),
                                              indeces_of_digits_from_the_front.end());
        auto max_el_back = *std::max_element(indeces_of_digits_from_the_back.begin(),
                                             indeces_of_digits_from_the_back.end());

        // check if these are less/greater than the first/last digit indices
        auto front_digit_idx = std::distance(substr_of_current_line.begin(), first_digit);
        auto back_digit_idx = std::distance(substr_of_current_line.rbegin(), last_digit);
        // convert back index to normal
        back_digit_idx = substr_of_current_line.size() - back_digit_idx - 1;

        std::string final_digit_str;

        if (min_el_front < front_digit_idx || front_digit_idx == std::string::npos) {
            // find the digit
            auto min_front = std::distance(indeces_of_digits_from_the_front.begin(),
                                           std::min_element(indeces_of_digits_from_the_front.begin(),
                                                            indeces_of_digits_from_the_front.end()));
            // save to table
            final_digit_str += std::to_string(min_front + 1);
        } else {
            final_digit_str += *first_digit;
        }

        if (max_el_back > back_digit_idx || back_digit_idx == std::string::npos) {
            // find the digit
            auto max_back = std::distance(indeces_of_digits_from_the_back.begin(),
                                          std::max_element(indeces_of_digits_from_the_back.begin(),
                                                           indeces_of_digits_from_the_back.end()));
            // save to table
            final_digit_str += std::to_string(max_back + 1);
        } else {
            final_digit_str += *last_digit;
        }

        table_of_digits[i] = std::stoi(final_digit_str);
        input_str = input_str.substr(input_str.find('\n') + 1);
    }

    // output sum
    auto sum = std::accumulate(table_of_digits.begin(), table_of_digits.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
