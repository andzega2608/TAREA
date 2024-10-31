/*
 * Tarea #1
 *
 * Fecha: 16/08/2024
 * Autor: Andres Ignacio Zegales Taborga
 * Matricula: A01711365
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones {
    public:
        /*
        * sumaIterativa(int n)
        *
        * Suma de manera iterada con un ciclo for
        * O(n) en todos los casos el ciclo se repite n veces
        *
        * param número entero
        * return suma iterativa
        */
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
        /*
        * sumaRecursiva(int n)
        *
        * Suma de manera recursiva donde el caso es hasta
        * que el número sea igual a cero
        * O(n) recursion de cabeza
        *
        * param número entero
        * return suma iterativa
        */
        int sumaRecursiva(int n){
            if (n == 0){
                return 0;
            }
            else {
                return n + sumaRecursiva(n-1);
            }
        }
        /*
        * sumaRecursiva(int n)
        *
        * Suma de manera directa implementando una fórmula
        * O(1) en todos los casos solo se realiza una instruccion
        *
        * param número entero
        * return suma iterativa
        */
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
