#ifndef STATICDEQUE_H
#define STATICDEQUE_H

#include "SDException.h"

#define DEFCAPACITY 30

template <class T>
class StaticDeque {
protected:
	T** arr;
	unsigned int capacity;
	int front;
	int rear;
	unsigned int size;
public:
	// konstruktori destruktori
	StaticDeque(unsigned int = DEFCAPACITY);
	StaticDeque(const StaticDeque<T>&);

	virtual ~StaticDeque();

	// basic ops
	void enqueueFront(T);
	T dequeueFront();
	void enqueueRear(T);
	T dequeueRear();
	T* peekFront();
	T* peekRear();

	// misc
	bool isEmpty() const { return size == 0; }
	bool isFull() const { return size == capacity; }
	unsigned int getSize() const { return size; }
};

template <class T>
StaticDeque<T>::StaticDeque(unsigned int capacity) 
	: arr(new T* [capacity]), capacity(capacity),
	front(-1), rear(-1), size(0) {
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;
}

template <class T>
StaticDeque<T>::StaticDeque(const StaticDeque<T>& q)
	: arr(new T* [q.capacity]), capacity(q.capacity),
	front(q.front), rear(q.rear), size(q.size) {
	for (int i = 0; i < q.capacity; ++i)
		if (q.arr[i] != nullptr)
			arr[i] = new T(*q.arr[i]);
}

template <class T>
StaticDeque<T>::~StaticDeque() {
	while (!isEmpty())
		dequeueFront();
	if (arr != nullptr)
		delete[] arr;
	arr = nullptr;
}

template <class T>
void StaticDeque<T>::enqueueFront(T el) {
	if (isFull())
		throw SDException("Deque overflow!");
	if (isEmpty())
		front = rear = 1;
	// front = (front - 1) % capacity; - ovo iz nekog razloga ne radi
	// u granicnom slucaju front == 0 (iako je recimo -1 mod 5 == 4)
	if (front == 0)
		front = capacity - 1;
	else
		front = (front - 1) % capacity;
	arr[front] = new T(el);
	size++;
}

template <class T>
T StaticDeque<T>::dequeueFront() {
	if (isEmpty())
		throw SDException("Deque underflow!");
	T forRet = *arr[front];
	delete arr[front];
	front = (front + 1) % capacity;
	size--;
	return forRet;
}

template <class T>
void StaticDeque<T>::enqueueRear(T el) {
	if (isFull())
		throw SDException("Deque overflow!");
	if (isEmpty())
		front = 0, rear = 0;
	arr[rear] = new T(el);
	rear = (rear + 1) % capacity;
	size++;
}

template <class T>
T StaticDeque<T>::dequeueRear() {
	if (isEmpty())
		throw SDException("Deque underflow!");
	if (rear == 0)
		rear = capacity - 1;
	else
		rear = (rear - 1) % capacity;
	T forRet = *arr[rear];
	delete arr[rear];
	size--;
	return forRet;
}

template <class T>
T* StaticDeque<T>::peekFront() {
	if (isEmpty())
		return nullptr;
	return arr[front];
}

template <class T>
T* StaticDeque<T>::peekRear() {
	if (isEmpty())
		return nullptr;
	int tmp;
	if (rear == 0)
		tmp = capacity - 1;
	else
		tmp = (rear - 1) % capacity;
	return arr[tmp];
}

#endif // !STATICDEQUE_H