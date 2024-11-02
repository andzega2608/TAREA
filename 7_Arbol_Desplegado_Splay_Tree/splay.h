/*
 * Tarea #7
 *
 * Fecha: 02/11/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
    private:
        T value;
        Node *left, *right, *parent;
        Node<T>* succesor();
        Node<T>* rot_right(Node<T>*);
        Node<T>* rot_left(Node<T>*);

    public:
        Node(T);
        Node(T, Node<T>*, Node<T>* ,Node<T>*);
        Node<T>* add(T);
        Node<T>* find(T);
        Node<T>* remove(T);
        void removeChilds();
        void inorder(std::stringstream&) const;
        void print_tree(std::stringstream&) const;
        void preorder(std::stringstream&) const;
        Node<T>* splay(Node<T>*, Node<T>*);
        friend class SplayTree<T>;
};
// Constructor por default
template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}
// Constructor por parámetros
template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}
/*
* add(T val)
*
* Añade el nuevo valor siguiendo las reglas de un BST
*
* param T val
* return Node<T>* Puntero al nodo con el valor añadido
*/
template <class T>
Node<T>* Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			return left->add(val);
		} else {
			left = new Node<T>(val);
			left->parent = this;
			return left;
		}
	} else {
		if (right != 0) {
			return right->add(val);
		} else {
			right = new Node<T>(val);
			right->parent = this;
			return right;
		}
	}
}
/*
* find(T val)
*
* Busca un nodo acorde al valor dado
*
* param T val
* return Node<T>* Puntero al nodo que contiene
* el valor a buscar
*/
template <class T>
Node<T>* Node<T>::find(T val) {
	if (val == value) {
		return this;
	} else {
		if (val < value) {
			if (left != 0) {
				return left->find(val);
			} else {
				return 0;
			}
		} else {
			if (right != 0) {
				return right->find(val);
			} else {
				return 0;
			}
		}
	}
}
/*
* succesor()
*
* Encuentra el sucesor en el árbol
*
* @param
* return Node<T>* Puntero al sucesor del nodo actual
*/
template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;
	le = left;
	ri = right;
	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}
	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}
/*
* remove(T val)
*
* Elimina el nodo con el valor especificado
*
* param T val
* return Node<T>* Nuevo árbol luego de la eliminación
*/
template <class T>
Node<T>* Node<T>::remove(T val) {
	if (val < value) {
		if (left != 0) {
			left = left->remove(val);
		}
	} else if (val > value) {
		if (right != 0) {
			right = right->remove(val);
		}
	} else {
		if (left == 0 && right == 0) {
			delete this;
			return 0;
		} else if (left == 0) {
			Node<T>* temp = right;
			right->parent = parent;
			delete this;
			return temp;
		} else if (right == 0) {
			Node<T>* temp = left;
			left->parent = parent;
			delete this;
			return temp;
		} else {
			Node<T>* succ = right->succesor();
			value = succ->value;
			right = right->remove(succ->value);
		}
	}
	return this;
}
/*
* removeChilds()
*
* Elimina todos los nodos hijos recursivamente
*
* @param
* @return
*/
template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}
/*
* rot_right(Node<T>* x)
*
* Realiza una rotación a la derecha en el árbol
*
* param Node<T>* x nodo donde se realiza la rotación
* return Node<T>* nuevo árbol luego de la rotación
*/
template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}
/*
* rot_right(Node<T>* x)
*
* Realiza una rotación a la izquierda en el árbol
*
* param Node<T>* x nodo donde se realiza la rotación
* return Node<T>* nuevo árbol luego de la rotación
*/
template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}
/*
* splay(Node<T>* root, Node<T>* x)
*
* Realiza las rotaciones de zig zig, zag zag, zig zag o zag ziz
* con el fin de llevar el último valor añadido a la raíz o el
* valor que se quiere buscar
*
* param Node<T>* root raíz inicial del árbol,
* Node<T>* x nodo a llevar a la raíz
* return Node<T>* nodo raíz tras las rotaciones
*/
template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){
		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		} else {
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			} else if (p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			} else if (p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			} else {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}
/*
* inorder(std::stringstream &aux) const
*
* Recorre y concatena el árbol en inorden y almacena en aux
*
* param std::stringstream &aux para almacenar el recorrido
* @return
*/
template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
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
* print_tree(std::stringstream &aux) const
*
* Imprime la estructura del árbol en aux
*
* param std::stringstream &aux para almacenar la estructura
* del árbol
* @return
*/
template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";
	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}
/*
* preorder(std::stringstream &aux) const
*
* Concatena los valores del árbol acorde a preorder
*
* param std::stringstream &aux para almacenar los valores
* @return
*/
template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
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

template <class T>
class SplayTree {
    private:
        Node<T> *root;
    public:
        SplayTree();
        ~SplayTree();
        bool empty() const;
        void add(T);
        bool find(T);
        void remove(T);
        void removeAll();
        std::string inorder() const;
        std::string print_tree() const;
        std::string preorder() const;
};
// Constructor por default
template <class T>
SplayTree<T>::SplayTree() : root(0) {}
// Destructor por default
template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}
/*
* empty() const
*
* Revisa si el árbol está vacío
*
* @param
* return true o false
*/
template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}
/*
* add(T val)
*
* Añade el valor al árbol y luego realiza
* las rotaciones para que el último valor se encuentre
* en la raíz
*
* param T val
* @return
*/
template<class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
        Node<T>* added = root->add(val);
		root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}
/*
* remove(T val)
*
* Elimina el valor en el árbol y luego realiza
* las rotaciones para que el padre del valor a eliminar
* se encuentre en la raíz
*
* param T val
* @return
*/
template <class T>
void SplayTree<T>::remove(T val) {
    if (root != 0) {
        if (val == root->value) {
            Node<T> *succ = root->succesor();
            if (succ != 0) {
                succ->left = root->left;
                succ->right = root->right;
                succ->parent = 0;
                if (succ->left)
                    succ->left->parent = succ;
                if (succ->right)
                    succ->right->parent = succ;
            }
            delete root;
            root = succ;
        } else {
            Node<T>* p = root->find(val);
            if (p != 0) {
                Node<T>* parent = p->parent;
                p = parent->remove(val);
                if (p) {
                    root = root->splay(root, p);
                }
            }
        }
    }
}
/*
* removeAll()
*
* Limpia todo el árbol
*
* @param
* @return
*/
template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}
/*
* find(T val)
*
* Busca el valor dentro del árbol y luego realiza
* las rotaciones para que el valor buscado se encuentre
* en la raíz
*
* param T val
* return true o false
*/
template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}
/*
* inorder() const
*
* Concatena los valor del árbol dentro de un string
* acorde a inordder
*
* @param
* return std::string concatenado de valores del árbol
*/
template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}
/*
* print_tree() const
*
* Devuelve la estructura completa del árbol
*
* @param
* return std::string: estructura del árbol
*/
template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;
	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}
/*
* inorder() const
*
* Concatena los valor del árbol dentro de un string
* acorde a preordder
*
* @param
* return std::string concatenado de valores del árbol
*/
template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* SplayTree_H_ */
