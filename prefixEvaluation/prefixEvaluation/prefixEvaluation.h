#include <iostream>
#include <exception>
#include <stack>
#include <string>

namespace miscellaneous {

	int precedence(char c) {
		switch (c) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			throw std::exception("Not an operator!");
		}
	}

	bool isOperator(char c) {
		return c == '+' || c == '-'
			|| c == '*' || c == '/';
	}

	bool isAsciiNum(char c) {
		return c >= '0' && c <= '9';
	}

}

namespace infixAndPostfix {
	
	namespace misc = miscellaneous;

	std::string infixToPostfix(const std::string& str) {
		
		std::stack<char> stek;
		stek.push('$');

		std::string ret = "";

		for (auto iter = str.begin(); iter != str.end(); iter++) {

			if (*iter == ' ')
				continue;
			
			char c = *iter;

			if (misc::isAsciiNum(c))
				ret += c;
			else if (misc::isOperator(c)) {
				if (stek.top() == '$' || stek.top() == '(' ||
					misc::precedence(stek.top()) < misc::precedence(c)) {
					stek.push(c);
				}
				else {
					while (stek.top() != '$' && stek.top() != '(' &&
						misc::precedence(stek.top()) >= misc::precedence(c)) {
						ret += stek.top();
						stek.pop();
					}
					stek.push(c);
				}
			}
			else if (c == '(')
				stek.push(c);
			else if (c == ')') {
				while (stek.top() != '$' && stek.top() != '(') {
					ret += stek.top();
					stek.pop();
				}
				if (stek.top() == '(')
					stek.pop();
				else 
					throw std::exception("Non-matching parentheses!");
			}

		}

		bool matching = true;

		while (stek.top() != '$') {
			if (stek.top() != '(')
				ret += stek.top();
			else
				matching = false;
			stek.pop();
		}

		if (!matching)
			throw std::exception("Non-matching parentheses!");

		return ret;

	}

	double evaluatePostfix(const std::string expr) {

		std::stack<double> stek;
		
		for (auto iter = expr.begin(); iter != expr.end(); iter++) {

			if (*iter == ' ')
				continue;

			if (!misc::isAsciiNum((char) * iter) && 
				!misc::isOperator((char) * iter))
				throw std::exception("Not a postfix expression!");

			if (misc::isAsciiNum((char) * iter))
				stek.push((double) * iter - '0');
			else if (misc::isOperator((char) * iter)) {
				if (stek.empty())
					throw std::exception("postfixEvaluation: Stack underflow!");
				double b = stek.top();
				stek.pop();
				if (stek.empty())
					throw std::exception("postfixEvaluation: Stack underflow!");
				double a = stek.top();
				stek.pop();
				switch ((char) * iter) {
				case '+':
					stek.push(a + b);
					break;
				case '-':
					stek.push(a - b);
					break;
				case '*':
					stek.push(a * b);
					break;
				case '/':
					stek.push(a / b);
				}
			}

		}

		double ret = stek.top();
		stek.pop();

		if (!stek.empty())
			throw std::exception("postfixEvaluation: Expression syntax error!");

		return ret;

	}

}

namespace infixAndPrefix {

	namespace misc = miscellaneous;

	std::string infixToPrefix(const std::string& expr) {
		
		std::stack<char> stek;
		stek.push('$');
		std::string ret = "";

		for (auto iter = expr.rbegin(); iter < expr.rend(); iter++) {
			
			if (*iter == ' ')
				continue;

			if (misc::isAsciiNum(*iter))
				ret.insert(0, 1, *iter); // insert one character at offset 0
			else if (misc::isOperator(*iter)) {
				if (stek.top() == '$' || stek.top() == ')' ||
					misc::precedence(stek.top()) < misc::precedence(*iter))
					stek.push(*iter);
				else {
					while (stek.top() != '$' && stek.top() != ')' &&
						misc::precedence(stek.top()) >= misc::precedence(*iter)) {
						ret.insert(0, 1, stek.top());
						stek.pop();
					}
					stek.push(*iter);
				}
			}
			else if (*iter == ')')
				stek.push(*iter);
			else if (*iter == '(') {
				while (stek.top() != '$' && stek.top() != ')') {
					ret.insert(0, 1, stek.top());
					stek.pop();
				}
				if (stek.top() == ')')
					stek.pop();
				else
					throw std::exception("Non-matching brackets!");
			}

		}

		bool matching = true;

		while (stek.top() != '$') {
			if (stek.top() != ')')
				ret.insert(0, 1, stek.top());
			else
				matching = false;
			stek.pop();
		}

		if (!matching)
			throw std::exception("Non-matching parentheses!");

		return ret;

	}

	double evaluatePrefix(const std::string& expr) {

		std::stack<double> stek;

		for (auto iter = expr.rbegin(); iter != expr.rend(); iter++) {

			if (*iter == ' ')
				continue;

			if (!misc::isAsciiNum( (char) * iter) &&
				!misc::isOperator( (char) * iter))
				throw std::exception("Not a prefix expression!");

			if (misc::isAsciiNum((char) * iter))
				stek.push((char) * iter - '0');
			else if (misc::isOperator((char) * iter)) {
				if (stek.empty())
					throw std::exception("evaluatePrefix: Stack underflow!");
				double a = stek.top();
				stek.pop();
				if (stek.empty())
					throw std::exception("evaluatePrefix: Stack underflow!");
				double b = stek.top();
				stek.pop();
				switch ((char) * iter) {
				case '+':
					stek.push(a + b);
					break;
				case '-':
					stek.push(a - b);
					break;
				case '/':
					stek.push(a / b);
					break;
				case '*':
					stek.push(a * b);
				}
			}
			
		}

		double rez = stek.top();
		stek.pop();

		if (!stek.empty())
			throw std::exception("evaluatePrefix: Expression syntax error!");

		return rez;

	}

}