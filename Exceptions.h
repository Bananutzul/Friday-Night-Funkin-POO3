#pragma once
#include <exception>
#include <string>

using namespace std;

class InvalidOptionException : public exception {
    string message;
public:
    InvalidOptionException(const string& message = "Invalid Option!") : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
