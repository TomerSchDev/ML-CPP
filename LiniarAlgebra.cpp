//
// Created by Tomer on 12/08/2022.
//

#include <random>
#include <iostream>
#include "LiniarAlgebra.h"


using namespace std;

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

vector<data_point *> *shuffleData(const vector<data_point *> *v) {
    auto *shuffled = new vector<data_point *>;
    for (auto i : *v) {
        auto d = new data_point(i);
        shuffled->push_back(d);
    }
    shuffle(shuffled->begin(), shuffled->end(), random_device());
    return shuffled;
}

Matrix *multi(const Vector *a, const Vector *b) {
    if (a->getSize() != b->getSize() || a->isTrans() == b->isTrans()) {
        return nullptr;
    }
    const unsigned int size = a->getSize();
    if (a->isTrans()) {
        //matrix 1X1
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += (*a)[i] * (*b)[i];
        }
        double **data = new double *[1];
        data[0] = new double[1]{sum};
        return new Matrix(1, 1, data);
    } else {
        //matrix size X size
        Vector **tempData = new Vector *[size];
        for (int i = 0; i < size; i++) {
            double *data = new double[size];
            double c = (*b)[i];
            for (int j = 0; j < size; j++) {
                double r = (*a)[j];
                data[j] = r * c;
            }
            tempData[i] = new Vector(size, data);
        }
        return new Matrix(size, size, tempData);
    }
}

Vector *multi(const Vector *a, const Matrix *b) {
    if (b->getRows() != a->getSize() || !a->isTrans()) {
        return nullptr;
    }
    const unsigned int size = b->getCols();
    double *data = new double[size];
    for (int i = 0; i < size; i++) {
        Vector *col = (*b)[i];
        double sum = 0;
        for (int j = 0; j < a->getSize(); j++) {
            double r = (*a)[j];
            double c = (*col)[j];
            sum += r * c;
        }
        data[i] = sum;
    }
    return new Vector(size, data, true);
}

double dot(const Vector *a, const Vector *b) {
    if (a->getSize() != b->getSize()) {
        return -1;
    }
    double sum = 0;
    const unsigned int size = a->getSize();
    for (int i = 0; i < size; i++) {

        double aI = (*a)[i];
        double bI = (*b)[i];
        sum += aI * bI;

    }
    return sum;
}

Vector *dot(const Matrix *a, const Vector *b) {
    if (a->getRows() != b->getSize()) {
        return nullptr;
    }
    const int size =a->getCols();
    double *tempData = new double[size];
    for (int i = 0; i < size; i++) {
        auto col = (*a)[i];
        tempData[i] = dot(col, b);
    }
    return new Vector(size,tempData);
}

int argMax(const Vector *v) {
    double max = (*v)[0];
    int index = 0;
    for (int i = 1; i < v->getSize(); i++) {
        double temp = (*v)[i];
        if (temp > max) {
            max = temp;
            index = i;
        }
    }
    return index;
}
