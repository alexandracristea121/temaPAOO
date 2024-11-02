#include "../inc/hello.hpp"
#include <iostream>

int main() {
    hello::Hello hello; 

    hello.addMessage("Salut!");
    hello.addMessage("Ce mai faci?");
    hello.addMessage("La revedere!");

    std::cout << "Messages in hello:" << std::endl;
    hello.showMessages();

    hello::Hello helloCopy = hello;
    std::cout << '\n';
    std::cout << "Messages in helloCopy after copying hello:" << std::endl;
    helloCopy.showMessages();

    hello::Hello helloMoved = std::move(hello);
    std::cout << '\n';
    std::cout << "Messages in helloMoved after moving hello:" << std::endl;
    helloMoved.showMessages();

    std::cout << '\n';
    std::cout << "Messages in hello after move:" << std::endl;
    hello.showMessages();
    std::cout << '\n';

    helloMoved.removeMessage("Ce mai faci?");
    std::cout << '\n';
    std::cout << "Messages in helloMoved after removing a message:" << std::endl;
    helloMoved.showMessages();

    helloMoved.clearMessages();

    return 0;
}