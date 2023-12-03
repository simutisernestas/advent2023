#include <fstream>
#include <iostream>

int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day2/input.txt");
    // put full file in the input string
    input_str = std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());

    std::cout << input_str << std::endl;

    uint64_t power_sum = 0;

    size_t parse_pos = 0;
    uint8_t max_blue = 0;
    uint8_t max_green = 0;
    uint8_t max_red = 0;
    while (true) {
        if (parse_pos >= input_str.size())
            break;

        switch (input_str[parse_pos]) {
            case ' ':
            case ':':
            case ';':
            case ',':
                parse_pos++;
                break;
            case '\n':
                power_sum += (max_blue * max_green * max_red);
                // TODO: reset
                max_blue = 0;
                max_green = 0;
                max_red = 0;
                parse_pos++;
                break;
            case 'G':
                while (input_str[parse_pos] != ':') {
                    parse_pos++;
                }
                break;
            default:
                if (!std::isdigit(input_str[parse_pos])) {
                    parse_pos++;
                    break;
                }

                std::string count_string{};
                while (std::isdigit(input_str[parse_pos])) {
                    count_string += input_str[parse_pos];
                    parse_pos++;
                }
                uint8_t count = std::stoi(count_string);

                parse_pos++;
                if (input_str[parse_pos] == 'b') {
                    max_blue = std::max(max_blue, count);
                }
                if (input_str[parse_pos] == 'g') {
                    max_green = std::max(max_green, count);
                }
                if (input_str[parse_pos] == 'r') {
                    max_red = std::max(max_red, count);
                }
                break;
        }
    }

    std::cout << "Possible count: " << power_sum << std::endl;
}