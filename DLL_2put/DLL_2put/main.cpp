#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DLList.h"

int main() {

	srand(time(NULL));
	
	try {

		DLList<int> intList;
		int n;

		std::cout << "Koliko cvorova zelite da ima vasa lista: ";
		std::cin >> n;

		for (int i = 0; i < n; ++i)
			intList.addToTail(rand() % 500 - 250);

		std::cout << intList << '\n';

		std::cout << "Koliko cvorova zelite da obrisete sa repa: ";
		std::cin >> n;

		std::cout << "Brisanje:\n";
		for (int i = 0; i < n; ++i)
			std::cout << intList.deleteFromTail() << '\n';

		std::cout << '\n' << intList << '\n';

		std::cout << "Koji element zelite da obrisete: ";
		std::cin >> n;

		std::cout << ((intList.deleteElement(n)) ? "Obrisan.\n" : "Nije u listi.\n");

		std::cout << intList << '\n';

		intList.printReverse(std::cout) << '\n';

	}
	catch (DLLException& ex) {
		std::cerr << ex.what() << '\n';
	}

	return 0;
}