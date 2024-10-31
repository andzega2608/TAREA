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
// Constructor por default
template <class T>
Heap<T>::Heap(unsigned int sze) {
    size_heap = sze;
    data = new T[size_heap];
    count = 0;
}
// Destructor por default
template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    size_heap = 0;
    count = 0;
}
/*
* empty() const
*
* Revisa si el heap esta vacio
*
* @param
* return true o false
*/
template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}
/*
* full() const
*
* Revisa si el heap esta lleno
*
* @param
* return true o false
*/
template <class T>
bool Heap<T>::full() const {
    return (count == size_heap);
}
/*
* parent(unsigned int pos) const
*
* Calcula y retorna la posición del nodo padre en el heap
* dada una posición de nodo.
*
* param posicion
* return posicion del padre
*/
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}
/*
* left(unsigned int pos) const
*
* Calcula y retorna la posición del hijo izquierdo
* en el heap dada una posición de nodo.
*
* param posicion
* return posicion del hijo izquierdo
*/
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return (2 * pos) + 1;
}
/*
* right(unsigned int pos) const
*
* Calcula y retorna la posición del hijo derecho
* en el heap dada una posición de nodo.
*
* param posicion
* return posicion del hijo derecho
*/
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (2 * pos) + 2;
}
/*
* swap(unsigned int i, unsigned int j)
*
* Cambia la posición entre dos elementos dentro del heap
*
* param unsigned int i, unsigned int j
* @return
*/
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}
/*
* heapify(unsigned int pos)
*
* Mantiene la propiedad del min-heap a partir de la
* posición especificada. Se encarga de comparar el valor
* de los hijos con el padre y realiza intercambios
*
* param unsigned int pos posicion del nodo a verificar
* @return
*/
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
/*
* push(T val)
*
* Inserta un nuevo valor en el heap, manteniendo
* la estructura completa
*
* param T val
* @return
*/
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
/*
* pop()
*
* Elimina y retorna el valor mínimo del heap
* Coloca el último elemento del heap en la raíz
* y luego aplica `heapify`
*
* @param
* return T val, valor mínimo dentro del heap
*/
template <class T>
T Heap<T>::pop() {
	T aux = data[0];
	data[0] = data[--count];
	heapify(0);
	return aux;
}
/*
* top()
*
* Retorna el valor que se encuentra en la raiz,
* es decir, el valor mínimo
*
* @param
* return T val, valor mínimo/raíz del heap
*/
template <class T>
T Heap<T>::top() {
	T aux = data[0];
	return aux;
}
/*
* size() const
*
* Retornar el tamaño del heap
*
* @param
* return tamaño del heap
*/
template <class T>
int Heap<T>::size() const {
    return count;
}
/*
* clear()
*
* Limpia todo el heap
*
* @param
* @return
*/
template <class T>
void Heap<T>::clear() {
    count = 0;
}
/*
* toString() const
*
* Concatena los valores del heap en un string
*
* @param
* return string con los valores concatenados
*/
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
