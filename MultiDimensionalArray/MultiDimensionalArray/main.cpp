#include <iostream>
#include "MultiDimensionalArray.h"

int main() {
	
	long dims[] = { 5l, 4l, 3l, 5l, 8l };
	long indices[] = { 3l, 2l, 1l, 3l, 6l };
	MultiDimensionalArray<int> mdimArrInt(dims, 5);

	std::cout << mdimArrInt.getOffset(indices, 5); // pogledaj primer sa casa

	return 0;
}