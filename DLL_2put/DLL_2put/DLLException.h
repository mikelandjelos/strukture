#ifndef DLLEXCEPTION_H
#define DLLEXCEPTION_H

#include <exception>

class DLLException : public std::exception {
protected:
	const char* errMsg;
public:
	DLLException(const char* errMsg = "Exception thrown by DLList!") 
		: errMsg(errMsg) {}
};

#endif // !DLLEXCEPTION_H