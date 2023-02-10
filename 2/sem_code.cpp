#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <chrono>
#include <random>


class Timer {
public:
	Timer(): start(std::chrono::steady_clock::now()) {}

	~Timer() {
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
	}
private:
	std::chrono::steady_clock::time_point start;
};

int main() {
    std::array<int, 5> arr;
    arr[2] = 42;

    for (auto item: arr) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    std::vector<int> vector;
    std::deque<int> deque;
    {
        Timer t;
        for (auto i = 0; i < 1'000; i++) {
            vector.insert(std::begin(vector), i);
        }
    }
    {
        Timer t;
        for (auto i = 0; i < 1'000; i++) {
            deque.push_back(i);
        }
    }

    std::random_device d;
    std::mt19937_64 mt(d());
    std::uniform_int_distribution<int> distribution(1, 10);
    for (auto i = 0; i < 10; i++) {
        std:: cout << distribution(mt) << ' ';
    }
    std::cout << std::endl;
    return 0;
}
