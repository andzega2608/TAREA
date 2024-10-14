/*
 * Tarea #1
 *
 * Fecha: 16/08/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include <iostream>

class Funciones {
    public:
        // O(n) en todos los casos el ciclo se repite n veces
        int sumaIterativa(int n){
            long suma = 0;
            if (n > 0){
                for (int i=1; i<=n; i++){
                    suma = suma + i;
                }
                return suma;
            }
            else {
                return 0;
            }
        }
        // O(n) recursion de cabeza
        int sumaRecursiva(int n){
            if (n == 0){
                return 0;
            }
            else {
                return n + sumaRecursiva(n-1);
            }
        }
        // O(1) en todos los casos solo se realiza una instruccion
        int sumaDirecta(int n){
            if (n > 0){
                return n * (n + 1) / 2;
            }
            else {
                return 0;
            }
        }
};

#endif /* FUNCIONES_H_ */
