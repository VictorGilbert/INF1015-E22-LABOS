// TD1exo1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n);i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int main()
{
    while (true) {
        int nombreATester;
        std::cout << "Entrez un nombre entier: ";
        std::cin >> nombreATester;
        if (nombreATester == -1) {
            std::cout << "\ngoodbye";
            return 0;//quite le programme, le reste de la fonction peut etre traité comme un else.
        }
        int i = nombreATester;
        while (!isPrime(i)) {
            i++; 
        }
        std::cout << "le prochain nombre premier est " << i << "\n";
    }
}
