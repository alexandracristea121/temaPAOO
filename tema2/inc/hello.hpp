#ifndef HELLO_HPP
#define HELLO_HPP

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

namespace hello {

class Message {
public:
    Message(const std::string& text);
    Message(const Message& other); 
    Message(Message&& other) noexcept; 
    ~Message();


    void display() const;
    const std::string& getText() const;
    const std::chrono::system_clock::time_point& getTime() const;

private:
    std::string* text;
    std::chrono::system_clock::time_point timeCreated; 
};

class Hello {
public:
//Item 6: Explicitly disallow the use of compiler generated functions you do not want
    Hello();
    Hello(const Hello& other) = delete; 
    Hello(Hello&& other) noexcept = delete;
    ~Hello();

    Hello& operator=(const Hello& other) = delete; 
    Hello& operator=(Hello&& other) noexcept = delete; 

    void addMessage(const std::string& message);
    void showMessages() const;
    void clearMessages();
    void removeMessage(const std::string& text);

private:
    std::vector<Message*> messages; 
};

} 

#endif 