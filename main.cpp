#include <iostream>
#include <dirent.h>
#include <vector>
#include <regex>
#include <sys/stat.h>
#include <iomanip>
#include "poscar.h"

using namespace std;

int main() {

    // ディレクトリ取得
    vector<int> dirnames;
    regex re("\\d+");
    DIR *dp;        // pointer for directory
    dirent *entry;  // entry point returned by readdir()

    dp = opendir("./");
    if (dp == NULL) {
        cout << "No Directory" << endl;
        return -1;
    }
    do {
        entry = readdir(dp);
        if (entry != NULL) {
            if (entry->d_type == DT_DIR) {
                if (regex_match(entry->d_name, re)) {
                    dirnames.push_back(stoi(entry->d_name));
                }
            }
        }
    } while (entry != NULL);

    int maxdirnum = *max_element(dirnames.begin(), dirnames.end());
    char lastdirname_c[8];
    sprintf(lastdirname_c, "%02d", maxdirnum);
    string lastdirname = string(lastdirname_c);

    // read POSCAR
    poscar p00("00/POSCAR");
    if (!p00.isReady()) {
        cout << "00/POSCAR was not read." << endl;
        return -1;
    }
    poscar pnn(lastdirname + "/POSCAR");
    if (!pnn.isReady()) {
        cout << lastdirname + "/POSCAR was not read." << endl;
        return -1;
    }

    // delta POSCAR
    poscar delta(p00, pnn, maxdirnum);

    // make directory
    for (int i = 1; i < maxdirnum; i++) {
        char dirname_c[8];
        sprintf(dirname_c, "%02d", i);
        string dirname = string(dirname_c);
        const char *dirname_cc = dirname_c;
        mkdir(dirname_cc, 0755);

        // make poscar
        ofstream fout(dirname + "/POSCAR");
        if (!fout) {
            cout << "Error during making " + dirname + "/POSCAR!" << endl;
            return -1;
        }

        fout << delta.getTitle() << endl;
        fout << "   "  << fixed << setw(18) << setprecision(16) << p00.getScale() + delta.getScale() * i << endl;
        fout << "    " << fixed << setw(19) << setprecision(16) << p00.getLattice(0) + delta.getLattice(0) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(1) + delta.getLattice(1) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(2) + delta.getLattice(2) * i << endl;
        fout << "    " << fixed << setw(19) << setprecision(16) << p00.getLattice(3) + delta.getLattice(3) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(4) + delta.getLattice(4) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(5) + delta.getLattice(5) * i << endl;
        fout << "    " << fixed << setw(19) << setprecision(16) << p00.getLattice(6) + delta.getLattice(6) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(7) + delta.getLattice(7) * i
             << "   "  << fixed << setw(19) << setprecision(16) << p00.getLattice(8) + delta.getLattice(8) * i << endl;
        fout << "   "  << delta.getElementsAsString() << endl;
        fout << "   "  << delta.getAtomNumsAsString() << endl;
        fout << "Direct" << endl;
        for (int j = 0; j < delta.getAtomNum(); j++) {
            fout << " " << fixed << setw(19) << setprecision(16) << p00.getCood(0 + 3*j) + delta.getCood(0 + 3*j) * i
                 << " " << fixed << setw(19) << setprecision(16) << p00.getCood(1 + 3*j) + delta.getCood(1 + 3*j) * i
                 << " " << fixed << setw(19) << setprecision(16) << p00.getCood(2 + 3*j) + delta.getCood(2 + 3*j) * i << endl;
        }

    }

    return 0;
}