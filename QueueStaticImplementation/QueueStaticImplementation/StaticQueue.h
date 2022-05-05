#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include <iostream>
#include "SQException.h"

#define DEFCAPACITY 30

template <class T>
class StaticQueue {
protected:
	T** arr;
	unsigned int capacity;
	unsigned int front;
	unsigned int rear;
	unsigned int size;
public:
	// konstruktori, destruktor
	StaticQueue(unsigned int = DEFCAPACITY);
	StaticQueue(const StaticQueue&);

	virtual ~StaticQueue();

	// basic ops
	void enqueue(T);
	T dequeue();
	T* peek(); // == getHead() iz praktikuma

	// misc
	bool isEmpty() const { return size == 0; }
	bool isFull() const { return size == capacity; }
	unsigned int getSize() const { return size; }

};

template <class T>
StaticQueue<T>::StaticQueue(unsigned int capacity) 
	: arr(new T * [capacity]), capacity(capacity),
	front(-1), rear(-1), size(0) {
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;
}

template <class T>
StaticQueue<T>::StaticQueue(const StaticQueue<T>& q) 
	: arr(new T * [q.capacity]), capacity(q.capacity),
	front(q.front), rear(q.rear), size(q.size) {
	for (int i = 0; i < q.capacity; ++i)
		if (q.arr[i] != nullptr)
			arr[i] = new T(*q.arr[i]);
}

template <class T>
StaticQueue<T>::~StaticQueue() {
	while (!isEmpty())
		dequeue();
	if (arr != nullptr)
		delete[] arr;
	arr = nullptr;
}

template <class T>
void StaticQueue<T>::enqueue(T el) {
	if (isFull()) // provera prekoracenja
		throw SQException("Queue overflow!");
	if (isEmpty()) // prvo dodavanje (spec. slucaj)
		front = rear = 0;
	arr[rear] = new T(el);
	rear = (rear + 1) % capacity;
	size++;
}

template <class T>
T StaticQueue<T>::dequeue() {
	if (isEmpty()) // provera potkoracenja
		throw SQException("Queue underflow!");
	T forRet = *arr[front];
	delete arr[front];
	front = (front + 1) % capacity;
	size--;
	return forRet;
}

template <class T>
T* StaticQueue<T>::peek() {
	if (isEmpty())
		return nullptr;
	return arr[front];
}

#endif // !STATICQUEUE_H