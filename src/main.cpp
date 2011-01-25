/* 
 * File:   main.cpp
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:14 PM
 */

#include <iostream>
#include "Ai.h"
#include "AParser.hpp"

// --------
// bon il reste a faire le chainage arriere,
// l'idée serais de parcourire les BoolFunc et de trouver les combinaisons de lettres manquantes pour que la Node soit true
// --------
// actuellement on gere le cas A*B=C*D mais pas si l'expression de droite contient un/des OR
// c'est due au fait qu'on ne gere pas l'operateur unaire NOT ( "!A" => NOT(A) )
// voir si on peut modifier la façon dont les BoolFunc sont stocker et interpreté pour prendre en compte NOT

int main(int ac, char** av) {
    Ai topClass;
    std::string path;
    if (ac >= 2) {
        path = av[ac - 1];
    } else {
        std::cout << "base file path ?" << std::endl;
        std::cin >> path;
    }
    if (topClass.loadPath(path)) {
        topClass.forward();
        topClass.backward();
    }
    return 0;
}

