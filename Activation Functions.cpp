//
// Created by Tomer on 14/08/2022.
//

#include <cmath>
#include "Activation Functions.h"

Vector Sigmoid::activate(const Vector &x) const {
    vector<double> output;
    for (int i = 0; i < x.getSize(); i++) {
        output.push_back(1 / (1 + exp(x[i])));
    }
    return {x.getSize(), output};
}

Vector Sigmoid::deActive(const Vector &dx) const {
    const Vector res = activate(dx);
    unsigned int size = res.getSize();
    vector<double> output;
    for (int i = 0; i < size; i++) {
        //(1 - res) * res
        output.push_back( (1 - res[i]) * res[i]);
    }
    return {size, output};
}
