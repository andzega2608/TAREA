/*
 * Tarea #5
 *
 * Fecha: 05/10/2024
 * Autor: Andrés Ignacio Zegales Taborga
 * Matricula: A01711365
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;
	TreeNode<T>* succesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
    void level(std::stringstream&);
    void aux_level(std::stringstream&, int);
    int n_height();
    void ancestors(T val, std::stringstream&);
    int levelamI(T, int);
	friend class BST<T>;
};
// Constructor por default
template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}
// Constructor por parámetros
template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri)
	: value(val), left(le), right(ri) {}
/*
* add(T val)
*
* Crea una nuevo nodo y lo agrega al arbol que ordena los nodos
* acorde al valor
*
* param T val
* @return
*/
template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}
/*
* find(T val)
*
* Busca dentro del arbol y revisa la ubicacion donde está ese nodo
*
* param T val
* return true o false
*/
template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
}
/*
* inorder(std::stringstream &aux) const
*
* Concatena el árbol, en un stringstream y lo ordena
* acorde a inorder
*
* param stringstream &aux
* @return
*/
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}
/*
* preorder(std::stringstream &aux) const
*
* Concatena el árbol, en un stringstream y lo ordena
* acorde a preorder
*
* param stringstream &aux
* @return
*/
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}
/*
* postorder(std::stringstream &aux) const
*
* Concatena el árbol, en un stringstream y lo ordena
* acorde a postorder
*
* param stringstream &aux
* @return
*/
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
    if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	aux << value << " ";
}
/*
* level(std::stringstream &aux)
*
* Concatena el árbol, en un stringstream y lo ordena
* acorde a los nivel de cada nodo
*
* param stringstream &aux
* @return
*/
template <class T>
void TreeNode<T>::level(std::stringstream &aux) {
    int n_level = n_height();
    for (int i = 1; i < n_level + 1; i++) {
        aux_level(aux, i);
    }
}
/*
* aux_level(std::stringstream &aux, int level)
*
* Concatena solo los nodos que se encuentran en nicho nivel especificado
*
* param stringstream &aux, int level
* @return
*/
template <class T>
void TreeNode<T>::aux_level(std::stringstream &aux, int level) {
    if (level == 1) {
        aux << value << " ";
    }
    if (left != 0) {
        left->aux_level(aux, level - 1);
    }
    if (right != 0) {
        right->aux_level(aux, level - 1);
    }
}
/*
* ancestors(T val, std::stringstream &aux)
*
* Concatena los ancestros de un nodo en específico
*
* param T val, std::stringstream &aux
* @return
*/
template <class T>
void TreeNode<T>::ancestors(T val, std::stringstream &aux) {
	if (val < value && left != 0){
        aux << value << " ";
        left->ancestors(val, aux);
	}
    else if (val > value && right != 0) {
        aux << value << " ";
        right->ancestors(val, aux);
    }
}
/*
* n_height()
*
* Retorna la profundidad máxima del árbol
*
* @param
* return profundidad máxima
*/
template <class T>
int TreeNode<T>::n_height(){
    if (left == 0 && right == 0){
        return 1;
    }
    else if (left != 0 && right == 0){
        return left->n_height() + 1;
    }
    else if (right != 0 && left == 0){
        return right->n_height() + 1;
    }
    int le = left->n_height() + 1;
    int ri = right->n_height() + 1;
    if (le > ri){
        return le;
    }
    else {
        return ri;
    }
}
/*
* levelamI(T val, int nivel)
*
* Indica en que nivel esta el nodo que se quiere buscar
*
* param T val, int nivel
* return nivel donde se encuentra el nodo
*/
template <class T>
int TreeNode<T>::levelamI(T val, int nivel) {
    if (val == value){
        return nivel;
    }
    if (val < value && left != 0){
        return left->levelamI(val, nivel+1);
    }
    else if (val > value && right != 0){
        return right->levelamI(val, nivel+1);
    }
}

template <class T>
class BST {
private:
	TreeNode<T> *root;
public:
	BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	std::string inorder() const;
	std::string preorder() const;
	std::string postorder() const;
	std::string level() const;
	std::string visit();
	int height();
	std::string ancestors(T);
	int whatlevelamI(T);
};
// Constructor por default
template <class T>
BST<T>::BST() : root(0) {}
/*
* empty() const
*
* Revisa si el arbol esta vacio
*
* @param
* return true o false
*/
template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}
/*
* add(T val)
*
* Añade el valor en el lugar correspondiente
*
* param T val
* @return
*/
template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new TreeNode<T>(val);
	}
}
/*
* find(T val)
*
* Busca el valor corresponediente
*
* param T val
* return true o false
*/
template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}
/*
* inorder()
*
* Devuelve un string con los nodos concatenados
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}
/*
* preorder()
*
* Devuelve un string con los nodos concatenados
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}
/*
* postorder()
*
* Devuelve un string con los nodos concatenados
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->postorder(aux);
		std::string aux2 = aux.str();
		aux2.pop_back();
		aux.str("");
		aux << aux2;
	}
	aux << "]";
	return aux.str();
}
/*
* level()
*
* Devuelve un string con los nodos concatenados
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::level() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->level(aux);
		std::string aux2 = aux.str();
		aux2.pop_back();
		aux.str("");
		aux << aux2;
	}
	aux << "]";
	return aux.str();
}
/*
* visit()
*
* Devuelve un string con los despliegues, es decir, inorder
* preorder, postorder y level
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::visit() {
    std::stringstream aux;
    aux << preorder() << "\n" << inorder() << "\n" << postorder() 
	    << "\n" << level();
    return aux.str();
}
/*
* heigh()
*
* Devuelve un entero con la profundida maxima
*
* @param
* return profundidad maxima
*/
template <class T>
int BST<T>::height(){
    if(!empty()){
        return root->n_height();
    }
    else {
        return 0;
    }
}
/*
* ancestor()
*
* Devuelve un string con los ancestros de un nodo concatenados
*
* @param
* return string concatenado
*/
template <class T>
std::string BST<T>::ancestors(T val){
	std::stringstream aux;
	aux << "[";
	if (root->find(val) == true) {
		root->ancestors(val, aux);
		std::string aux2 = aux.str();
		aux2.pop_back();
		aux.str("");
		aux << aux2;
	}
	else {
        aux << "";
	}
	aux << "]";
	return aux.str();
}
/*
* whatlevelamI()
*
* Devuelve un entero indicando en que nivel se encuentra dicho valor
*
* param T val
* return entero donde se encuentra dicho valor
*/
template <class T>
int BST<T>::whatlevelamI(T val){
    if (!empty()){
        return root->levelamI(val, 1);
    }
    else {
        return -1;
    }
}

#endif /* BST_H_ */
