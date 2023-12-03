#include <fstream>
#include <iostream>

#define MAX_BLUE_COUNT 14
#define MAX_GREEN_COUNT 13
#define MAX_RED_COUNT 12

bool is_too_many_blues(uint8_t blue_count) {
    return blue_count > MAX_BLUE_COUNT;
}

bool is_too_many_greens(uint8_t green_count) {
    return green_count > MAX_GREEN_COUNT;
}

bool is_too_many_reds(uint8_t red_count) {
    return red_count > MAX_RED_COUNT;
}

int main() {
    std::string input_str;
    // parse from file input.txt
    std::ifstream input_file("../day2/input.txt");
    // put full file in the input string
    input_str = std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());

    std::cout << input_str << std::endl;

    uint64_t possible_sum = 0;

    size_t parse_pos = 0;
    bool is_current_possible = true;
    std::string game_id = "";
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
                if (is_current_possible)
                    possible_sum += std::stoi(game_id);
                // reset
                parse_pos++;
                is_current_possible = true;
                game_id = "";
                break;
            case 'G':
                while (input_str[parse_pos] != ':') {
                    if (std::isdigit(input_str[parse_pos]))
                        game_id += input_str[parse_pos];
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
                if (input_str[parse_pos] == 'b' && is_too_many_blues(count)) {
                    is_current_possible = false;
                }
                if (input_str[parse_pos] == 'g' && is_too_many_greens(count)) {
                    is_current_possible = false;
                }
                if (input_str[parse_pos] == 'r' && is_too_many_reds(count)) {
                    is_current_possible = false;
                }
                break;
        }
    }

    std::cout << "Possible count: " << possible_sum << std::endl;
}