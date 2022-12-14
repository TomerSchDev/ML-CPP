//
// Created by Tomer on 12/08/2022.
//

#ifndef NN_LINIARALGEBRA_H
#define NN_LINIARALGEBRA_H
#include "Vector.h"
#include "Matrix.h"
#include "vector"
#include <algorithm>

#include "Matrix.h"
#include "Vector.h"
class data_point;
using namespace std;

Matrix vectorMultiVector(const Vector &a, const Vector &b);
double dot(const Vector &a, const Vector &b);
Vector dot(const Matrix &a, const Vector &b);
Vector dot(const Matrix &a, const Vector &b,bool);

vector<data_point *> shuffleData(const vector<data_point *>& v);
int argMax(const Vector& v);
Vector softMax(const Vector&v);
#endif //NN_LINIARALGEBRA_H
