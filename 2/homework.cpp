#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
    for (auto item : v) {
        os << item << ' ';
    }
    return os;
}

#define range(container) std::begin(container), std::end(container)

int main() {
    std::vector<int> P1;
    for (int i = 1; i < 11; i++) {
        P1.insert(std::end(P1), i);
    }
    std::cout << "ex1: " << P1 << std::endl;


    int a = 0;
    std::cin >> a;
    P1.insert(std::end(P1), a);
    std::cin >> a;
    P1.insert(std::end(P1), a);
    std::cout << "ex2: " << P1 << std::endl;


    std::random_device d;
    std::mt19937_64 mt(d());
    std::uniform_int_distribution<int> distribution(0, P1.size() - 1);

    for (int i = 0; i < 100; i++) {
        int random_ind1 = distribution(mt);
        int random_ind2 = distribution(mt);
        std::swap(P1.at(random_ind1), P1.at(random_ind2));
    }
    std::cout << "ex3: " << P1 << std::endl;

    auto end = std::end(P1);
    for (auto it = std::begin(P1); it != end; it++) {
        end = std::remove(it + 1, end, *it);
    }
    P1.erase(end, std::end(P1));
    std::cout << "ex4: " << P1 << std::endl;


    return 0;
}
