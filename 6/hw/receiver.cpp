#include <iostream>
#include <vector>
#include <iterator>
#include <thread>
#include <boost/asio.hpp>

bool output(boost::asio::ip::tcp::socket& s, std::string& message) {
    std::string mess;
    do {
        boost::asio::streambuf buffer;

        boost::asio::read_until(s, buffer, '\n');

        std::istream stream(&buffer);

        std::getline(stream, mess);

        if (mess != message) {
            std::cout << mess << std::endl;
            message = mess;
        }
    } while (message != "EXIT");
    return true;
}

bool enter(boost::asio::ip::tcp::socket& s, std::string& message, std::string& message_serv) {
    do {
        std::getline(std::cin, message_serv);
        boost::asio::write(s, boost::asio::buffer(message_serv + "\n"));
    } while (message != "EXIT");
    return (message == "EXIT");
}

int main() {
	auto port = 9999;
	std::string ip = "127.0.0.1";

	boost::asio::ip::tcp::endpoint e(boost::asio::ip::address::from_string(ip), port);

	boost::asio::io_service serv;

	boost::asio::ip::tcp::acceptor a(serv, e.protocol());
	a.bind(e);
	a.listen();

	boost::asio::ip::tcp::socket s(serv);
	a.accept(s);

	std::string message;
	std::string message_serv;

	std::thread t1(
        &enter,
        std::ref(s),
        std::ref(message),
        std::ref(message_serv)
    );

	output(s, message);


    t1.join();

}
