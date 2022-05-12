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
        std::cout << "Entrez un nombre entier:";
        std::cin >> nombreATester;
        if (nombreATester == -1) {
            std::cout << "\ngoodbye";
            return 0;
        }
        int i = nombreATester;
        while (!isPrime(i)) {
            i++;
        }
        std::cout << "le prochain nombre entier est " << i << "\n";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
