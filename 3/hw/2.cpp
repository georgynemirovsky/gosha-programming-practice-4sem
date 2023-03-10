#include <iostream>
#include <regex>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> find_matches(const std::string& text, std::regex pattern) {
	std::vector<std::string> matches;
	std::transform(std::sregex_iterator(std::begin(text), std::end(text), pattern), std::sregex_iterator(), std::back_inserter(matches), [](auto match){return match.str();});
	return matches;
}


int main() {
    std::string text = "Hello shubhamg199630@gmail.com Rohit neeraj@gmail.com";

    std::cout << "Found matches" << std::endl;

	std::regex pattern(R"((\w+([\.-]?\w+)*@\w+([\.-]?\w+)*\.\w{2,4}))");

	auto matches = find_matches(text, pattern);

	std::copy(std::begin(matches), std::end(matches), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
