/*
 * Tarea #2
 *
 * Fecha: 29/08/2024
 * Autor: Andrés Ignacio Zegales Taborga
 * Matricula: A01711365
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	int busqAux(std::vector<T>&, int, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	void ordenaBurbuja(std::vector<T>&);
	void ordenaSeleccion(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);
	int busqSecuencial(std::vector<T>&, int);
	int busqBinaria(std::vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v.size() - i - 1; j++){
            if (v[j] > v[j+1]){
                swap(v, j, j+1);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v) {
	int index;
	for (int i = 0; i < v.size(); i++){
        index = i;
        for (int j = i + 1; j < v.size(); j++){
            if (v[index] > v[j]){
                index = j;
            }
        }
        if (index != i){
            swap(v, i, index);
        }
	}
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
    for (int i = low; i <= high; i++){
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;
	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
	std::vector<T> tmp(v.size());
	mergeSplit(v, tmp, 0, v.size() - 1);
}


template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &v, int val) {
	ordenaBurbuja(v); // Precondicion. Se asegura que el vector este ordenado
	for (int i = 0; i < v.size(); i++){
        if (val == v[i]){
            return i;
        }
	}
	return -1;
}

template <class T>
int Sorts<T>::busqAux(std::vector<T> &v, int low, int high, int val) {
	int mid = (high + low) / 2;
	if (low <= high){  // Verifica si no está el elemento
        if (v[mid] == val){ // Condicion base
            return mid;
        }
        else {
            if (val > v[mid]){ // Separacion de la parte derecha del arreglo
                return busqAux(v, mid + 1, high, val);
            }
            else { // Separacion de la parte izquierda del arreglo
                return busqAux(v, low, mid - 1, val);
            }
        }
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v, int val) { // Funcion adecuada
	ordenaBurbuja(v); // Precondicion. Se asegura que el vector este ordenado
	return busqAux(v, 0, v.size()-1, val);
}
#endif /* SORTS_H_ */
