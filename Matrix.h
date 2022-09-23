//
// Created by Tomer on 11/08/2022.
//

#ifndef NN_MATRIX_H
#define NN_MATRIX_H

#include <ostream>
#include "Vector.h"
#include <vector>


class Vector;

class Matrix {


    unsigned int rows;
    unsigned int cols;
    vector<Vector> data;

public:
    Matrix() {
        this->rows = 0;
        this->cols = 0;
        //std::cout<<"Non Exisit Matrix! stop"<<std::endl;
    }


    Matrix(unsigned int rows, unsigned int cols) {
        this->rows = rows;
        this->cols = cols;
        for (int i = 0; i < cols; i++) { this->data.emplace_back(rows); }
    }

    Matrix(unsigned int rows, unsigned int cols, const vector<Vector> &data) {
        this->rows = rows;
        this->cols = cols;
        this->data = vector<Vector>(data);
    }

    Matrix(const Matrix &old) {
        this->rows = old.rows;
        this->cols = old.cols;
        this->data = vector<Vector>(old.data);
    }

    Matrix operator+(double alpha) const {
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            tempData.push_back(this->data[i] + alpha);
        }
        return {this->rows, this->cols, tempData};
    }

    Matrix *operator+=(double alpha) {
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            tempData.push_back(this->data[i] + alpha);
        }
        this->data = tempData;
        return this;
    }

    Matrix *operator*=(double alpha) {
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            tempData.push_back(this->data[i] * alpha);
        }
        this->data = tempData;
        return this;
    }

    Matrix operator*(double alpha) const {
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            tempData.push_back(this->data[i] * alpha);
        }
        return {this->rows, this->cols, tempData};
    }

    Matrix operator+(const Matrix &b) const {
        if (b.rows != this->rows || b.cols != this->cols) {
            std::cout << "Wrong sizes in + operator in Matrix class" << std::endl;
            return {};
        }
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            tempData.push_back(this->data[i] + b.data[i]);
        }
        return {this->rows, this->cols, tempData};
    }

    Matrix operator*(const Matrix &b) const {
        if (this->cols != b.rows) {
            std::cout << "Wrong sizes in * operator in Matrix class with matrix" << std::endl;
            return {};
        }
        vector<Vector> tempData;
        //for every new column of b
        for (int i = 0; i < b.cols; i++) {
            Vector col = b.data[i];
            //for every new row of a (this)
            vector<double> tempDoubleData;
            for (int j = 0; j < this->rows; j++) {
                vector<double> row;
                for (auto temp = 0; temp < this->cols; temp++) {
                    row.push_back(this->data[temp][j]);
                }
                double temp = 0;
                //calculate inside
                for (int k = 0; k < this->cols; k++) {
                    double aI = row[k];
                    double bI = col[k];
                    temp += aI * bI;
                }
                tempDoubleData.push_back(temp);
            }
            tempData.push_back(Vector(this->rows, tempDoubleData));
        }
        return {this->rows, b.cols, tempData};

    }

    Vector operator*(const Vector &b) const {
        if (this->cols != b.getSize() && !b.isTrans()) {
            std::cout << "Wrong sizes in * operator in Matrix class with vector" << std::endl;
            return {};
        }
        vector<double> pDouble;
        for (int i = 0; i < b.getSize(); i++) {
            vector<double> row;
            for (auto temp = 0; temp < this->cols; temp++) {
                row.push_back(this->data[temp][i]);
            }
            double temp = 0;
            for (int j = 0; j < this->cols; j++) {
                double r = row[j];
                double c = b[j];
                temp += c * r;
            }
            pDouble.push_back(temp);
        }
        return {this->rows, pDouble};
    }

    Vector operator[](int i) const {
        return this->data[i];
    }

    Matrix updatePlus(int index, const Vector &v) {
        vector<Vector> tempData;
        for (int i = 0; i < this->cols; i++) {
            if (i == index) {
                tempData.push_back(this->data[i] + v);
            } else {
                tempData.push_back(this->data[i]);
            }
        }
        return {this->rows, this->cols, tempData};
    }

    Matrix transpose() {
        vector<Vector> vectors;
        //auto **pDouble = new double *[this->rows];
        for (int i = 0; i < this->rows; i++) {
            vector<double> data;
            for (int j = 0; j < this->cols; j++) {
                Vector col = this->data[j];
                data.push_back(col[i]);
            }
            vectors.emplace_back(this->cols,data);
        }
        return {this->cols, this->rows, vectors};
    }


    friend std::ostream &operator<<(std::ostream &out, const Matrix &a) {
        for (int i = 0; i < a.rows; i++) {
            out << " | ";
            for (int j = 0; j < a.cols; j++) {
                out << a[j][i] << " | ";
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
