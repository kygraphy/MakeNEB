//
// Created by K.Y. on 2018/01/25.
//

#include "poscar.h"

poscar::poscar() {

}

poscar::poscar(string filename) {
    readPoscar(filename);
}


poscar::poscar(poscar p1, poscar p2, int num) {

    title = p1.getTitle();
    elements = p1.getElements();
    atomNums = p1.getAtomNums();
    atomNum = setAtomNum();

    scale = (p2.getScale() - p1.getScale()) / (double)num;

    for (int i = 0; i < 9; i++) {
        lattice[i] = (p2.getLattice(i) - p1.getLattice(i)) / (double)num;
    }

    for (int i = 0; i < atomNum; i++) {

        // choose direction of minimum distance.
        double cood1[3];
        cood1[0] = (p2.getCood(3*i) - p1.getCood(3*i)) / (double)num;
        cood1[1] = (p2.getCood(3*i+1) - p1.getCood(3*i+1)) / (double)num;
        cood1[2] = (p2.getCood(3*i+2) - p1.getCood(3*i+2)) / (double)num;

        double cood2[3];
        cood2[0] = (p2.getCood(3*i) - 1.0 - p1.getCood(3*i)) / (double)num;
        cood2[1] = (p2.getCood(3*i+1) - 1.0 - p1.getCood(3*i+1)) / (double)num;
        cood2[2] = (p2.getCood(3*i+2) - 1.0  - p1.getCood(3*i+2)) / (double)num;

        coods.push_back(abs(cood1[0]) <= abs(cood2[0]) ? cood1[0] : cood2[0]);
        coods.push_back(abs(cood1[1]) <= abs(cood2[1]) ? cood1[1] : cood2[1]);
        coods.push_back(abs(cood1[2]) <= abs(cood2[2]) ? cood1[2] : cood2[2]);

    }

    ready = true;
}

poscar::~poscar() {

}

bool poscar::readPoscar(string filename) {

    ifstream fin(filename);
    if (!fin) {
        cout << "No " << filename << "!!" << endl;
        return false;
    }

    string buf;
    int linenum = 1;
    while (getline(fin, buf)) {
        if (linenum == 1) {
            title = buf;

        } else if (linenum == 2) {
            scale = stod(buf);

        } else if (linenum == 3) {
            stringstream ss;
            ss << buf;
            ss >> lattice[0] >> lattice[1] >> lattice[2];

        } else if (linenum == 4) {
            stringstream ss;
            ss << buf;
            ss >> lattice[3] >> lattice[4] >> lattice[5];

        } else if (linenum == 5) {
            stringstream ss;
            ss << buf;
            ss >> lattice[6] >> lattice[7] >> lattice[8];

        } else if (linenum == 6) {
            stringstream ss;
            ss << buf;
            while (!ss.eof()) {
                string tmp;
                ss >> tmp;
                elements.push_back(tmp);
            }

        } else if (linenum == 7) {
            stringstream ss;
            ss << buf;
            while (!ss.eof()) {
                int tmp;
                ss >> tmp;
                atomNums.push_back(tmp);
            }
            atomNum = setAtomNum();

        } else if (linenum >= 9 && linenum < atomNum + 9) {
            stringstream ss;
            double cood[3] = {};
            ss << buf;
            ss >> cood[0] >> cood[1] >> cood[2];
            coods.push_back(cood[0]);
            coods.push_back(cood[1]);
            coods.push_back(cood[2]);

        }

        linenum++;
    }

    ready = true;
    return true;
}

int poscar::setAtomNum() {
    int sum = accumulate(atomNums.begin(), atomNums.end(), 0);
    return sum;
}

bool poscar::isReady() {
    return ready;
}

vector<string> poscar::getElements() {
    return elements;
}

vector<int> poscar::getAtomNums() {
    return atomNums;
}

double poscar::getScale() {
    return scale;
}

double poscar::getLattice(int num) {
    return lattice[num];
}

double poscar::getCood(int num) {
    return coods[num];
}

string poscar::getTitle() {
    return title;
}

string poscar::getElementsAsString() {
    string elementStr;
    for (auto it = begin(elements); it != end(elements); ++it) {
        elementStr += *it + "  ";
    }
    return elementStr;
}

string poscar::getAtomNumsAsString() {
    string atomNumStr;
    for (auto it = begin(atomNums); it != end(atomNums); ++it) {
        atomNumStr += to_string(*it) + "  ";
    }
    return atomNumStr;
}

int poscar::getAtomNum() {
    return atomNum;
}




