#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


#define ever (;;)
#define range(container) std::begin(container), std::end(container)

std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
    for (auto item : v) {
        os << item << ' ';
    }
    return os;
}

int main() {
    std::vector<int> array;

    for (auto i = 0; i < 10;) {
        array.push_back(i++);
    }

    std::cout << array << std::endl;

    std::vector<int> other;

    std::reverse_copy(std::begin(array), std::end(array), std::back_inserter(other));

    std::cout << other << std::endl;

    std::vector<int> squares;

    std::transform(std::begin(array), std::end(array), std::back_inserter(squares), [](auto item) {
                                                                                       return item * item;
                                                                                       });
    std::cout << squares << std::endl;

    auto remove_from = std::remove_if(range(squares), [](auto item){return item % 2;});
    squares.erase(remove_from, std::end(squares));

    std::cout << squares << std::endl;

    std::cout << "sum of filtered squares:" << std::accumulate(range(squares), 0) << std::endl;
    return 0;
}
