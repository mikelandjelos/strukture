#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Stack.h"

int main() {

	try {

		long n;

		std::cout << "Koliko elemenata zelite da ima vas stek: ";
		std::cin >> n;

		Stack<int> stackInt;

		srand(time(NULL));

		for (int i = 0; i < n; ++i)
			stackInt.push(rand() % 100 - 50);

		std::cout << '\n' << stackInt << '\n';

		std::cout << "Koliko elemenata zelite da izbacite sa steka: ";
		std::cin >> n;

		for (int i = 0; i < n; ++i)
			std::cout << "Izbacivanje:\n" << stackInt.pop() << '\n';

		std::cout << '\n' << stackInt << '\n';

		std::cout << "\nVrsni element: " << stackInt.getTop()
			<< "\nVelicina steka i zauzece: " << stackInt.getSize()
			<< "el. , " << stackInt.getSizeInBytes() << "B\n";

	}
	catch (std::exception* ex) {
		std::cerr << ex->what() << '\n';
		delete ex;
	}

	return 0;
}