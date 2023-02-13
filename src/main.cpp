#include <iostream>
#include <map>
#include <asio.hpp>

int main() {
    asio::thread_pool tp{1};
    // auto ex = asio::make_strand(tp);
    auto ex = tp.executor();

    asio::post(ex, []() {
        std::cout << "From TP 1" << std::endl;
    });
    asio::post(ex, []() {
        std::cout << "From TP 2" << std::endl;
    });
    asio::post(ex, []() {
        std::cout << "From TP 3" << std::endl;
    });
    asio::post(ex, []() {
        std::cout << "From TP 4" << std::endl;
    });

    tp.join();

    return 0;
}
