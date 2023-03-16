#include <thread>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <functional>
#include "json.hpp"

using steady_clock_t = std::chrono::steady_clock;

template <typename T>
class Timer {
public:

	Timer(): begin(steady_clock_t::now()) {}

	double gettime() {
        end = std::chrono::steady_clock::now();
        passed += end - begin;
        T d = std::chrono::duration_cast<T>( passed );
        return d.count();
	}

	~Timer() {
		//std::cout << message << ": " << std::chrono::duration_cast<T>(steady_clock_t::now() - begin).count() << std::endl;
	}
private:
    std::chrono::duration<double> passed = std::chrono::duration<double>(0);
	steady_clock_t::time_point begin;
	steady_clock_t::time_point end;
	std::string message;
};

template<typename Iter, typename T>
void accumulate_block(Iter begin, Iter end, T init, T& result) {
	result = std::accumulate(begin, end, init);
}

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init, unsigned int num_threads) {
	std::vector<std::thread> threads;
	std::vector<T> results(num_threads - 1);
	auto block_size = std::distance(begin, end) / num_threads;
	for (auto i = 0u; i + 1 < num_threads; i++) {
		threads.push_back(std::thread(
			accumulate_block<Iter, T>,
			std::next(begin, i * block_size),
			std::next(begin, (i + 1) * block_size),
			0,
			std::ref(results[i]))
		);
	}
	T last_result;
	accumulate_block(std::next(begin, (num_threads - 1) * block_size),
			end, init, last_result);
	std::for_each(std::begin(threads), std::end(threads), std::mem_fn(&std::thread::join));
	return std::accumulate(std::begin(results), std::end(results), last_result);
}

int main() {
	unsigned int size = 0;


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution d(1, 10);

	std::cin >> size;
	std::vector<long long int> randoms;

	std::generate_n(std::back_inserter(randoms), size, [&gen, &d](){return d(gen);});

	nlohmann::json jsonfile;
	unsigned int num_threads = std::thread::hardware_concurrency();
	jsonfile["num_of_threads"] = num_threads;
	for (unsigned int i = 1; i <= num_threads; i++) {
        double sum = 0;
        long long int result = 0;
        for (int j = 0; j < 1000; j++) {
            Timer<std::chrono::microseconds> t;
            result = parallel_accumulate(randoms.begin(), randoms.end(), 0, i);
            double time = t.gettime();
            sum += time;
        }
        jsonfile[std::to_string(i)] = sum / 1000;
        std::cout << "sum " << result << " number of threads " << i << " time: " << sum/1000 << std::endl;
	}
	std::ofstream file("times.json");
	file << jsonfile;
}
