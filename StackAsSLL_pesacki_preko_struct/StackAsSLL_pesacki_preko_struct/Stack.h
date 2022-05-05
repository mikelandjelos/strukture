#pragma once

#include <iomanip>
#include <iostream>
#include <exception>

template <class T>
struct StackNode {
	T* info;
	StackNode<T>* next;
	StackNode(T info, StackNode<T>* next = nullptr) : info(new T(info)), next(next) {}
	~StackNode() { if (info != nullptr) delete info; next = nullptr, info = nullptr; }
};

template <class T>
class Stack {
protected:
	StackNode<T>* m_top;
	unsigned long m_numOfEl;
	static unsigned long maxNumberOfBytes;
public:
	// constructors, destructor
	Stack();
	Stack(const Stack<T>&);
	virtual ~Stack();

	// basic stack operations
	void push(T);
	T pop();

	// miscellaneous
	bool isEmpty() const { return m_top == nullptr; }
	T getTop() const { return *m_top->info; }
	T& getTopRef() { return *m_top->info; }
	bool checkMemReq() { return m_numOfEl * sizeof(T) > maxNumberOfBytes; }
	long getSize() { return m_numOfEl; }
	long getSizeInBytes() { return m_numOfEl * sizeof(T); }

	// operatorske funkcije
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const Stack<T>&);

protected:
	virtual std::ostream& write(std::ostream&) const;
};

template <class T>
unsigned long Stack<T>::maxNumberOfBytes = 8096;

template <class T>
Stack<T>::Stack() 
	: m_top(nullptr), m_numOfEl(0) {}

template <class T>
Stack<T>::Stack(const Stack<T>& stek) {}

template <class T>
Stack<T>::~Stack() {
	while (!isEmpty())
		pop();
}

template <class T>
void Stack<T>::push(T info) { // addToHead
	m_top = new StackNode<T>(info, m_top);
	m_numOfEl++;
}

template <class T>
T Stack<T>::pop() { // deleteFromHead
	if (isEmpty())
		throw new std::exception("STACK_ERR: Cannot delete element from empty collection!");
	StackNode<T>* forDel = m_top;
	m_top = m_top->next;
	T ret = *forDel->info;
	delete forDel;
	m_numOfEl--;
	return ret;
}

template <class T>
std::ostream& Stack<T>::write(std::ostream& izlTok) const {
	for (StackNode<T>* iter = m_top; iter != nullptr; iter = iter->next)
		izlTok << "| " << std::setw(4) << std::setfill(' ') << *iter->info << " |\n";
	return izlTok;
}

template <class T>
std::ostream& operator<<(std::ostream& izlTok, const Stack<T>& stek) {
	return stek.write(izlTok);
}