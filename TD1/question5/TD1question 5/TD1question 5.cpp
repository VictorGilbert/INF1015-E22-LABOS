// TD1question 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct item {
    int quantite;
    string nom;
    string type;
    double prix;
};

int main()
{
    fstream newfile;
    newfile.open("inventaire.txt", ios::in);
    string ligne;
    while (getline(newfile, ligne)) {
        std::cout << ligne << "\n";
        std::stringstream test("this_is_a_test_string");
        std::string segment;
    }
}