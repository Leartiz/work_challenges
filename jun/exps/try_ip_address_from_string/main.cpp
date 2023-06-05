#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

int main()
{
    // okk
    {
        try {
            const auto ip = boost::asio::ip::address::from_string("127.0.0.1");
            std::cout << ip << std::endl;
        }
        catch(std::runtime_error& err) {
            std::cerr << "rtm err: " << err.what() << std::endl;
        }
    }
    {
        try {
            const auto ip = boost::asio::ip::address::from_string("0.0.0.0");
            std::cout << ip << std::endl;
        }
        catch(std::runtime_error& err) {
            std::cerr << "rtm err: " << err.what() << std::endl;
        }
    }

    {
        using namespace boost::asio::ip;
        const auto lhs = tcp::endpoint(address::from_string("0.0.0.0"), 11111);
        const auto rhs = tcp::endpoint(tcp::v4(), 11111);

        // ***

        std::cout << "lhs: " << lhs << std::endl;
        std::cout << "rhs: " << lhs << std::endl;
        std::cout << "lhs == rhs: " << (lhs == rhs) << std::endl;
    }

    std::cout << std::endl;

    // err
    {
        try {
            const auto ip = boost::asio::ip::address::from_string("my.domain.com");
            std::cout << ip << std::endl;
        }
        catch(std::runtime_error& err) {
            std::cerr << "rtm err: " << err.what() << std::endl;
        }
    }

    {
        try {
            const auto ip = boost::asio::ip::address::from_string("127.0.0.1.1");
            std::cout << ip << std::endl;
        }
        catch(std::runtime_error& err) {
            std::cerr << "rtm err: " << err.what() << std::endl;
        }
    }

    {
        try {
            const auto ip = boost::asio::ip::address::from_string("128.128.128.555");
            std::cout << ip << std::endl;
        }
        catch(std::runtime_error& err) {
            std::cerr << "rtm err: " << err.what() << std::endl;
        }
        catch(std::exception& err) {
            std::cerr << "err: " << err.what() << std::endl;
        }
    }

    return 0;
}
