//
// Created by Tomer on 13/08/2022.
//

#ifndef MLCPP_ML_H
#define MLCPP_ML_H

#include "Vector.h"
#include "vector"
#include "LiniarAlgebra.h"
#include "Activation Functions.h"
using namespace std;

class data_point;

class Perceptron {
public:
    double theta;
    int changing_rate;
    double multi;
    Vector *bias;
    Matrix* w;

    Perceptron(int classes, int size) {
        this->theta = 0.1;
        this->changing_rate = 50;
        this->multi = 0.5;
        this->bias = new Vector(classes);
        this->w = new Matrix(size, classes);
    };

    void train(vector<data_point *> *data);

    double test(vector<data_point *> *data);
};

class NN {
    int num_hidden_layers;
    int neurons;
    int classes;
    double lr;
    const ActivityFunction *function;
    Vector **bias;
    Matrix **ws;
    Vector **H;
    Vector **Z;
    Vector **dB;
    Matrix **dW;


public:
    NN(int classes, int size, int layers_number, int neurons, const ActivityFunction *function) {
        this->function = function;
        this->neurons = neurons;
        this->num_hidden_layers = layers_number;
        this->bias = new Vector *[layers_number + 1];
        this->ws = new Matrix *[layers_number + 1];
        this->ws[0] = new Matrix(size, neurons);
        this->bias[0] = new Vector(neurons);
        for (int i = 1; i < this->num_hidden_layers; i++) {
            this->ws[i] = new Matrix(neurons, neurons);
            this->bias[i] = new Vector(neurons);
        }
        this->classes = classes;
        this->lr = 0.1;
        this->ws[layers_number] = new Matrix(neurons, classes);
        this->bias[layers_number] = new Vector(classes);
        this->H = new Vector *[layers_number + 2];
        this->Z = new Vector *[layers_number + 1];
        this->dB = new Vector *[layers_number + 1];
        this->dW = new Matrix *[layers_number + 1];
    }

    void train(vector<data_point *> *data);

    void fprop(Vector *x);

    void bprop(int real_y);

    void update();

    double test(vector<data_point *> *data);
};

#endif //MLCPP_ML_H
