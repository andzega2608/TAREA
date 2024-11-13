/*
 * Tarea #9 
 *
 * Fecha: 14/11/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;
	Key *keys;
	Key initialValue;
	Value *values;
	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	bool put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};
// Constructor por default
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	size = sze; 
	keys = new Key[size];
	initialValue = init; 
	for (unsigned int i = 0; i < size; i++){
		keys[i] = init;
	}
	values = new Value[size];
	for (int i = 0; i < sze; i++){
		values[i] = 0;
	}
	func = f; 
	count = 0;
}
// Destructor 
template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}
/*
* full() const
*
* Verifica si el hash se encuentra lleno o no
*
* @param 
* return true o false
*/
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	if (count > size){
		return true;
	}
	return false;
}
/*
* indexOf(const Key k) const
*
* Retorna el indice del valor que se quiere busca. En caso
* que no se encuentre devuleve un -1
*
* param const Key k
* return indice del valor dentro del hash
*/
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
    unsigned int i, start;
    int c = 0;
    start = i = func(k) % size;
    do {
        if (keys[i] == k) {
            return i;
        }
        c = c + 1;
        i = (start + c * c) % size;
    } while (keys[i] != initialValue && start != i);
    return -1;
}
/*
* put(Key k, Value v)
*
* Inserta unn nuevo valor dentro de la tabla de hash a partir
* de una función cuadrática.
*
* param Key k, Value v
* return true si se inserto el elemento, false caso contrario
*/
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
    unsigned int i, start;
    int c = 0;
    long pos;
    pos = indexOf(k);
    if (pos != -1) {
        values[pos] = v;
        return true;
    }
    start = i = func(k) % size;
    do {
        if (keys[i] == initialValue) {
            keys[i] = k;
            values[i] = v;
            count++;
            return true;
        }
        c = c + 1;
        i = (start + c * c) % size;
    } while (c < size);
    return false;
}
/*
 * contains(const Key k) const
 *
 * Verifica si la key se encuentra en la tabla de hash
 *
 * param const Key k
 * return true si se encuentra, false si no se encuentra 
 */
template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;
	pos = indexOf(k);
	return (pos != -1);
}
/*
* get(const Key k)
* 
* Recupera el valor correspoendiente a la llave en 
* la tabla de hash
*
* param (const Key k)
* return valor de la key correspondiente
*/
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	unsigned int i, start;
	long pos;
	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
}
/*
* clear()
* 
* Limpia toda la tabla de hash con su valor inicial
* 
* @param
* @return
*/
template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}
/*
* toString() const
* 
* Concatena todos las keys, valores e indices de la taabla de 
* hash en un stringstream paraa luuego retornarlo en un string.
* Este string no toma en cuenta el valor inicial
* 
* @param
* return string con keys, valores e indices de la tabla de hash
*/
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (unsigned int i = 0; i < size; i++) {
		if (keys[i] != initialValue) {
			aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
		}
	}
	return aux.str();
}
#endif /* HASH_H_ */