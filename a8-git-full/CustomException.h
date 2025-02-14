#pragma once
#include <exception>
#include <string>

class ExceptionClass : public std::exception {
private:
	std::string message;
public:
	ExceptionClass(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};