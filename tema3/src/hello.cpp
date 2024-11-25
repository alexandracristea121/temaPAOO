#include "../inc/hello.hpp"
#include <algorithm>
#include <iomanip>

hello::Message::Message(const std::string& text) 
    : text(new std::string(text)), timeCreated(std::chrono::system_clock::now()) {
}

hello::Message::Message(const Message& other) 
    : text(new std::string(*other.text)), timeCreated(other.timeCreated) {
}

hello::Message::Message(Message&& other) noexcept 
    : text(other.text), timeCreated(other.timeCreated) {
    other.text = nullptr;
}

hello::Message::~Message() {
    delete text; 
}

hello::Message& hello::Message::operator=(const Message& other) {
    if (this != &other) { 
        delete text; 
        text = new std::string(*other.text); 
        timeCreated = other.timeCreated; 
    }
    return *this; 
}


hello::Message& hello::Message::operator=(Message&& other) noexcept {
    if (this != &other) { 
        delete text; 
        text = other.text; 
        timeCreated = other.timeCreated; 
        other.text = nullptr; 
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

hello::Hello::Hello() {}

hello::Hello::Hello(const Hello& other) {
    for (const auto& msg : other.messages) {
        messages.push_back(new Message(*msg)); 
    }
}

hello::Hello::Hello(Hello&& other) noexcept : messages(std::move(other.messages)) {
    other.messages.clear(); 
}


hello::Hello::~Hello() {
    clearMessages(); 
}

hello::Hello& hello::Hello::operator=(const Hello& other) {
    if (this != &other) { 
        clearMessages(); 
        for (const auto& msg : other.messages) {
            messages.push_back(new Message(*msg)); 
        }
    }
    return *this;
}

hello::Hello& hello::Hello::operator=(Hello&& other) noexcept {
    if (this != &other) { 
        clearMessages(); 
        messages = std::move(other.messages); 
        other.messages.clear(); 
    }
    return *this;
}

void hello::Hello::addMessage(const std::string& message) {
    messages.push_back(new Message(message)); 
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
    for (auto& msg : messages) {
        delete msg;
    }
    messages.clear(); 
}

void hello::Hello::removeMessage(const std::string& text) {
    auto it = std::find_if(messages.begin(), messages.end(), [&](Message* msg) {
        return msg->getText() == text;
    });

    if (it != messages.end()) {
        delete *it;
        messages.erase(it); 
        std::cout << "Message '" << text << "' removed." << std::endl;
    } else {
        std::cout << "Message '" << text << "' not found." << std::endl;
    }
}
