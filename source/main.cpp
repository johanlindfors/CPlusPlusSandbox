#include <cstdio>
#include <vector>

int main() {
    std::vector<int> numbers = { 0, 1, 2 , 3 , 4, 5};

    printf("Length of numbers: %zd\n", numbers.size());
    for(auto iter = numbers.begin(); iter != numbers.end();) {
        printf("%d", *iter);
        iter = numbers.erase(iter);
    }
    printf("\nLength of numbers: %zd\n", numbers.size());
    return 0;
}