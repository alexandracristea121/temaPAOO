#include "../inc/hello.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>


hello::Message::Message(const std::string& text) 
    : text(std::make_unique<std::string>(text)), timeCreated(std::chrono::system_clock::now()) {
}

hello::Message::Message(const Message& other) 
    : text(std::make_unique<std::string>(*other.text)), timeCreated(other.timeCreated) {
}

hello::Message::Message(Message&& other) noexcept 
    : text(std::move(other.text)), timeCreated(other.timeCreated) { 
}

hello::Message::~Message() = default;

hello::Message& hello::Message::operator=(const Message& other) {
    if (this != &other) {
        text = std::make_unique<std::string>(*other.text); 
        timeCreated = other.timeCreated;
    }
    return *this;
}

hello::Message& hello::Message::operator=(Message&& other) noexcept {
    if (this != &other) {
        text = std::move(other.text);
        timeCreated = other.timeCreated;
    }
    return *this;
}

void hello::Message::display() const {
    auto now_c = std::chrono::system_clock::to_time_t(timeCreated);
    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(timeCreated);
    auto ns = now_ns.time_since_epoch().count() % 1000000000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << '.' 
        << std::setw(9) << std::setfill('0') << ns;
    std::cout << *text << " (Created at: " << oss.str() << ")" << std::endl;
}

const std::string& hello::Message::getText() const {
    return *text;
}

const std::chrono::system_clock::time_point& hello::Message::getTime() const {
    return timeCreated;
}


hello::Hello::Hello() = default;

hello::Hello::Hello(const Hello& other) {
    for (const auto& msg : other.messages) {
        messages.push_back(std::make_unique<Message>(*msg)); 
    }
}

hello::Hello::Hello(Hello&& other) noexcept 
    : messages(std::move(other.messages)) { 
}

hello::Hello::~Hello() = default;

hello::Hello& hello::Hello::operator=(const Hello& other) {
    if (this != &other) {
        clearMessages();
        for (const auto& msg : other.messages) {
            messages.push_back(std::make_unique<Message>(*msg)); 
        }
    }
    return *this;
}

hello::Hello& hello::Hello::operator=(Hello&& other) noexcept {
    if (this != &other) {
        clearMessages();
        messages = std::move(other.messages); 
    }
    return *this;
}

void hello::Hello::addMessage(const std::string& message) {
    messages.push_back(std::make_unique<Message>(message)); 
}

void hello::Hello::showMessages() const {
    if (messages.empty()) {
        std::cout << "No messages." << std::endl;
        return;
    }

    std::cout << "Messages: " << std::endl;
    for (const auto& msg : messages) {
        msg->display();
    }
}

void hello::Hello::clearMessages() {
    messages.clear(); 
}

void hello::Hello::removeMessage(const std::string& text) {
    auto it = std::remove_if(messages.begin(), messages.end(), [&](const std::unique_ptr<Message>& msg) {
        return msg->getText() == text;
    });

    if (it != messages.end()) {
        messages.erase(it, messages.end());
        std::cout << "Message '" << text << "' removed." << std::endl;
    } else {
        std::cout << "Message '" << text << "' not found." << std::endl;
    }
}
