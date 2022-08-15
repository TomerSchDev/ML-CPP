//
// Created by Tomer on 13/08/2022.
//

#include <iostream>
#include "ML.h"
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

int MAX_EPOCH = 10;

void Perceptron::train(vector<data_point *> *data) {
    for (int i = 0; i < MAX_EPOCH; i++) {
        vector<data_point *> *points = shuffleData(data);
        for (auto p:*points) {
            Vector *d = dot(this->w, p->x);
            Vector *f = *d + this->bias;
            int result = argMax(f);
            if (result != p->y) {
                auto diff = *(p->x) * this->theta;
                //strength real answer
                this->w=this->w->updatePlus(p->y, diff);
                this->bias=this->bias->updatePlus(p->y, this->theta);
                //subdue false result
                this->w=this->w->updatePlus(result, *diff * -1);
                this->bias=this->bias->updatePlus(result, -this->theta);

            }
        }
    }
}

double Perceptron::test(vector<data_point *> *data) {
    double success = 0;
    for (auto p:*data) {
        Vector *d = dot(this->w, p->x);
        Vector *f = *d + this->bias;
        int result = argMax(f);
        success += (result == p->y) ? 1 : 0;
    }
    return success / data->size();
}

void NN::train(vector<data_point *> *data) {
    int size=data->size();
    for (int i = 0; i < MAX_EPOCH; i++) {
        int pointsDone=0;
        vector<data_point *> *points = shuffleData(data);
        for (auto p:*points) {
            this->fprop(p->x);
            this->bprop( p->y);
            this->update();
            pointsDone++;
            cout<<"Finished "<<pointsDone<<" From Total "<<size<< " meaning : "<<(pointsDone*100/size)<<"%"<<endl;
        }
        cout<<"finished round "<<i<<endl;
    }
}


void NN::fprop(Vector *x) {
    this->H[0] = new Vector(x);
    for (int i = 0; i < this->num_hidden_layers; i++) {
        auto zd = dot(this->ws[i], this->H[i]);
        this->Z[i] = *zd + this->bias[i];
        this->H[i + 1] = this->function->activate(this->Z[i]);
    }
    auto tempZ = dot(this->ws[this->num_hidden_layers], this->H[this->num_hidden_layers]);
    this->Z[this->num_hidden_layers] = *tempZ + this->bias[this->num_hidden_layers];
    this->H[this->num_hidden_layers + 1] = softMax(this->Z[this->num_hidden_layers]);
}


void NN::bprop(int real_y) {
    auto *encoded_y = new Vector(this->classes);
    encoded_y = encoded_y->updatePlus(real_y, -1);
    auto dLoss = (*this->H[this->num_hidden_layers + 1] + encoded_y);
    this->dW[this->num_hidden_layers] = multi(dLoss, this->H[this->num_hidden_layers]->transpose());
    this->dB[this->num_hidden_layers] = dLoss;
    for (int i = this->num_hidden_layers - 1; i > -1; i--) {
        auto dl = dot(this->ws[i + 1]->transpose(), dLoss);
        dLoss = (*dl * this->function->deActive(this->Z[i]));
        auto h = this->H[i]->transpose();
        this->dW[i] = multi(dLoss, h);
        this->dB[i] = dLoss;
    }

}

void NN::update() {
    for (int i = 0; i < this->num_hidden_layers + 1; i++) {
        this->ws[i] = *this->ws[i] + (*this->dW[i] * -this->lr);
        this->bias[i] = *this->bias[i] + (*this->dB[i] * -this->lr);
    }
}

double NN::test(vector<data_point *> *data) {
    double success = 0;
    for (auto p:*data) {
        this->fprop(p->x);
        int result= argMax(this->H[this->num_hidden_layers + 1]);
        success += (result == p->y) ? 1 : 0;
    }
    return success / data->size();
}


