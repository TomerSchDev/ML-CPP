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

class AbstractMachine {
public:
    virtual void train(const vector<data_point*> &data){};

    virtual double test(const vector<data_point*> &data){return -1;} ;
};



class Perceptron : public AbstractMachine {
public:
    double theta;
    Vector bias;
    Matrix w;

    Perceptron(int classes, int size) {
        this->theta = 0.1;
        this->bias = Vector(classes);
        this->w = Matrix(size, classes);
    };

    void train(const vector<data_point*> &data) override;

    double test(const vector<data_point*> &data) override;
};

class NN : public AbstractMachine {
    int num_hidden_layers;
    int neurons;
    int classes;
    double lr;
    ActivityFunction& function;
    Vector *bias;
    Matrix *ws;
    Vector *H;
    Vector *Z;
    Vector *dB;
    Matrix *dW;

public:
    NN(int classes, int size, int layers_number, int neurons, ActivityFunction &function): function(function) {
        this->function = function;
        this->neurons = neurons;
        this->num_hidden_layers = layers_number;
        this->bias = new Vector[layers_number + 1];
        this->ws = new Matrix[layers_number + 1];
        this->ws[0] = Matrix(size, neurons);
        this->bias[0] = Vector(neurons);
        for (int i = 1; i < this->num_hidden_layers; i++) {
            this->ws[i] = Matrix(neurons, neurons);
            this->bias[i] = Vector(neurons);
        }
        this->classes = classes;
        this->lr = 0.1;
        this->ws[layers_number] = Matrix(neurons, classes);
        this->bias[layers_number] = Vector(classes);
        this->H = new Vector[layers_number + 2];
        this->Z = new Vector[layers_number + 1];
        this->dB = new Vector[layers_number + 1];
        this->dW = new Matrix[layers_number + 1];
    }

    void train(const vector<data_point*> &data) override;

    void fprop(const Vector& x);

    void bprop(int real_y);

    void update();

    double test(const vector<data_point*> &data) override;
};

#endif //MLCPP_ML_H
