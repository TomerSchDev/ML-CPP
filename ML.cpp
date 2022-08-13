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

int MAX_EPOCH = 300;

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
        success += (result == p->y)?1 : 0;
    }
    return success/data->size();
}
