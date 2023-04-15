#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <iterator>

bool output(boost::asio::ip::tcp::socket& s, std::string& message) {
    std::string mess;
    while (message != "EXIT") {
        boost::asio::streambuf buffer;

        boost::asio::read_until(s, buffer, '\n');

        std::istream stream(&buffer);

        std::getline(stream, mess);

        if (mess != message) {
            std::cout << mess << std::endl;
            message = mess;
        }
    }
    return true;
}

bool enter(boost::asio::ip::tcp::socket& s, std::string& message) {
    while (message != "EXIT") {
        std::getline(std::cin, message);
        boost::asio::write(s, boost::asio::buffer(message + "\n"));
    }
    return (message == "EXIT");
}

int main() {
	auto port = 9999;
	std::string ip = "127.0.0.1";

	boost::asio::ip::tcp::endpoint e(
			boost::asio::ip::address::from_string(ip), port);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket s(io_service, e.protocol());

	s.connect(e);
	std::string message = "Connected!";
	std::string message_serv;

	boost::asio::write(s, boost::asio::buffer(message + "\n"));

	std::thread t1(
        &enter,
        std::ref(s),
        std::ref(message)
    );

	std::thread t2(
        &output,
        std::ref(s),
        std::ref(message_serv)
    );

	t1.join();
	t2.join();

    boost::asio::write(s, boost::asio::buffer("EXIT\n"));
}
