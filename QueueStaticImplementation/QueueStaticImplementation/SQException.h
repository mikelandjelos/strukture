#ifndef SQEXCEPTION_H
#define SQEXCEPTION_H

#include <exception>
#include <string>

class SQException : std::exception {
private:
	std::string errMsg;
public:
	SQException(const std::string em = "") {
		errMsg += "SQException: ";
		errMsg += (em == "") ? "Thrown!" : em;
	}
	const char* what() const noexcept override {
		return errMsg.c_str();
	}
};

#endif // !SQEXCEPTION_H