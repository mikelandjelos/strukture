#ifndef DLLIST_H
#define DLLIST_H

#include "DLLNode.h"
#include "DLLException.h"

template <class T>
class DLList {
protected:
	DLLNode<T>* head, * tail;
	unsigned int numOfNodes;

public:

	// konstruktori
	DLList();
	DLList(const DLList<T>&);

	// destruktor
	virtual ~DLList();

	// dodavanje cvorova
	void addToHead(T);
	void addToTail(T);

	// brisanje cvorova
	T deleteFromHead();
	T deleteFromTail();
	bool deleteElement(T);

	// trazenje cvorova
	DLLNode<T>* findElement(T);
	bool isInList(T) const;

	// miscellaneous
	bool isEmpty() const { return head == nullptr; }
	unsigned int size() const { return numOfNodes; }
	unsigned long sizeInBytes() const { return numOfNodes * sizeof(T); }
	const DLLNode<T>* getHead() const { return head; }
	const DLLNode<T>* getTail() const { return tail; }
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const DLList<T>&);
	std::ostream& printReverse(std::ostream&);

protected:
	std::ostream& write(std::ostream&) const;

};

template <class T>
DLList<T>::DLList() 
	: head(nullptr), tail(nullptr), numOfNodes(0) {}

template <class T>
DLList<T>::~DLList() {
	while (!isEmpty())
		deleteFromTail();
	numOfNodes = 0;
}

template <class T>
void DLList<T>::addToHead(T info) {
	DLLNode<T>* novi = new DLLNode<T>(info);
	if (head != nullptr)
		novi->next = head,
		head->prev = novi;
	head = novi;
	if (tail == nullptr) tail = head;
	numOfNodes++;
}

template <class T>
void DLList<T>::addToTail(T info) {
	DLLNode<T>* novi = new DLLNode<T>(info);
	if (tail != nullptr)
		novi->prev = tail,
		tail->next = novi;
	tail = novi;
	if (head == nullptr) head = tail;
	numOfNodes++;
}

template <class T>
T DLList<T>::deleteFromHead() {
	if (isEmpty())
		throw DLLException("DLLIST_ERR: Deletion from empty list!");
	DLLNode<T>* forDel = head;
	if (head == tail) head = tail = nullptr;
	else {
		head = head->next;
		head->prev = nullptr;
	}
	T ret = *forDel->info;
	delete forDel;
	numOfNodes--;
	return ret;
}

template <class T>
T DLList<T>::deleteFromTail() {
	if (isEmpty())
		throw DLLException("DLLIST_ERR: Deletion from empty list!");
	DLLNode<T>* forDel = tail;
	if (head == tail) head = tail = nullptr;
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}
	T ret = *forDel->info;
	delete forDel;
	numOfNodes--;
	return ret;
}

template <class T>
bool DLList<T>::deleteElement(T el) {
	if (isEmpty())
		return false;
	DLLNode<T>* iter = head;
	while (iter != nullptr) {
		if (*iter->info == el) {
			if (iter != head && iter != tail)
				iter->prev->next = iter->next,
				iter->next->prev = iter->prev,
				delete iter,
				numOfNodes--;
			else
				if (iter == head)
					deleteFromHead();
				else
					deleteFromTail();
			return true;
		}
		iter = iter->next;
	}
	return false;
}

template <class T>
DLLNode<T>* DLList<T>::findElement(T el) {
	DLLNode<T>* iter = head;
	while (iter != nullptr) {
		if (*iter->info == el)
			return iter;
		iter = iter->next;
	}
	return nullptr;
}

template <class T>
bool DLList<T>::isInList(T el) const {
	return (findElement(el) == nullptr) ? false : true;
}

template <class T>
std::ostream& DLList<T>::write(std::ostream& izlTok) const {
	izlTok << "start ->\n\t";
	DLLNode<T>* iter = head;
	while (iter->next != nullptr) {
		izlTok << *iter->info << " <=> ";
		iter = iter->next;
	}
	return izlTok << *iter->info << " -> null";
}

template <class T>
std::ostream& operator<<(std::ostream& izlTok, const DLList<T>& lista) {
	return lista.write(izlTok);
}

template <class T>
std::ostream& DLList<T>::printReverse(std::ostream& izlTok) {
	izlTok << "start ->\n\t";
	DLLNode<T>* iter = tail;
	while (iter->prev != nullptr) {
		izlTok << *iter->info << " <=> ";
		iter = iter->prev;
	}
	return izlTok << *iter->info << " -> null";
}

#endif // !DLLIST_H