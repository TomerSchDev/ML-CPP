//
// Created by Tomer on 11/08/2022.
//

#ifndef NN_MATRIX_H
#define NN_MATRIX_H

#include <ostream>
#include "Vector.h"


class Vector;

class Matrix {


    unsigned int rows;
    unsigned int cols;
    Vector **data;

public:
    Matrix() {
        this->rows = 0;
        this->cols = 0;
        this->data = nullptr;
    }

    Matrix(const Matrix *pMatrix) {
        this->rows = pMatrix->rows;
        this->cols = pMatrix->cols;
        this->data = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            this->data[i] = (*pMatrix)[i];
        }
    }

    Matrix(unsigned int rows, unsigned int cols) {
        this->rows = rows;
        this->cols = cols;
        this->data = new Vector *[cols];
        for (int i = 0; i < cols; i++) {
            this->data[i] = new Vector(rows);
        }
    }

    Matrix(unsigned int rows, unsigned int cols, Vector **data) {
        this->rows = rows;
        this->cols = cols;
        this->data = new Vector *[cols];
        for (int i = 0; i < 3; i++) {
            this->data[i] = new Vector(data[i]);
        }
    }

    Matrix(unsigned int rows, unsigned int cols, double **data) {
        this->rows = rows;
        this->cols = cols;
        this->data = new Vector *[cols];
        for (int i = 0; i < cols; i++) {
            this->data[i] = new Vector(rows, data[i]);
        }
    }

    Matrix *operator+(double alpha) const {
        Vector **tempData = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            auto t = new Vector(this->data[i]);
            tempData[i] = *t + alpha;
        }
        return new Matrix(this->rows, this->cols, tempData);
    }

    Matrix *operator+=(double alpha) {
        Vector **tempData = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            auto t = new Vector(this->data[i]);
            tempData[i] = *t + alpha;
        }
        delete this->data;
        this->data = tempData;
        return this;
    }

    Matrix *operator*=(double alpha) {
        Vector **tempData = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            auto t = new Vector(this->data[i]);
            tempData[i] = *t * alpha;
        }
        delete this->data;
        this->data = tempData;
        return this;
    }

    Matrix *operator*(double alpha) const {
        Vector **tempData = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            auto t = new Vector(*this->data[i]);
            tempData[i] = *t * alpha;
        }
        return new Matrix(this->rows, this->cols, tempData);
    }

    Matrix *operator+(Matrix *b) const {
        if (b->rows != this->rows || b->cols != this->cols) {
            return nullptr;
        }
        auto tempData = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            auto aV = new Vector(this->data[i]);
            auto bV = new Vector(b->data[i]);
            tempData[i] = *aV + bV;
        }
        return new Matrix(this->rows, this->cols, tempData);
    }

    Matrix *operator*(const Matrix *b) const {
        if (this->cols != b->rows) {
            return nullptr;
        }
        Vector **tempData = new Vector *[b->cols];
        //for every new column of b
        for (int i = 0; i < b->cols; i++) {
            Vector *col = new Vector((*b)[i]);
            //for every new row of a (this)
            auto *tempIntData = new double[this->rows];
            for (int j = 0; j < this->rows; j++) {
                auto *row = new double[this->cols];
                for (auto temp = 0; temp < this->cols; temp++) {
                    row[temp] = (*this->data[temp])[j];
                }
                double temp = 0;
                //calculate inside
                for (int k = 0; k < this->cols; k++) {
                    double aI = row[k];
                    double bI = (*col)[k];
                    temp += aI * bI;
                }
                tempIntData[j] = temp;
            }
            tempData[i] = new Vector(this->rows, tempIntData);
        }
        return new Matrix(this->rows, b->cols, tempData);

    }

    Vector *operator*(const Vector *b) const {
        if (this->cols != b->getSize() && !b->isTrans()) {
            return nullptr;
        }
        auto *pDouble = new double[this->rows];
        for (int i = 0; i < b->getSize(); i++) {
            double *row = new double[this->cols];
            for (auto temp = 0; temp < this->cols; temp++) {
                row[temp] = (*this->data[temp])[i];
            }
            int temp = 0;
            for (int j = 0; j < this->cols; j++) {
                double r = row[j];
                double c = (*b)[j];
                temp += c * r;
            }
            pDouble[i] = temp;
        }
        return new Vector(this->rows, pDouble);
    }

    Vector *operator[](int i) const {
        return new Vector(this->data[i]);
    }

    Matrix *updatePlus(int index, Vector *v) {
        Vector **pVector = new Vector *[this->cols];
        for (int i = 0; i < this->cols; i++) {
            if (i == index) {
                pVector[i] = *this->data[i] + v;
            } else {
                pVector[i] = new Vector(this->data[i]);
            }
        }
        return new Matrix(this->rows, this->cols, pVector);
    }


    ~Matrix() {
        for (int i = 0; i < this->rows; i++) {
            //delete this->data[i];
        }
        //delete[]this->data;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix *m) {
        Matrix a(m);
        for (int i = 0; i < a.rows; i++) {
            out << " | ";
            for (int j = 0; j < a.cols; j++) {
                Vector *t = a[j];
                out << (*t)[i] << " | ";
            }
            out << "\n";
        }
        return out;
    }

    unsigned int getRows() const {
        return rows;
    }

    unsigned int getCols() const {
        return cols;
    }


};


#endif //NN_MATRIX_H
