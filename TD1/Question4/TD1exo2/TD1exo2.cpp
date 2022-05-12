// TD1exo2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


void trieur(int(&tableau)[10]) {//TODO: commenter ce code.
    int buffer;
    int minimum;
    int minimumIndex;
    for (int i = 0; i < 10; i++) {
        minimum = tableau[i];
        minimumIndex = i;
        for (int j = i; j < 10; j++) {
            if (tableau[j] < minimum){
                minimum = tableau[j];
                minimumIndex = j;
            }
        }
        buffer = minimum;
        tableau[minimumIndex] = tableau[i];
        tableau[i] = buffer;
    }
}

int main()
{
    int tableau[10];
    int nombre;
    std::cout << "entrez 10 nombres entiers";
    for (int i = 0; i < 10; i++) {
        std::cin >> nombre;
        tableau[i] = nombre;
    }
    trieur(tableau);
    for (int i = 0; i < 10; i++) {
        std::cout << tableau[i]<<"  ";
    }

}
