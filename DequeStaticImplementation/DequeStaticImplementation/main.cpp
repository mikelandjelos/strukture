#include <iostream>
#include <cstdlib>
#include <ctime>
#include "StaticDeque.h"

void terminator() {
	std::cerr << "Terminisan!\n";
	std::abort();
}

int main() {

	std::set_terminate(terminator);
	srand(time(NULL));
	int n;

	// regularno
	try {

		std::cout << "Koliko elemenata zelite u svom deque-u: ";
		std::cin >> n;

		StaticDeque<int> regular(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n; ++i) {
			int tmp = rand() % 100 - 50;
			if (i % 2 == 0) {
				std::cout << "Enqueue front: " << tmp << '\n';
				regular.enqueueFront(tmp);
			}
			else {
				std::cout << "Enqueue rear: " << tmp << '\n';
				regular.enqueueRear(tmp);
			}
		}

		std::cout << ((regular.isFull())
			? "\nDeque napunjen!\n" : "\nDoslo je do greske!\n");

		std::cout << "\nVrsni elementi: " 
			<< "\nfront - " << *regular.peekFront() << '\n'
			<< "\nrear - " << *regular.peekRear() << '\n';

		std::cout << "\n\t\tIzbacivanje elemenata:\n";

		for (int i = 0; i < n; ++i)
			if (i % 2 == 0)
				std::cout << "Dequeue front: " << regular.dequeueFront() << '\n';
			else
				std::cout << "Dequeue rear: " << regular.dequeueRear() << '\n';

		std::cout << ((regular.isEmpty())
			? "\nDeque ispraznjen!\n" : "\nDoslo je do greske!\n");

		regular.enqueueFront(5);

	}
	catch (SDException& ex) {
		std::cerr << ex.what() << "\n";
	}

	std::cout << "------------------------";
	std::cout << "------------------------\n\n";

	// overflow
	try {

		std::cout << "Koliko elemenata zelite u svom deque-u: ";
		std::cin >> n;

		StaticDeque<int> overflown(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n + 1; ++i) {
			int tmp = rand() % 100 - 50;
			if (i % 2 == 0) {
				std::cout << "Enqueue front: " << tmp << '\n';
				overflown.enqueueFront(tmp);
			}
			else {
				std::cout << "Enqueue rear: " << tmp << '\n';
				overflown.enqueueRear(tmp);
			}
		}

	}
	catch (SDException& ex) {
		std::cerr << ex.what() << "\n";
	}

	std::cout << "------------------------";
	std::cout << "------------------------\n\n";

	// underflow
	try {

		std::cout << "Koliko elemenata zelite u svom deque-u: ";
		std::cin >> n;

		StaticDeque<int> underflown(n);

		std::cout << "\n\t\tDodavanje elemenata:\n";

		for (int i = 0; i < n; ++i) {
			int tmp = rand() % 100 - 50;
			if (i % 2 == 0) {
				std::cout << "Enqueue front: " << tmp << '\n';
				underflown.enqueueFront(tmp);
			}
			else {
				std::cout << "Enqueue rear: " << tmp << '\n';
				underflown.enqueueRear(tmp);
			}
		}

		std::cout << ((underflown.isFull())
			? "\nDeque napunjen!\n" : "\nDoslo je do greske!\n");

		std::cout << "\nVrsni elementi: "
			<< "\nfront - " << *underflown.peekFront() << '\n'
			<< "\nrear - " << *underflown.peekRear() << '\n';

		std::cout << "\n\t\tIzbacivanje elemenata:\n";

		for (int i = 0; i < n + 1; ++i)
			if (i % 2 == 0)
				std::cout << "Dequeue front: " << underflown.dequeueFront() << '\n';
			else
				std::cout << "Dequeue rear: " << underflown.dequeueRear() << '\n';

	}
	catch (SDException& ex) {
		std::cerr << ex.what() << "\n";
	}

	return 0;
}

//Koliko elemenata zelite u svom deque - u: 5
//
//Dodavanje elemenata :
//Enqueue front : -10
//Enqueue rear : -38
//Enqueue front : -14
//Enqueue rear : 43
//Enqueue front : -42
//
//Deque napunjen!
//
//Vrsni elementi :
//front - -42
//
//rear - 43
//
//Izbacivanje elemenata :
//Dequeue front : -42
//Dequeue rear : 43
//Dequeue front : -14
//Dequeue rear : -38
//Dequeue front : -10
//
//Deque ispraznjen!
//------------------------------------------------
//
//Koliko elemenata zelite u svom deque - u : 5
//
//Dodavanje elemenata :
//Enqueue front : 31
//Enqueue rear : -23
//Enqueue front : 0
//Enqueue rear : -41
//Enqueue front : -12
//Enqueue rear : -13
//SDException : Deque overflow!
//------------------------------------------------
//
//Koliko elemenata zelite u svom deque - u : 5
//
//Dodavanje elemenata :
//Enqueue front : 2
//Enqueue rear : 10
//Enqueue front : -24
//Enqueue rear : 21
//Enqueue front : 6
//
//Deque napunjen!
//
//Vrsni elementi :
//front - 6
//
//rear - 21
//
//Izbacivanje elemenata :
//Dequeue front : 6
//Dequeue rear : 21
//Dequeue front : -24
//Dequeue rear : 10
//Dequeue front : 2
//SDException : Deque underflow!