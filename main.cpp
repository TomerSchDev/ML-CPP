#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "LiniarAlgebra.h"
#include "vector"
#include "ML.h"
#include <fstream>
#include <memory>
#include <string>

struct data_point {
    Vector *x;
    int y;

    data_point(Vector *v, int r) {
        x = v;
        y = r;
    }

    data_point(data_point *d) {
        x = new Vector(d->x);
        y = d->y;
    }
};
using namespace std;



double *fromVectorToArray(vector<double> v) {
    double *pInt = new double[v.size()];
    for (int i = 0; i < v.size(); i++) {
        pInt[i] = v[i];
    }
    return pInt;
}

vector<data_point *> *get_data(string file_path) {
    ifstream file;
    file.open(file_path);
    string line;
    auto *data = new vector<data_point *>;
    while (!file.eof()) {
        file >> line;
        vector<double> x;
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
        auto *v = new Vector(x.size(), fromVectorToArray(x));
        auto dataPoint = new data_point(v, y);
        data->push_back(dataPoint);
    }
    file.close();
    return data;
}

void presptronCheck() {
    clock_t start = clock();
    vector<data_point *> *data = get_data("data.txt");
    srand(time(NULL));
    Perceptron p(3, 5);
    int train = 240;
    cout << "Start Train" << endl;
    p.train(new vector<data_point *>(data->begin(), data->begin() + train));
    cout << "Finished Train" << endl;
    double r = p.test(new vector<data_point *>(data->begin() + train + 1, data->end()));
    cout << r << endl;
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

void NNcheck() {
    clock_t start = clock();
    vector<data_point *> *data = get_data("nn_data_full.txt");
    srand(time(NULL));
    NN nn(10, 784, 3, 100, new Sigmoid());
    double train = 0.8;
    int ammount = data->size() * train;
    cout << "Start Train" << endl;
    nn.train(new vector<data_point *>(data->begin(), data->begin() + ammount));
    cout << "Finished Train" << endl;
    double r = nn.test(new vector<data_point *>(data->begin() + ammount + 1, data->end()));
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;

}

int main() {
    //NNcheck();
    //presptronCheck();
    shared_ptr<Matrix*> start = std::make_shared<Matrix*>(new Matrix(5,5));
    cout<<*start<<endl;
    return 0;
}
