#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

template<typename T>
void print_vector(const std::vector<T> &vec) {
    for (auto &item: vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

bool all_same(const std::string &str) {
    auto first_letter = str[0];
    return std::all_of(str.begin(), str.end(), [first_letter](const char &ch) {
        return ch == first_letter;
    });
}

long get_J_count(const std::string &str) {
    return std::count_if(str.begin(), str.end(),
                         [](char c) { return c == 'J'; });
}

bool is_five_kind(const std::string &str) {
    return all_same(str.substr(0, 5));
}

bool is_four_kind(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    return all_same(sorted_str.substr(0, 4)) || all_same(sorted_str.substr(1, 4));
}

bool is_full_house(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    return all_same(sorted_str.substr(0, 3)) && all_same(sorted_str.substr(3, 2)) ||
           all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(2, 3));
}

bool is_three_kind(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    return all_same(sorted_str.substr(0, 3)) || all_same(sorted_str.substr(1, 3)) ||
           all_same(sorted_str.substr(2, 3));
}

bool is_two_pair(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    return all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(2, 2)) ||
           all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(3, 2)) ||
           all_same(sorted_str.substr(1, 2)) && all_same(sorted_str.substr(3, 2));
}

bool is_one_pair(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    return all_same(sorted_str.substr(0, 2)) || all_same(sorted_str.substr(1, 2)) ||
           all_same(sorted_str.substr(2, 2)) || all_same(sorted_str.substr(3, 2));
}

auto char_to_int = std::map<char, int>{
        {'A', 14},
        {'K', 13},
        {'Q', 12},
        {'J', 11},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
};


int main() {
    // parse from file input.txt
    std::ifstream input_file("../day7/input.txt");

    std::string line;
    std::vector<std::pair<std::string, long>> hand_bid_map;
    while (std::getline(input_file, line)) {
        auto hand = line.substr(0, line.find_first_of(' '));
        auto bid = static_cast<long>(std::stol(line.substr(line.find_first_of(' ') + 1)));
        hand_bid_map.emplace_back(hand, bid);
    }

    // sort map by keys with a custom function
    std::sort(hand_bid_map.begin(), hand_bid_map.end(),
              [](const std::pair<std::string, long> &a,
                 const std::pair<std::string, long> &b) {

                  if (is_five_kind(a.first) && !is_five_kind(b.first)) {
                      return true;
                  } else if (!is_five_kind(a.first) && is_five_kind(b.first)) {
                      return false;
                  }

                  if (is_four_kind(a.first) && !is_four_kind(b.first)) {
                      return true;
                  } else if (!is_four_kind(a.first) && is_four_kind(b.first)) {
                      return false;
                  }

                  if (is_full_house(a.first) && !is_full_house(b.first)) {
                      return true;
                  } else if (!is_full_house(a.first) && is_full_house(b.first)) {
                      return false;
                  }

                  if (is_three_kind(a.first) && !is_three_kind(b.first)) {
                      return true;
                  } else if (!is_three_kind(a.first) && is_three_kind(b.first)) {
                      return false;
                  }

                  if (is_two_pair(a.first) && !is_two_pair(b.first)) {
                      return true;
                  } else if (!is_two_pair(a.first) && is_two_pair(b.first)) {
                      return false;
                  }

                  if (is_one_pair(a.first) && !is_one_pair(b.first)) {
                      return true;
                  } else if (!is_one_pair(a.first) && is_one_pair(b.first)) {
                      return false;
                  }

                  for (int i = 0; i < 5; ++i) {
                      int value_a = char_to_int[a.first[i]];
                      int value_b = char_to_int[b.first[i]];
                      if (value_a == value_b)
                          continue;
                      return value_a > value_b;
                  }

                  throw std::runtime_error("should never reach here");
              });

    long long total_win = 0;
    for (long i = static_cast<long>(hand_bid_map.size()) - 1; i >= 0; --i) {
        auto bid = hand_bid_map[i].second;
        auto multiplier = hand_bid_map.size() - i;
        total_win += bid * multiplier;
//        std::cout << bid << " " << multiplier << std::endl;
//        std::cout << hand_bid_map[i].first << " " << hand_bid_map[i].second << std::endl;
    }
    std::cout << total_win << std::endl;

    return 0;
}