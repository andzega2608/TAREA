/*
 * Tarea #4
 *
 * Fecha: 25/09/2024
 * Autor: Andrés Ignacio Zegales Taborga
 * Matricula: A01711365
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;

template <class T>
class DLink {
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);
        T	    value;
        DLink<T> *previous;
        DLink<T> *next;
        friend class DList<T>;
};
// Constructor por default
template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}
// Constructor por parametros
template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val),
    previous(prev), next(nxt) {}
// Constructor por copia
template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value),
    previous(source.previous), next(source.next) {}

template <class T>
class DList {
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
    public:
        DList();
        std::string toStringForward() const;
        std::string toStringBackward() const;
        void insertion(T val);
        int search(T val);
        void update(int index, T val);
        void deleteAt (int index);
};
// Constructor por default
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}
/*
* std::string DList<T>::toStringForward() const
*
* Retorna un string con los valores de cada nodo dentro
* de la lista doblemente enlazada por delante
*
* param
* @return string de valores
*/
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}
/*
* std::string DList<T>::toStringBackward() const
*
* Retorna un string con los valores de cada nodo dentro
* de la lista doblemente enlazada por atras
*
* param
* @return string de valores
*/
template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;
	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}
/*
* void insertion(T val)
*
* Inserta el valor al final de la lista doblemente enlazada
*
* param T val
* @return
*/

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *p = new DLink<T> (val);
    if (head == 0 && tail == 0){
        head = p;
        tail = p;
    }
    else {
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
    size ++;
}
/*
* int search(T val)
*
* Retorna el valor del indice del valor dentro de la
* lista, si no se encuentra el valor, retorna -1
*
* param T val
* @return indice del valor dentro de la lista
*/
template <class T>
int DList<T>::search(T val){
    int c1 = 0;
    int c2 = size - 1;
    DLink<T> *p = head;
    DLink<T> *q = tail;
    while (p != q){
        if (p->value == val){
            return c1;
        }
        p = p->next;
        c1 = c1 + 1;
        if (q->value == val){
            return c2;
        }
        q = q->previous;
        c2 = c2 - 1;
    }
    return -1;
}
/*
* void update(int index, T val)
*
* Cambia el valor de un dato dentro de la lista acorde a su indice
*
* param indice del elemento dentro de la lista y su valor a cambiar
* @return
*/
template <class T>
void DList<T>::update(int index, T val){
    DLink<T> *p; int c;
    int aux = size/2 - 1;
    if (index <= aux){
        p = head;
        c = 0;
        while (c != index){
            p = p->next;
            c = c + 1;
        }
    }
    else {
        p = tail;
        c = size - 1;
        while (c != index){
            p = p->previous;
            c = c - 1;
        }
    }
    p->value = val;
}
/*
* void deleteAt(int index)
*
* Elima el valor dentro de la lista acorde a su indice
*
* param indice del elemento a eliminar
* @return
*/
template <class T>
void DList<T>::deleteAt(int index){
    DLink<T> *p;
    if (head == tail){
        delete head;
        head = 0;
        tail = 0;
	}
	else {
        if (index == 0){
            p = head;
            p = p->next;
            p->previous = 0;
            delete head;
            head = p;
        }
        else if (index == (size - 1)){
            p = tail;
            p = p->previous;
            p->next = 0;
            delete tail;
            tail = p;
        }
        else {
            int c;
            int aux = size/2 - 1;
            if (index <= aux){
                p = head;
                c = 0;
                while (c != index){
                    p = p->next;
                    c = c + 1;
                }
                p->previous->next = p->next;
                p->next->previous = p->previous;
            }
            else {
                p = tail;
                c = size - 1;
                while (c != index){
                    p = p->previous;
                    c = c - 1;
                }
                p->next->previous = p->previous;
                p->previous->next = p->next;
            }
        }
	}
    size--;
}
#endif /* DLIST_H_ */
