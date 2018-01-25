//
// Created by K.Y. on 2018/01/25.
//

#ifndef MAKENEB_POSCAR_H
#define MAKENEB_POSCAR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <cmath>

using namespace std;

class poscar {
    bool ready = false;
    string title;
    double scale;
    double lattice[9];
    vector<string> elements;
    vector<int> atomNums;
    int atomNum;
    vector<double> coods;
    bool readPoscar(string filename);
    int setAtomNum();
public:
    poscar();
    poscar(string filename);
    poscar(poscar p1, poscar p2, int num);
    ~poscar();
    bool isReady();
    vector<string> getElements();
    vector<int> getAtomNums();
    double getScale();
    double getLattice(int num);
    double getCood(int num);
    string getTitle();
    string getElementsAsString();
    string getAtomNumsAsString();
    int getAtomNum();
};


#endif //MAKENEB_POSCAR_H
