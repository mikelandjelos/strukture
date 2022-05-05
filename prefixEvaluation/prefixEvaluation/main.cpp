#include <iostream>
#include <cstring>
#include <stack>
#include <exception>
#include <string>
#include "prefixEvaluation.h"

using namespace infixAndPrefix;
using namespace infixAndPostfix;

int main() {

	try {

		std::string expr("( 9 - 3 ) * ( 4 + 3 / 5 ) * 4 + 7");

		// std::cout << evaluatePrefix("**+4/35-934") << '\n';

		std::string prefix = infixToPrefix(expr);
		std::string postfix = infixToPostfix(expr);

		std::cout << postfix.c_str() << " = ";
		std::cout << evaluatePostfix(postfix.c_str()) << '\n';

		std::cout << prefix.c_str() << " = ";
		std::cout << evaluatePrefix(prefix.c_str()) << '\n';
	
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	

	return 0;
}

