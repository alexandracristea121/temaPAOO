#include "../inc/hello.hpp"
#include <iostream>

int main() {
    hello::Hello hello; 

    hello.addMessage("Salut!");
    hello.addMessage("Ce mai faci?");
    hello.addMessage("La revedere!");

    std::cout << "Messages in hello:" << std::endl;
    hello.showMessages();


    hello::Message msg("Test message");
    hello::Message copyMsg = msg;  
    hello::Message movedMsg = std::move(copyMsg);  

    std::cout << "\nOriginal message: ";
    msg.display();

    std::cout << "\nMoved message: ";
    movedMsg.display();

/*
    hello::Hello helloCopy = hello;  -am interzis copierea 
    std::cout << '\n';
    std::cout << "Messages in helloCopy after copying hello:" << std::endl;
    helloCopy.showMessages();
*/
    return 0;
}