#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>

int main() {
    std::string input_str = "1abc2\n"
                            "pqr3stu8vwx\n"
                            "a1b2c3d4e5f\n"
                            "treb7uchet\n";
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

        // check if found digits
        if (first_digit != substr_of_current_line.end() && last_digit != substr_of_current_line.rend()) {
            // concatenate digits in string
            std::string digits_str;
            digits_str += *first_digit;
            digits_str += *last_digit;
            // convert to int
            int digits = std::stoi(digits_str);
            // save to table
            table_of_digits[i] = digits;
        } else {
            // save zero to table
            table_of_digits[i] = 0;
        }
        input_str = input_str.substr(input_str.find('\n') + 1);
    }

    // output sum
    auto sum = std::accumulate(table_of_digits.begin(), table_of_digits.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
