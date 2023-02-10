#include <iostream>
#include <chrono>
#include <cmath>

template <typename T>
class Timer {
public:
	Timer(): begin(std::chrono::steady_clock::now()) { }

	void stop() {
	    end = std::chrono::steady_clock::now();
        passed += end - begin;
	}

	void start() {
        begin = std::chrono::steady_clock::now();
	}

	void show() {
	    stop();
        T d = std::chrono::duration_cast<T>( passed );
        std::cout << d.count() << '\n';
	}


	void reset() {
        passed = std::chrono::duration<double>(0);
	}

	~Timer() {
	    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "Last interval" << std::endl;
		std::cout << "Delete timer" << '\n';
	}
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> passed;
};

int main() {
	auto count = 0.;
	{
	    std::cout << "Start timer" << '\n';
		Timer<std::chrono::microseconds> t;
		for (auto i = 0; i < 1'000'000; i++) {
			count += std::sin(i) + std::cos(i);
		}
		t.show();
		std::cout << "Stop timer" << '\n';
		std::cout << "Start working again" << '\n';
		t.start();
		for (auto i = 0; i < 1'000'000; i++) {
			count += std::sin(i) + std::cos(i);
		}
		t.show();
		std::cout << "Stop timer" << '\n';
		std::cout << "Reset timer" << '\n';
		t.reset();
		t.start();
		for (auto i = 0; i < 1'000'000; i++) {
			count += std::sin(i) + std::cos(i);
		}
		t.show();
	}
	std::cout << "After" << std::endl;
}
