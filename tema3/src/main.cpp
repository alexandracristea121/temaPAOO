#include "../inc/hello.hpp"
#include <iostream>

int main() {
    hello::Hello hello;

    hello.addMessage("Salut!");
    hello.addMessage("Ce mai faci?");
    hello.addMessage("La revedere!");

    std::cout << "Messages in hello:" << std::endl;
    hello.showMessages();

    hello::Message msg1("Hello!");
    hello::Message msg2("World!");

    std::cout << "\nBefore assignment:" << std::endl;
    msg1.display();
    msg2.display();

    
    msg1 = msg2;
    std::cout << "\nAfter copy assignment (msg1 = msg2):" << std::endl;
    msg1.display();
    msg2.display();

  
    msg1 = hello::Message("New message!");
    std::cout << "\nAfter move assignment (msg1 = temporary):" << std::endl;
    msg1.display();

   
    std::cout << "\nTesting self-assignment for copy:" << std::endl;
    msg1 = msg1; 
    msg1.display();

    std::cout << "\nTesting self-assignment for move:" << std::endl;
    msg1 = std::move(msg1); 
    msg1.display();

    std::cout << "\n=== Testing Item 12: Copy all parts of an object ===" << std::endl;
    hello::Hello originalHello;
    originalHello.addMessage("Original Message 1");
    originalHello.addMessage("Original Message 2");

    std::cout << "Messages in originalHello before copy:" << std::endl;
    originalHello.showMessages();

    
    hello::Hello copiedHello = originalHello; 
    std::cout << "\nMessages in copiedHello (copied from originalHello):" << std::endl;
    copiedHello.showMessages();

    originalHello.addMessage("Original Message 3");
    std::cout << "\nMessages in originalHello after adding 'Original Message 3':" << std::endl;
    originalHello.showMessages();

    std::cout << "\nMessages in copiedHello after modifying originalHello:" << std::endl;
    copiedHello.showMessages(); 

    return 0;
}
