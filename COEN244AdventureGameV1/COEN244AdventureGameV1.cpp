// COEN244AdventureGameV1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include "Level.h"
#include "Item.h"
#include "Game.h"
#include "AdventureException.h"

int main(int argc, char** argv) {
    using namespace std;

    ifstream mapFile;
    
    mapFile.open("level2.txt");
    
    Level l1(mapFile);


    try {
        l1.play();

    }
    catch (EscapedDungeonException e) {
        cout << e.toStr();
    }


    // l1.draw();
    /*
    Item sword = { "item/sword.txt" };
    cout << sword.getArt() << endl << sword.getName() << endl 
         << sword.getDescription();
         */

    //Game g;

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

