//
// Created by Tomer on 14/08/2022.
//

#ifndef MLCPP_ACTIVATION_FUNCTIONS_H
#define MLCPP_ACTIVATION_FUNCTIONS_H

#include "Vector.h"

class ActivityFunction {
public:
    virtual Vector *activate(const Vector *x) const = 0;

    virtual Vector *deActive(const Vector *dx) const = 0;
};

class Sigmoid : public ActivityFunction {
public:
    Vector *activate(const Vector *x) const override;

    Vector *deActive(const Vector *dx) const override;
};

#endif //MLCPP_ACTIVATION_FUNCTIONS_H
