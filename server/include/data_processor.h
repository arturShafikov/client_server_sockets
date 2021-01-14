#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class DataProcessor {
public:
 std::string process_data(char* data);
private:
 std::vector<int> extract_numbers(const std::string& string_data);
};

#endif
