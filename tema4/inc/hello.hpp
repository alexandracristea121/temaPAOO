#ifndef HELLO_HPP
#define HELLO_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>

namespace hello {

class Message {
public:
    explicit Message(const std::string& text);
    Message(const Message& other); 
    Message(Message&& other) noexcept;
    ~Message();

    Message& operator=(const Message& other); 
    Message& operator=(Message&& other) noexcept;

    void display() const;
    const std::string& getText() const;
    const std::chrono::system_clock::time_point& getTime() const;

private:
    std::unique_ptr<std::string> text; 
    std::chrono::system_clock::time_point timeCreated;
};

class Hello {
public:
    Hello();
    Hello(const Hello& other); 
    Hello(Hello&& other) noexcept; 
    ~Hello();

    Hello& operator=(const Hello& other); 
    Hello& operator=(Hello&& other) noexcept;

    void addMessage(const std::string& message);
    void showMessages() const;
    void clearMessages();
    void removeMessage(const std::string& text);

private:
    std::vector<std::unique_ptr<Message>> messages; 
};

} 

#endif
