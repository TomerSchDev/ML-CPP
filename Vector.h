//
// Created by Tomer on 12/08/2022.
//

#ifndef NN_VECTOR_H
#define NN_VECTOR_H


#include <ostream>
#include <iostream>
#include <vector>
#include "memory"
#include "IteratorV.h"

using namespace std;

class Vector {
    unsigned int size;
    vector<double> data;
    bool trans;
public:
    Vector() {
        this->size = 0;
        //std::cout << "Non Exist Vector! stop" << std::endl;
        this->trans = false;
    }

    bool isTrans() const {
        return trans;
    }

    Vector(unsigned int size) {
        this->size = size;
        for (int i = 0; i < size; i++) {
            this->data.push_back(0);
        }
        this->trans = false;
    }

    Vector(unsigned int size, const vector<double> &data) {
        this->size = size;
        this->data = vector<double>(data);
        this->trans = false;
    }

    Vector(unsigned int size, const vector<double> &data, bool trans) {
        this->size = size;
        for (auto d:data) {
            this->data.emplace_back(d);
        }
        this->trans = trans;
    }


    Vector(const Vector &old) {
        this->size = old.size;
        this->trans = old.trans;
        this->data = vector<double>(old.data);
    }

    Vector(const Vector *pVector, bool trans) {
        this->size = pVector->size;
        this->trans = trans;
        this->data = vector<double>(pVector->data);
    }


    friend std::ostream &operator<<(std::ostream &out, const Vector &a) {
        if (a.trans) {
            out << " | ";
            for (int i = 0; i < a.size; i++) {
                out << a.data[i] << " | ";
            }
            out << "\n";
        } else {
            for (unsigned int i = 0; i < a.size; i++) {
                out << " | " << a.data[i] << " | " << "\n";
            }
        }
        return out;
    }

    Vector transpose() const {
        return {this, !this->trans};
    }


    Vector operator+(double alpha) const {
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(this->data[i] + alpha);
        }
        return {this->size, tempData};
    }

    Vector operator*(double alpha) const {
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(this->data[i] * alpha);
        }
        return {this->size, tempData};
    }

    Vector operator+(const Vector &b) const {
        if (this->size != b.size) {
            std::cout << "Wrong sizes in + operator in Vector class with Vector" << std::endl;
            return {};
        }
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(this->data[i] + b.data[i]);
        }
        return {this->size, tempData};
    }

    Vector *operator+=(double alpha) {
        vector<double> tempData;

        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(data[i] + alpha);
        }
        this->data = tempData;
        return this;
    }

    Vector *operator*=(double alpha) {
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(data[i] * alpha);
        }
        this->data = tempData;
        return this;
    }

    Vector dotMultply(const Vector &v) {
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(this->data[i] * v.data[i]);
        }
        return {this->size, tempData};
    }

    Vector *operator+=(const Vector &b) {
        if (this->size != b.size) {
            std::cout << "Wrong sizes in += operator in Vector class with Vector" << std::endl;
            return {};
        }
        vector<double> tempData;

        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(data[i] + b.data[i]);
        }
        this->data = tempData;
        return this;
    }

    Vector *operator*=(const Vector &b) {
        if (this->size != b.size) {
            std::cout << "Wrong sizes in *= operator in Vector class with Vector" << std::endl;
            return {};
        }
        vector<double> tempData;

        for (int i = 0; i < this->size; i++) {
            tempData.emplace_back(data[i] * b.data[i]);
        }
        this->data = tempData;
        return this;
    }

    Vector updatePlus(int index, double v) const {
        vector<double> tempData;
        for (int i = 0; i < this->size; i++) {
            if (i == index) {
                tempData.emplace_back(this->data[i] + v);
            } else {
                tempData.emplace_back(this->data[i]);
            }
        }

        return {this->size, tempData};
    }


    double operator[](int i) const {
        return this->data[i];
    }


    unsigned int getSize() const {
        return size;
    }


};


#endif //NN_VECTOR_H
