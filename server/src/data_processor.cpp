#include "data_processor.h"

std::vector<int> DataProcessor::extract_numbers(const std::string& string_data) {
 std::vector<int> numbers;
 int number = 0;
 int coef = 1;
 auto r_it = string_data.rbegin();
 while (r_it != string_data.rend()) {
  if (isdigit(*r_it)) {
   while (isdigit(*r_it)&&(r_it != string_data.rend())) {
    number = number + (coef*(*r_it - '0'));
    r_it++;
    coef = coef*10;
   }
   numbers.push_back(number);
   number = 0;
   coef = 1;
   continue;
  }
  r_it++;
 }
 return numbers;
}

std::string DataProcessor::process_data(char* data) {
 std::string output = "";
 std::string string_data(data);
 std::vector<int> numbers = extract_numbers(string_data);
 std::sort(numbers.begin(), numbers.end());
 int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
 for (auto i = numbers.begin(); i != numbers.end(); i++) {
  output = output + std::to_string(*i);
  output = output + ' ';
 }
 output = output + '\n';
 output = output + std::to_string(sum);
 return output;
}
