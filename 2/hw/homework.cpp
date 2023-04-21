#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
    for (auto item : v) {
        os << item << ' ';
    }
    return os;
}

bool is_prime (int value) {
    double tmp = (double) value;
    int v = (int) floor(sqrt(tmp));
    for (int i = 2; i <= v; i++) {
        if (value % i == 0) {
            return false;
        }
    }
    return true;
}

bool less_then (int i) { return (i < 0); }

#define range(container) std::begin(container), std::end(container)

int main() {
    std::vector<int> P1;
    for (int i = 1; i < 11; i++) {
        P1.insert(std::end(P1), i);
    }
    std::cout << "ex1: " << P1 << std::endl;


    int n = 0;
    std::cout << "how many numbers do you want to insert? ";
    std::cin >> n;
    int a = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        P1.push_back(a);
    }
    std::cout << "ex2: " << P1 << std::endl;


    std::random_device d;
    std::mt19937_64 mt(d());
    std::uniform_int_distribution<int> distribution(0, P1.size() - 1);
    std::uniform_int_distribution<int> distribution2(0, 100);

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

    int num = 0;
    for (auto it : P1) {
        if (it % 2 == 1) {
            num++;
        }
    }
    std::cout << "ex5: " << num << std::endl;


    std::cout << "ex6: " << *(std::min_element(range(P1))) << " " << *(std::max_element(range(P1))) << std::endl;


    std::vector<int> prime_numbers;
    for (auto it : P1) {
        if (is_prime(it)) {
            prime_numbers.push_back(it);
        }
    }
    std::sort(range(prime_numbers));
    std::cout << "ex7: " << prime_numbers << std::endl;


    std::transform(std::begin(P1), std::end(P1), std::begin(P1), [](auto item) {
                                                                                return item * item;
                                                                                });
    std::cout << "ex8: " << P1 << std::endl;


    std::vector<int> P2;
    for (int i = 0; i < P1.size(); i++) {
        auto random_number = distribution2(mt);
        P2.push_back(random_number);
    }
    std::cout << "ex9: " << P2 << std::endl;


    std::cout << "ex10: " << std::accumulate(range(P2), 0) << std::endl;


    std::cout << "How much elements you want change? Number of elements: " << P2.size() << std::endl;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        P2.at(i) = 1;
    }
    std::cout << "ex11: " << P2 << std::endl;


    std::vector<int> P3;
    for (int i = 0; i < P1.size(); i++) {
        P3.push_back(P2.at(i) - P1.at(i));
    }
    std::cout << "ex12: " << P3 << std::endl;

    std::replace_if(P3.begin(), P3.end(), less_then, 0);
    std::cout << "ex13: " << P3 << std::endl;

    std::transform(range(P3), std::begin(P3), [](auto item){if (item < 0) {return 0;} else {return item;}});
    std::cout << "ex14: " << P3 << std::endl;


    std::vector<int> other;
    std::reverse_copy(std::begin(P3), std::end(P3), std::back_inserter(other));
    P3 = other;
    std::cout << "ex15: " << P3 << std::endl;


    int m1 = 0, m2 = 0, m3 = 0;
    for (auto it : P3) {
        if (it >= m1) {
            m3 = m2;
            m2 = m1;
            m1 = it;
        } else if (it >= m2) {
            m3 = m2;
            m2 = it;
        } else if (it >= m3) {
            m3 = it;
        }
    }
    std::cout << "ex16: " << m3 << ' ' << m2 << ' ' << m1 << std::endl;


    std::sort(range(P1));
    std::sort(range(P2));
    std::cout << "ex17:" << std::endl << "P1: " << P1 << std::endl << "P2: " << P2 << std::endl;


    std::vector<int> P4;
    std::copy(P1.begin(), P1.end(), std::back_inserter(P4));
    std::copy(P2.begin(), P2.end(), std::back_inserter(P4));
    std::sort(range(P4));
    std::cout << "ex18: " << P4 << std::endl;


    int i = 0;
    while ((P4.at(i) <= 1) && (i < P4.size())) {
        i++;
    }
    std::cout << "ex19: Maximum possible index: " << i << std::endl;


    std::cout << "ex20: " << std::endl <<
    "P1: " << P1 << std::endl <<
    "P2: " << P2 << std::endl <<
    "P3: " << P3 << std::endl <<
    "P4: " << P4 << std::endl;


    return 0;
}
