#include <iostream>
#include <fstream>
#include <iomanip>
#include "Matrix.h"
#include "LiniarAlgebra.h"
#include "vector"
#include "ML.h"
#include <string>
#include "map"

struct data_point {
    Vector x;
    int y;

    data_point(const Vector &v, int r) {
        x = Vector(v);
        y = r;
    }

    data_point(const data_point &d) {
        x = Vector(d.x);
        y = d.y;
    }
};
using namespace std;



double *fromVectorToArray(vector<double> v) {
    auto *pInt = new double[v.size()];
    for (int i = 0; i < v.size(); i++) {
        pInt[i] = v[i];
    }
    return pInt;
}

vector<data_point *> get_data(vector<double> x,std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    vector<data_point *> data;
    while (getline(file, line)) {
        int y;
        string temp;
        for (char c : line) {
            switch (c) {
                case (','):
                    x.push_back(stod(temp));
                    temp = "";
                    break;
                case ('?'):
                    y = stod(temp);
                    temp = "";
                    break;
                default:
                    temp += c;
                    break;
            }
        }
        data.push_back(new data_point(Vector(x.size(), vector<double>(x)), y));
        x.clear();
    }
    file.close();
    return data;
}

int main(int argc, char **argv) {
    vector<double> x;
    map<string, string> machineData;
    map<string, AbstractMachine *> machines;
    machineData["Perceptron"] = "data.txt";
    machineData["NN"] = "nn_data.txt";
    machines["Perceptron"] = new Perceptron(3, 5);
    Sigmoid s{};
    machines["NN"] = new NN(10, 784, 3, 160, s);
    clock_t start = clock();
    if (argc < 2) {
        return -1;
    }
    string type = argv[1];
    vector<data_point *> data = shuffleData(get_data(x,machineData[type]));
    srand(time(NULL));
    auto m = machines[type];
    int train = 0.8 * data.size();
    cout << "Start Train" << endl;
    m->train(vector<data_point *>(data.begin(), data.begin() + train));
    cout << "Finished Train" << endl;
    double r = m->test(vector<data_point *>(data.begin() + train + 1, data.end()));
    cout << r << endl;
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;

}
