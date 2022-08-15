//
// Created by Tomer on 12/08/2022.
//

#ifndef NN_VECTOR_H
#define NN_VECTOR_H


#include <ostream>
#include <iostream>
#include "memory"

using namespace std;

class Vector {
    unsigned int size;
    shared_ptr<double *> data;
    bool trans;
public:
    Vector() {
        this->size = 0;
        this->data = nullptr;
        std::cout << "Non Exisit Vector! stop" << std::endl;
        this->trans = false;
    }

    bool isTrans() const {
        return trans;
    }

    Vector(unsigned int size) {
        this->size = size;
        this->data = std::make_shared<double *>(new double[size]);
        this->trans = false;
    }

    Vector(unsigned int size, const double *data) {
        this->size = size;
        this->data = make_shared<double *>(new double[size]);
        for (int i = 0; i < size; i++) {
            (*this->data)[i] = data[i];
        }
        this->trans = false;
    }

    Vector(unsigned int size, double *data, bool trans) {
        this->size = size;
        this->data = make_shared<double *>(new double[size]);

        for (int i = 0; i < size; i++) {
            (*this->data)[i] = data[i];
        }
        this->trans = trans;
    }

    Vector(const Vector *pVector) {
        this->size = pVector->size;
        this->data = make_shared<double *>(new double[size]);
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] = (*pVector->data)[i];
        }
        this->trans = pVector->trans;

    }

    Vector(const Vector &old) {
        this->size = old.size;
        //this->data = new double[this->size];
        this->size = old.size;
        this->data = make_shared<double *>(new double[size]);
        this->trans = old.trans;
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] = (*old.data)[i];
        }
    }

    Vector(const Vector *pVector, bool trans) {
        this->size = pVector->size;
        this->trans = trans;
        this->data = make_shared<double *>(new double[size]);
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] = (*pVector->data)[i];
        }
    }

    shared_ptr<Vector *>transpose() const {
        return make_shared<Vector*>(new Vector(this, !this->trans));
    }

    shared_ptr<Vector *>operator+(double alpha) const {
        auto *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double d = (*this->data)[i];
            tempData[i] = d + alpha;
        }
        return make_shared<Vector*>(new Vector(this->size, tempData));
    }

    shared_ptr<Vector *>operator*(double alpha) const {
        auto *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double d = (*this->data)[i];
            tempData[i] = d * alpha;
        }
        return make_shared<Vector*>(new Vector(this->size, tempData));
    }

    shared_ptr<Vector *>operator+(Vector *b) const {
        if (this->size != b->size) {
            std::cout << "Wrong sizes in + operator in Vector class with Vector" << std::endl;
            return nullptr;
        }
        auto *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double a = (*this->data)[i];
            double bD = (*b->data)[i];
            tempData[i] = a + bD;
        }
        return make_shared<Vector*>(new Vector(this->size, tempData));
    }

    Vector *operator+=(double alpha) {
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] += alpha;
        }
        return this;
    }

    Vector *operator*=(double alpha) {
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] *= alpha;
        }
        return this;
    }

    shared_ptr<Vector *> operator*(const Vector *v) {
        auto *temp = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            temp[i] = (*this->data)[i] * (*v->data)[i];
        }
        return make_shared<Vector*>(new Vector(this->size, temp));
    }

    Vector *operator+=(Vector *b) {
        if (this->size != b->size) {
            std::cout << "Wrong sizes in += operator in Vector class with Vector" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] += (*b->data)[i];
        }
        return this;
    }

    Vector *operator*=(Vector *b) {
        if (this->size != b->size) {
            std::cout << "Wrong sizes in *= operator in Vector class with Vector" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < this->size; i++) {
            (*this->data)[i] *= (*b->data)[i];
        }
        return this;
    }

    shared_ptr<Vector *> updatePlus(int index, double v) const {
        auto* pDouble=new double[this->size];
        for(int i=0;i< this->size;i++){
            if(i==index){
                pDouble[i]=(*this->data)[i]+v;
            }else{
                pDouble[i]=(*this->data)[i];
            }
        }
        return make_shared<Vector*>( new Vector(this->size,pDouble));
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector* v) {
        Vector a(v);
        if (a.trans) {
            out << " | ";
            for (int i = 0; i < a.size; i++) {
                out << (*a.data)[i] << " | ";
            }
            out << "\n";
        } else {
            for (unsigned int i = 0; i < a.size; i++) {
                out << " | " << (*a.data)[i] << " | " << "\n";
            }
        }
        return out;
    }

    double operator[](int i) const {
        double t = (*this->data)[i];
        return t;
    }


    unsigned int getSize() const {
        return size;
    }

};


#endif //NN_VECTOR_H
