/*
 * Tarea #3
 *
 * Fecha: 20/09/2024
 * Autor: Andrés Ignacio Zegales Taborga
 * Matricula: A01711365
 */

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link {
    private:
        Link(T);
        Link(T, Link<T>*);
        Link(const Link<T>&);
        T	    value;
        Link<T> *next;
        friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
    private:
        Link<T> *head;
        int 	size;
    public:
        List();
        std::string toString() const;
        void insertion(T val);
        int search(T val);
        void update(int index, T val);
        void deleteAt (int index);
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
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

template <class T>
void List<T>::insertion(T val){
    Link<T> *nuevo;
	nuevo = new Link<T>(val);
	if (head == 0) {
		head = nuevo;
	}
	else {
        Link<T> *temp = head;
        while (temp->next != 0){
            temp = temp->next;
        }
        temp->next = nuevo;
	}
	size++;
}

template <class T>
int List<T>::search(T val){
    int index = 0;
    Link<T> *temp;
    temp = head;
    while (temp != 0){
        if (temp->value == val){
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

template <class T>
void List<T>::update(int index, T val){
    Link<T> *temp = head;
    int aux = 0;
    while (aux != index){
        temp = temp->next;
        aux++;
    }
    temp->value = val;
}

template <class T>
void List<T>::deleteAt(int index){
    Link<T> *p = head;
    if (index == 0){
        head = head->next;
        delete p;
    }
    else {
        int ind = index - 1;
        int aux = 0;
        Link<T> *q = p->next;
        while ((aux != ind) && (q->next != 0)){
            aux = aux + 1;
            p = p->next;
            q = q->next;
        }
        p->next = q->next;
        delete q;
    }
    size--;
}

#endif /* LIST_H_ */
