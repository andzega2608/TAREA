/*
 * Tarea #8
 *
 * Fecha: 06/11/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    private:
        int edgesList;
        int edgesMat;
        int nodes;
        vector<int> *adjList;
        int *adjMatrix;
    public:
        Graph(int);
        Graph();
        void addEdgeAdjList(int, int);
        void addEdgeAdjMatrix(int, int);
        string printAdjList();
        string printAdjMat();
        string printAdjMat_clean();
        string DFS(int, int);
        string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
        string BFS(int, int);
        string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
        string print_visited(list<int>);
        string print_path(vector<vector<int>>&,int ,int);
        bool contains(list<int>, int);
        void sortAdjList();
        void loadGraphList(string, int);
        void loadGraphMat(string, int, int);
};
/*
* loadGraphList(string string_nodos, int a)
*
* Inicializa una lista de adyancencia para el grafo a partir
* de un string. De la misma manera el valor entero
* sirve para establecer la cantidad de nodos
*
* param (string string_nodos, int a)
* @return
*/
void Graph::loadGraphList(string string_nodos, int a) {
    adjList = new vector<int>[a];
    nodes = a;
    int u, v;
    char ignore;
    istringstream ss(string_nodos);
    while (ss >> ignore >> u >> ignore >> v >> ignore) {
        addEdgeAdjList(u, v);
    }
    sortAdjList();
}
/*
* loadGraphList(string string_nodos, int a)
*
* Inicializa una matriz de adyancencia para el grafo a partir
* de un string. De la misma manera los valores enteros hacen
* referencia al numero de filas y columnas de la matriz
*
* param (string string_nodos, int a)
* @return
*/
void Graph::loadGraphMat(string string_nodos, int a, int b) {
    adjMatrix = new int[a * b]();
    nodes = a;
    int u, v;
    char ignore;
    istringstream ss(string_nodos);
    while (ss >> ignore >> u >> ignore >> v >> ignore) {
        addEdgeAdjMatrix(u, v);
    }
}
// Constructor por default
Graph::Graph() {
	edgesList = edgesMat = 0;
}
// Constructor por parametros
Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}
/*
* addEdgeAdjList(int u, int v)
*
* Anade una nueva relacion existe entre los diversos nodos
* a la lista de adyacencia
*
* param (int u, int v)
* @return
*/
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}
/*
* addEdgeAdjMatrix(int u, int v)
*
* Anade una nueva relacion existe entre los diversos nodos
* a la matriz de adyacencia
*
* param (int u, int v)
* @return
*/
void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}
/*
* printAdjList()
*
* Retorna un string con las conexiones de cada
* vertice del grafo acorde a la lista de adyacencia
*
* @param
* return string
*/
string Graph::printAdjList(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
        aux << "vertex " << i << " :";
        for (int j = 0; j < adjList[i].size(); j ++){
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}
/*
* sortAdjList()
*
* Ordena los nodos adyacentes de cada vertice
* en la lista de adyacencia
*
* @param
* @return
*/
void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}
/*
* printAdjMat()
*
* Retorna un string con las conexiones de cada
* vertice del grafo acorde a la matriz de adyacencia
*
* @param
* return string
*/
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
        }
    }
	return aux.str();
}
/*
* printAdjMat_clean()
*
* Retorna un string que representa
* la matriz de adyacencia del grafo
*
* @param
* return string
*/
string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
    }
	return aux.str();
}
/*
* DFS(int start, int goal)
*
* Realiza una búsqueda en profundidad desde el nodo start
* hasta el nodo goal
*
* param nodo inicial, nodo final
* string con los nodos visitados y el camino
*/
string Graph::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    st.push(start);
    string ans = depthHelper(start, goal, st, visited, paths);
    ans = ans + print_path(paths, start, goal);
    return ans;
}
/*
* depthHelper(int current, int goal, stack<int> &st,
* list<int> &visited, vector<vector<int>> &paths)
*
* Función auxiliar recursiva para la busquedad de profundidad.
* Gestiona el stack y los caminos
*
* param int current, int goal, stack<int> &st,
  list<int> &visited, vector<vector<int>> &paths
* return string con el camino
*/
string Graph::depthHelper(int current,
    int goal,
	stack<int> &st,
	list<int> &visited,
	vector<vector<int>> &paths){
    if (current == goal) {
        return print_visited(visited);
    } else if (st.empty()) {
        return "node not found";
    } else {
        current = st.top();
        st.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                st.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
        }
        return depthHelper(current, goal, st, visited, paths);
    }
}
/*
* BFS(int start, int goal)
*
* Realiza una búsqueda en amplittud desde el nodo start
* hasta el nodo goal
*
* param nodo inicial, nodo final
* string con los nodos visitados y el camino
*/
string Graph::BFS(int start, int goal){
	queue<int> qu;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    qu.push(start);
    string ans = breadthHelper(start, goal, qu, visited, paths);
    ans = ans + print_path(paths, start, goal);
    return ans;
}
/*
* breadthHelper(int current, int goal, queue<int> &st,
* list<int> &visited, vector<vector<int>> &paths)
*
* Función auxiliar recursiva para la busquedad de Amplitud.
* Maneja la queue y los caminos
*
* param int current, int goal, queue<int> &st,
  list<int> &visited, vector<vector<int>> &paths
* return string con el camino
*/
string Graph::breadthHelper(int current,
    int goal,
	queue<int> &qu,
	list<int> &visited,
	vector<vector<int>> &paths){
	if (current == goal) {
        return print_visited(visited);
    } else if (qu.empty()) {
        return "node not found";
    } else {
        current = qu.front();
        qu.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                qu.push(adjList[current][i]);
                paths[adjList[current][i]].push_back(current);
            }
        }
        return breadthHelper(current, goal, qu, visited, paths);
    }
}
/*
* contains(list<int> ls, int node)
*
* Verifica si el nodo se encuentre en la lista de
* visitados
*
* param list<int> ls, int node
* return true o false
*/
bool Graph::contains(list<int> ls, int node){
	list<int>::iterator it;
	it = find(ls.begin(), ls.end(), node);
	if(it != ls.end())
		return true;
	else
		return false;
}
/*
* print_visited(list<int> q)
*
* Imprime la lista de nodos visitados
*
* param list<int> q
* string de los nodos vistados
*/
string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
    }
	return aux.str();
}
/*
* print_path(vector<vector <int>> &path,
  int start, int goal)
*
* Imprime el camino encontrado
*
* param vector<vector <int>> &path, int start, int goal
* string del camino encontrado
*/
string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif /* Graph_H_ */

