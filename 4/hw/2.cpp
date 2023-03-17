#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <future>

template<typename Iter, typename Func>
int block_for_each(Iter begin, Iter end, Func f) {
    std::for_each(begin, end, f);
}
template<typename Iter, typename Func>
void parallel_for_each (Iter begin, Iter end, Func f) {
    auto num_threads = std::thread::hardware_concurrency();
    auto block_size = std::distance(begin, end) / num_threads;
    std::vector<std::future<int>> futures;
    for (auto i = 0u; i + 1 < num_threads; i++) {
        futures.push_back(std::async(std::launch::async, &block_for_each<Iter, Func>, std::next(begin, i * block_size), std::next(begin, (i + 1) * block_size), f));
    }
    futures.push_back(std::async(std::launch::async, &block_for_each<Iter, Func>, std::next(begin, (num_threads - 1) * block_size), end, f));
}

int main() {
    int size = 0;
    std::cin >> size;
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), 1);
    parallel_for_each(std::begin(v), std::end(v), [](int &it){it *= it;});
    for (int it : v) {
        std::cout << it << " ";
    }
    return 0;
}
