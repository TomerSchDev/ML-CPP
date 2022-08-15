//
// Created by Tomer on 14/08/2022.
//

#include <cmath>
#include "Activation Functions.h"

Vector *Sigmoid::activate(const Vector *x) const{
    auto *output = new double[x->getSize()];
    for (int i = 0; i < x->getSize(); i++) {
        output[i] = 1 / (1 + exp((*x)[i]));
    }
    return new Vector(x->getSize(), output);
}

Vector *Sigmoid::deActive(const Vector *dx) const{
    const Vector *res = activate(dx);
    unsigned int size = res->getSize();
    auto *output = new double[size];
    for (int i = 0; i < size; i++) {
        //(1 - res) * res
        output[i] = (1 - (*res)[i]) * (*res)[i];
    }
    return new Vector(size, output);
}
