//
// Created by Tomer on 13/08/2022.
//

#ifndef MLCPP_ML_H
#define MLCPP_ML_H

#include "Vector.h"
#include "vector"
#include "LiniarAlgebra.h"
using namespace std;

class data_point;

class Perceptron {
public:
    double theta;
    int changing_rate;
    double multi;
    Vector *bias;
    Matrix* w;

    Perceptron(int classes,int size) {
        this->theta = 0.1;
        this->changing_rate = 50;
        this->multi = 0.5;
        this->bias = new Vector(classes);
        this->w=new Matrix(size,classes);
    };

    void train(vector<data_point *> *data);

    double test(vector<data_point *> *data);
};

#endif //MLCPP_ML_H
