#define nElements 10
#include <iostream>


void trieur(int(&tableau)[nElements]) {
    int buffer; // utilise pour stocker les valeurs pour quelles ne soient pas ecrasee
    int minimum;
    int minimumIndex;
    for (int i = 0; i < nElements; i++) {

        minimum = tableau[i];                   //cette boucle ne sert qua trouver le minimum et son index
        minimumIndex = i;
        for (int j = i; j < nElements; j++) { 
            if (tableau[j] < minimum){
                minimum = tableau[j];
                minimumIndex = j;
            }
        }

        buffer = minimum;                   //une fois quon a ces valeurs, on echange. Cet alogrithme est inefficace et laid mais il est impose par les directives.
        tableau[minimumIndex] = tableau[i];
        tableau[i] = buffer;
    }
}

int main()
{
    int tableau[nElements];
    std::cout << "Entrez 10 nombres entiers: ";
    std::cin >> tableau[0]>> tableau[1]>> tableau[2]>> tableau[3]>> tableau[4]>>
                tableau[5]>> tableau[6]>> tableau[7]>> tableau[8]>> tableau[9];
    trieur(tableau);
    std::cout << "Voici le tableau trie : ";
    for (int i = 0; i < 10; i++) {
        std::cout << tableau[i]<<"  ";
    }

}
