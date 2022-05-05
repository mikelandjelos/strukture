#pragma once

#include <exception>
#include <iostream>
#include <iomanip>

template <class T>
class Stack {
protected:
	T** m_array;
	long m_top;
	long m_capacity;
	static unsigned long maxNumberOfBytes;

public:
	// constructors, destructor
	Stack(long);
	Stack(const Stack<T>&, float = 1.);
	virtual ~Stack();
	
	// basic stack operations
	void push(T);
	T pop();

	// miscellaneous
	long getSize() const { return m_top + 1; }
	bool isEmpty() const { return m_top == -1; }
	bool isFull() const { return m_top + 1 == m_capacity;  }
	T getTop() const { return *m_array[m_top]; }
	bool checkMemReq() const { 
		if (m_capacity * sizeof(T) > maxNumberOfBytes) return true; 
		return false;
	}
	long getSizeInBytes() const { return getSize() * sizeof(T); }

	// operatorske funkcije
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const Stack<T>&);

protected:
	virtual std::ostream& write(std::ostream&) const;
};

// uracunato je samo koliko instance zauzimaju, ne i sam niz
// pointer-a koji zapravo predstavlja nasu interni memorijski medijum
template <class T>
unsigned long Stack<T>::maxNumberOfBytes = 8096;

template <class T>
Stack<T>::Stack(long capacity)
	: m_capacity(capacity), m_top(-1) {
	if (capacity <= 0 || checkMemReq())
		throw new std::exception("STACK_ERR: Memory allocation failed!");
	m_array = new T * [capacity];
	for (int i = 0; i < m_capacity; ++i)
		m_array[i] = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& stack, float allocMul) 
	: m_capacity(stack.m_capacity * allocMul), m_top(stack.m_top) {
	if (allocMul < 1. )
		throw new std::exception("STACK_ERR: Couldn't downsize allocated memory!");
	if (checkMemReq())
		throw new std::exception("STACK_ERR: Memory allocation failed!");
	m_array = new T * [m_capacity];
	for (int i = 0; i < m_capacity; ++i)
		m_array[i] = stack.m_array[i];
}

template <class T>
Stack<T>::~Stack() {
	for (int i = 0; i <= m_top; ++i)
		if (m_array[i] != nullptr)
			delete m_array[i],
			m_array[i] = nullptr;
	if (m_array != nullptr)
		delete m_array,
		m_array = nullptr;
}

template <class T>
void Stack<T>::push(T el) {
	if (isFull())
		throw new std::exception("STACK_ERR: Stack overflow!");
	m_array[++m_top] = new T(el);
}

template <class T>
T Stack<T>::pop() {
	if (isEmpty())
		throw new std::exception("STACK_ERR: Stack underflow!");
	T ret = *m_array[m_top--];
	delete m_array[m_top + 1], 
		m_array[m_top + 1] = nullptr;
	return ret;
}

template <class T>
std::ostream& Stack<T>::write(std::ostream& izlTok) const {
	for (int i = m_top; i >= 0; i--)
		izlTok << "| " << std::setw(4) << std::setfill(' ') << *m_array[i] << " |\n";
	return izlTok;
}

template <class T>
std::ostream& operator<<(std::ostream& izlTok, const Stack<T>& stack) {
	return stack.write(izlTok);
}