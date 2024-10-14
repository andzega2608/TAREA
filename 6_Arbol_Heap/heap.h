/*
 * Tarea #6
 *
 * Fecha: 16/10/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap {
    private:
        T *data;
        unsigned int size_heap;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);
    public:
        Heap(unsigned int);
        ~Heap();
        bool empty() const;
        bool full() const;
        void push(T);
        T pop();
        T top();
        int size() const;
        void clear();
        std::string toString() const;
    };

template <class T>
Heap<T>::Heap(unsigned int sze) {
    size_heap = sze;
    data = new T[size_heap];
    count = 0;
}

template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    size_heap = 0;
    count = 0;
}

template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T>
bool Heap<T>::full() const {
    return (count == size_heap);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return (2 * pos) + 1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (2 * pos) + 2;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le < count && data[le] < data[min]) {
		min = le;
	}
	if (ri < count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;
	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
T Heap<T>::pop() {
	T aux = data[0];
	data[0] = data[--count];
	heapify(0);
	return aux;
}

template <class T>
T Heap<T>::top() {
	T aux = data[0];
	return aux;
}

template <class T>
int Heap<T>::size() const {
    return count;
}

template <class T>
void Heap<T>::clear() {
    count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}
#endif /* HEAP_H_ */
