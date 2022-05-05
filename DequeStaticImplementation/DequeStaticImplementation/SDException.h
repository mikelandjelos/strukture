#ifndef SDEXCEPTION_H
#define SDEXCEPTION_H

#include <exception>
#include <string>

class SDException : public std::exception {
protected:
	std::string errMsg;
public:
	SDException(const std::string em = "") {
		errMsg += "SDException: ";
		errMsg += (em == "") ? "Thrown!" : em;
	}
	const char* what() const noexcept override {
		return errMsg.c_str();
	}
};

#endif // !SDEXCEPTION_H