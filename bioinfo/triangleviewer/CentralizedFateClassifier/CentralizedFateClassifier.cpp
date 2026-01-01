#include "GeneTreeConstructor.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

    //cout << "You have entered " << argc
        //<< " arguments:" << "\n";
    string s;
    string proteinfile;
    vector<float> fates_variables;
    fates_variables.resize(13);
    float g[3], a[3], b[3];
    if (argc > 1)
        for (int i = 0; i < 2; ++i) {
            //cout << argv[i] << "\n";
            s = argv[i];
        }
    //cout << argv[1];
    if (s == "-h") {
        cout << "there are two modes:" << endl;
        cout << endl;
        cout << "1) CentralizedFateClassifier -m default -csvfile" << endl;
        cout << "-csvfile: file list of proteins" << endl;
        cout << "Outputs: One newick gene Tree and Two CSV file which are all combinations probabality and avrage probability" << endl;
        cout << endl;
        cout << "2) CentralizedFateClassifier -m triangleviewer gm gh gw am ah aw bm bh bw" << endl;
        cout << "Outputs: CSV file with all of the probabilities and intermediate values like igs and pa and pb" << endl;
    }
    else if (s == "-m") {
        s = argv[2];
        if (s == "default") {
            proteinfile = argv[3];
            WritetoCSV(proteinfile);
            cout << "done!" << endl;
        }
        else if (s == "triangleviewer") {
            //cout << "triangleveiwer" << endl;
            for (int i = 0; i < 3; i++) {
                g[i] = stof(argv[3 + i]);
                //cout << g[i];
            }
            for (int i = 0; i < 3; i++) {
                a[i] = stof(argv[6 + i]);
                //cout << a[i];
            }
            for (int i = 0; i < 3; i++) {
                b[i] = stof(argv[9 + i]);
                //cout << b[i];
            }
            fates_variables = ProbabilitiesCalculation(g, a, b);
                cout << "P_subfunc=" << fates_variables[0] << endl
                << "P_cons=" << fates_variables[1] << endl
                << "P_neo=" << fates_variables[2] << endl
                << "P_pseudo=" << fates_variables[3] << endl
                << "P_spec=" << fates_variables[4] << endl
                << "ig_a=" << fates_variables[5] << endl
                << "ig_b=" << fates_variables[6] << endl
                << "ia_g=" << fates_variables[7] << endl
                << "ib_g=" << fates_variables[8] << endl
                << "ig_a_plus_b=" << fates_variables[9] << endl
                << "ia_plus_b_g=" << fates_variables[10] << endl
                << "pa=" << fates_variables[11] << endl
                << "pb=" << fates_variables[12] << endl;
                cout << "done!" << endl;
        }
    }
    else {
        // operator is doesn't match any case constant (+, -, *, /)
        //cout << "Error! The operator is not correct" << endl;
        cout << "Use -h to help!" << endl;
    }


    return 0;
}
