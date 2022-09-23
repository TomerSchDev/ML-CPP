//
// Created by Tomer on 12/08/2022.
//

#include <random>
#include <iostream>
#include <cmath>
#include "LiniarAlgebra.h"


using namespace std;

struct data_point {
    Vector *x;
    int y;

    data_point(Vector *v, int r) {
        x = v;
        y = r;
    }

    data_point(const data_point &d) {
        x = d.x;
        y = d.y;
    }
};

vector<data_point *> shuffleData(const vector<data_point *> &v) {
    vector<data_point *> shuffled(v.begin(), v.end());
    shuffle(shuffled.begin(), shuffled.end(), random_device());
    return shuffled;
}

Matrix vectorMultiVector(const Vector &a, const Vector &b) {
    if (a.isTrans() == b.isTrans()) {
        std::cout << "Wrong trans in multi function between vector and vector" << std::endl;
        return {};
    }
    if (a.isTrans()) {
        if (a.getSize() != b.getSize()) {
            std::cout << "Wrong size in multi function between vector and vector" << std::endl;

        }
        int size = a.getSize();
        //matrix 1X1
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += a[i] * b[i];
        }
        vector<double> data;
        data.push_back(sum);
        vector<Vector> v;
        v.push_back(Vector(1, data));
        return {1, 1, v};
    } else {
        //matrix a.size rows X b.size cols
        unsigned int rowSize = b.getSize();
        unsigned int colsSize = a.getSize();
        vector<Vector>tempData;
        for (int i = 0; i < colsSize; i++) {
            vector<double>data;
            double c = a[i];
            for (int j = 0; j < rowSize; j++) {
                data.push_back(b[j] * c);
            }
            tempData.push_back(Vector(rowSize, data));
        }
        return {rowSize, colsSize, tempData};
    }
}

Vector multi(const Vector a, const Matrix b) {
    if (b.getRows() != a.getSize() || !a.isTrans()) {
        std::cout << "Wrong sizes in vectorMultiVector function between vector and matrix" << std::endl;
        return {};
    }
    const unsigned int size = b.getCols();
    vector<double> data;
    for (int i = 0; i < size; i++) {
        Vector col = b[i];
        double sum = 0;
        for (int j = 0; j < a.getSize(); j++) {
            double r = a[j];
            double c = col[j];
            sum += r * c;
        }
        data.push_back(sum);
    }
    return {size, data, true};
}

double dot(const Vector &a, const Vector &b) {
    if (a.getSize() != b.getSize()) {
        return -1;
    }
    double sum = 0;
    const unsigned int size = a.getSize();
    for (int i = 0; i < size; i++) {
        sum += a[i] * b[i];

    }
    return sum;
}

Vector dot(const Matrix &a, const Vector &b) {
    if (a.getRows() != b.getSize()) {
        std::cout << "Wrong sizes in dot function with matrix and vector" << std::endl;
        return {};
    }
    const unsigned int size = a.getCols();
    vector<double> tempData;
    for (int i = 0; i < size; i++) {
        Vector v = a[i];
        tempData.push_back(dot(v, b));
    }
    return {size, tempData};
}

Vector dot(const Matrix &a, const Vector &b, bool print) {
    if (a.getRows() != b.getSize()) {
        return {};
    }
    const unsigned int size = a.getCols();
    vector<double> tempData;
    for (int i = 0; i < size; i++) {
    }
    for (int i = 0; i < size; i++) {
        auto col = a[i];
        if (print) {
            cout << col << endl;
        }
        tempData.push_back(dot(col, b));
    }
    return {size, tempData};
}

int argMax(const Vector &v) {
    double max = v[0];
    int index = 0;
    for (int i = 1; i < v.getSize(); i++) {
        double temp = v[i];
        if (temp > max) {
            max = temp;
            index = i;
        }
    }
    return index;
}

Vector softMax(const Vector &x) {
    double sum = 0;
    unsigned int size = x.getSize();
    for (int i = 0; i < size; i++) {
        sum += exp(x[i]);
    }
    vector<double> output;
    for (int i = 0; i < size; i++) {
        output.push_back(exp(x[i]) / sum);
    }
    return {size, output};
}
