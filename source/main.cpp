#include <cstdio>
#include <vector>
#include <string>
#include <filesystem>


int main() {
    // std::vector<int> numbers = { 0, 1, 2 , 3 , 4, 5};

    // printf("Length of numbers: %zd\n", numbers.size());
    // for(auto iter = numbers.begin(); iter != numbers.end();) {
    //     printf("%d", *iter);
    //     iter = numbers.erase(iter);
    // }
    // printf("\nLength of numbers: %zd\n", numbers.size());
    std::string current_working_dir(std::filesystem::current_path().generic_string());
    printf(current_working_dir.c_str());
    return 0;
}