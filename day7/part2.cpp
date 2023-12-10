#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>


std::map<char, long> char_count_set(const std::string &str) {
    std::map<char, long> char_count;
    for (auto &ch: str) {
        char_count[ch]++;
    }
    return char_count;
}

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

bool is_five_kind(const std::string &str) {
    if (all_same(str.substr(0, 5))) {
        return true;
    }

    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }

    return std::any_of(count_set.begin(), count_set.end(),
                       [js](const std::pair<char, long> &item) {
                           return (item.second == 5 - js) && (item.first != 'J');
                       });
}

bool is_four_kind(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    bool is = all_same(sorted_str.substr(0, 4)) || all_same(sorted_str.substr(1, 4));
    if (is) {
        return true;
    }

    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }

    return std::any_of(count_set.begin(), count_set.end(),
                       [js](const std::pair<char, long> &item) {
                           return (item.second == 4 - js) && (item.first != 'J');
                       });
}

bool is_full_house(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    bool is = all_same(sorted_str.substr(0, 3)) && all_same(sorted_str.substr(3, 2)) ||
              all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(2, 3));
    if (is) { return true; }

    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }

    if (js == 1) {
        // find 2 chars with count 2
        auto it = std::find_if(count_set.begin(), count_set.end(),
                               [](const std::pair<char, long> &item) {
                                   return item.second == 2 && (item.first != 'J');
                               });
        if (it == count_set.end()) { return false; }
        auto it2 = std::find_if(it++, count_set.end(),
                                [](const std::pair<char, long> &item) {
                                    return item.second == 2 && (item.first != 'J');
                                });
        if (it2 == count_set.end()) {
            return false;
        }
        return true;
    }

    if (js == 2) {
        // find 1 char with count 3
        auto it = std::find_if(count_set.begin(), count_set.end(),
                               [](const std::pair<char, long> &item) {
                                   return item.second == 3 && (item.first != 'J');
                               });
    }

    if (js == 3) {
        // find 1 char with count 2
        auto it = std::find_if(count_set.begin(), count_set.end(),
                               [](const std::pair<char, long> &item) {
                                   return item.second == 2 && (item.first != 'J');
                               });
        if (it == count_set.end()) { return false; }
        return true;
    }

    return false;
}

bool is_three_kind(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    bool is = all_same(sorted_str.substr(0, 3)) || all_same(sorted_str.substr(1, 3)) ||
              all_same(sorted_str.substr(2, 3));
    if (is) { return true; }

    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }

    return std::any_of(count_set.begin(), count_set.end(),
                       [js](const std::pair<char, long> &item) {
                           return (item.second == 3 - js) && (item.first != 'J');
                       });
}

bool is_two_pair(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    bool is = all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(2, 2)) ||
              all_same(sorted_str.substr(0, 2)) && all_same(sorted_str.substr(3, 2)) ||
              all_same(sorted_str.substr(1, 2)) && all_same(sorted_str.substr(3, 2));
    if (is) { return true; }

    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }

    if (js == 1 || js == 2) {
        // find 1 chars with count 2
        auto it = std::find_if(count_set.begin(), count_set.end(),
                               [](const std::pair<char, long> &item) {
                                   return item.second == 2 && (item.first != 'J');
                               });
        if (it == count_set.end()) { return false; }
        return true;
    }

    return false;
}

bool is_one_pair(const std::string &str) {
    std::string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    bool is = all_same(sorted_str.substr(0, 2)) || all_same(sorted_str.substr(1, 2)) ||
              all_same(sorted_str.substr(2, 2)) || all_same(sorted_str.substr(3, 2));
    auto count_set = char_count_set(str);
    auto js = count_set['J'];
    if (js == 0) { return false; }
    return true;
}

auto char_to_int = std::map<char, int>{
        {'A', 14},
        {'K', 13},
        {'Q', 12},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
        {'J', 1},
};

long get_kind(const std::string &str) {
    if (is_five_kind(str)) {
        return 9;
    } else if (is_four_kind(str)) {
        return 8;
    } else if (is_full_house(str)) {
        return 7;
    } else if (is_three_kind(str)) {
        return 6;
    } else if (is_two_pair(str)) {
        return 5;
    } else if (is_one_pair(str)) {
        return 4;
    } else {
        return 0;
    }
}

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

                  auto a_kind = get_kind(a.first);
                  auto b_kind = get_kind(b.first);

                  if (a_kind == b_kind) {
                      for (int i = 0; i < 5; ++i) {
                          int value_a = char_to_int[a.first[i]];
                          int value_b = char_to_int[b.first[i]];
                          if (value_a == value_b)
                              continue;
                          return value_a > value_b;
                      }
                  }

                  return a_kind > b_kind;

                  throw std::runtime_error("should never reach here");
              });

    long long total_win = 0;
    for (long i = static_cast<long>(hand_bid_map.size()) - 1; i >= 0; --i) {
        long long bid = hand_bid_map[i].second;
        long long multiplier = static_cast<long>(hand_bid_map.size()) - i;
        total_win += bid * multiplier;
        std::cout << hand_bid_map[i].first << " " << bid << " " << multiplier
                  << ' ' << get_kind(hand_bid_map[i].first) << std::endl;
    }
    std::cout << total_win << std::endl;

    return 0;
}