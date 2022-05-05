#pragma once

#include <exception>

template <class T>
class MultiDimensionalArray {
protected:
	T* m_data;			// podaci
	long* m_dim;		// dimenzije
	long* m_fact;		// faktori
	int m_dimensions;	// broj dimenzija
public:
	MultiDimensionalArray(long*, int);
	virtual ~MultiDimensionalArray() {
		delete[] m_data;
		delete[] m_dim;
		delete[] m_fact;
	}
	inline T& getAt(long* indices, int n) {
		return m_data[getOffset(indices, n)];
	}
	inline void setAt(T el, long* indices, int n) {
		m_data[getOffset(indices, n)];
	}
	long getOffset(long*, int);
protected:
};

template <class T>
MultiDimensionalArray<T>::MultiDimensionalArray(long* dim, int n) {

	m_dimensions = n;
	m_dim = new long[n];
	m_fact = new long[n];

	long pom = 1;

	for (int i = n - 1; i >= 0; --i) {
		m_dim[i] = dim[i];
		m_fact[i] = pom;
		pom *= dim[i];
	}

	m_data = new T[pom];

}

template <class T>
long MultiDimensionalArray<T>::getOffset(long* indices, int n) {

	if (n != m_dimensions)
		throw std::exception("M_DIM_ARR: Dimension conflict!");

	long offset = 0;

	for (int i = 0; i < n; ++i)
		if (indices[i] < 0 || indices[i] >= m_dim[i])
			throw std::exception("M_DIM_ARR: Index out of bounds!");
		else
			offset += indices[i] * m_fact[i];

	return offset;

}