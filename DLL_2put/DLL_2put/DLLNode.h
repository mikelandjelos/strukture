#ifndef DLLNODE_H
#define DLLNODE_H

#include <iostream>

template <class T>
class DLLNode {
public:
	T* info;
	DLLNode<T>* next, * prev;
public:
	DLLNode(T info, DLLNode<T>* prev = nullptr, DLLNode<T>* next = nullptr)
		: info(new T(info)), prev(prev), next(next) {}

	virtual ~DLLNode() {
		if (info != nullptr)
			delete info;
		info = nullptr;
		next = prev = nullptr;
	}
	template <class T>
	friend bool operator==(const DLLNode<T>&, const DLLNode<T>&);
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const DLLNode<T>&);
};
template <class T>
bool operator==(const DLLNode<T>& levi, const DLLNode<T>& desni) {
	return *levi.info == *desni.info;
}

template <class T>
std::ostream& operator<<(std::ostream& izlTok, const DLLNode<T>& node) {
	return izlTok << *node->info;
}

#endif // !DLLNODE_H