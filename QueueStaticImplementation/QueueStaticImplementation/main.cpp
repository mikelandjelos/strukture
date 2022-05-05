#include <iostream>
#include <cstdlib>
#include <ctime>
#include "StaticQueue.h"

void terminator() {
	std::cerr << "Program terminisan!\n";
	std::abort();
}

int main() {

	std::set_terminate(terminator);
	srand(time(NULL));
	int n;
	
	// regularno
	try {

		std::cout << "Koliko elemenata zelite u svom redu: ";
		std::cin >> n;

		StaticQueue<int> regular(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n; ++i) {
			int tmp = rand() % 100 - 50;
			regular.enqueue(tmp);
			std::cout << "Enqueue: " << tmp << '\n';
		}

		std::cout << ((regular.isFull())
			? "\nRed napunjen!\n" : "\nDoslo je do greske!\n");

		std::cout << "\nVrsni element: " << *regular.peek() << '\n';

		std::cout << "\n\t\tIzbacivanje elemenata:\n";

		for (int i = 0; i < n; ++i)
			std::cout << "Dequeue: " << regular.dequeue() << '\n';

		std::cout << ((regular.isEmpty())
			? "\nRed ispraznjen!\n" : "\nDoslo je do greske!\n");

		regular.enqueue(5);
		
	}
	catch (SQException& ex) {
		std::cerr << ex.what() << "\n";
	}

	std::cout << "------------------------";
	std::cout << "------------------------\n\n";

	// overflow
	try {

		std::cout << "Koliko elemenata zelite u svom redu: ";
		std::cin >> n;

		StaticQueue<int> overflown(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n + 1; ++i) {
			int tmp = rand() % 100 - 50;
			overflown.enqueue(tmp);
			std::cout << "Enqueue: " << tmp << '\n';
		}

	}
	catch (SQException& ex) {
		std::cerr << ex.what() << "\n";
	}

	std::cout << "------------------------";
	std::cout << "------------------------\n\n";

	// underflow
	try {

		std::cout << "Koliko elemenata zelite u svom redu: ";
		std::cin >> n;

		StaticQueue<int> underflown(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n; ++i) {
			int tmp = rand() % 100 - 50;
			underflown.enqueue(tmp);
			std::cout << "Enqueue: " << tmp << '\n';
		}

		std::cout << ((underflown.isFull())
			? "\nRed napunjen!\n" : "\nDoslo je do greske!\n");

		std::cout << "\nVrsni element: " << *underflown.peek() << '\n';

		std::cout << "\n\t\tIzbacivanje elemenata:\n";

		for (int i = 0; i < n + 1; ++i)
			std::cout << "Dequeue: " << underflown.dequeue() << '\n';

	}
	catch (SQException& ex) {
		std::cerr << ex.what() << "\n";
	}

	return 0;
}

/*		Primer izlaza:
* 
* 
		Koliko elemenata zelite u svom redu : 10

		Dodavanje elemenata :
		Enqueue: -50
		Enqueue : 25
		Enqueue : -3
		Enqueue : 46
		Enqueue : 18
		Enqueue : 7
		Enqueue : 49
		Enqueue : 26
		Enqueue : 16
		Enqueue : -33

		Red napunjen!

		Vrsni element : -50

		Izbacivanje elemenata :
		Dequeue: -50
		Dequeue : 25
		Dequeue : -3
		Dequeue : 46
		Dequeue : 18
		Dequeue : 7
		Dequeue : 49
		Dequeue : 26
		Dequeue : 16
		Dequeue : -33

		Red ispraznjen!
		------------------------------------------------

		Koliko elemenata zelite u svom redu : 10

		Dodavanje elemenata :
		Enqueue: 19
		Enqueue : -21
		Enqueue : 35
		Enqueue : -44
		Enqueue : -37
		Enqueue : -3
		Enqueue : 6
		Enqueue : 8
		Enqueue : 15
		Enqueue : 49
		SQException : Queue overflow!
		------------------------------------------------

		Koliko elemenata zelite u svom redu : 10

		Dodavanje elemenata :
		Enqueue: 15
		Enqueue : -14
		Enqueue : -42
		Enqueue : 10
		Enqueue : -23
		Enqueue : -38
		Enqueue : -18
		Enqueue : -39
		Enqueue : 27
		Enqueue : 15

		Red napunjen!

		Vrsni element : 15

		Izbacivanje elemenata :
		Dequeue: 15
		Dequeue : -14
		Dequeue : -42
		Dequeue : 10
		Dequeue : -23
		Dequeue : -38
		Dequeue : -18
		Dequeue : -39
		Dequeue : 27
		Dequeue : 15
		SQException : Queue underflow!
*/