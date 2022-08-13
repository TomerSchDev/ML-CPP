//
// Created by Tomer on 12/08/2022.
//

#ifndef NN_VECTOR_H
#define NN_VECTOR_H


#include <ostream>

class Vector {
    unsigned int size;
    double *data;
    bool trans;
public:
    Vector() {
        this->size = 0;
        this->data = nullptr;
        this->trans = false;
    }

    bool isTrans() const {
        return trans;
    }

    Vector(unsigned int size) {
        this->size = size;
        this->data = new double[size]{0};
        this->trans = false;
    }

    Vector(unsigned int size, double *data) {
        this->size = size;
        this->data = data;
        this->trans = false;
    }

    Vector(unsigned int size, double *data, bool trans) {
        this->size = size;
        this->data = data;
        this->trans = trans;
    }

    Vector(const Vector *pVector) {
        this->size = pVector->size;
        this->data = new double[this->size];
        this->trans = pVector->trans;
        for (int i = 0; i < this->size; i++) {
            this->data[i] = (*pVector)[i];
        }
    }

    Vector(const Vector *pVector, bool trans) {
        this->size = pVector->size;
        this->data = new double[this->size];
        this->trans = trans;
        for (int i = 0; i < this->size; i++) {
            this->data[i] = (*pVector)[i];
        }
    }

    ~Vector() {
        //delete[]this->data;

    }

    Vector *transpose() const {
        return new Vector(this, !this->trans);
    }

    Vector *operator+(double alpha) const {
        double *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double d = this->data[i];
            tempData[i] = d + alpha;
        }
        return new Vector(this->size, tempData);
    }

    Vector *operator*(double alpha) const {
        double *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double d = this->data[i];
            tempData[i] = d * alpha;
        }
        return new Vector(this->size, tempData);
    }

    Vector *operator+(Vector *b) const {
        if (this->size != b->size) {
            return nullptr;
        }
        double *tempData = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            double a = this->data[i];
            double bD = b->data[i];
            tempData[i] = a + bD;
        }
        return new Vector(this->size, tempData);
    }

    Vector *operator+=(double alpha) {
        for (int i = 0; i < this->size; i++) {
            this->data[i] += alpha;
        }
        return this;
    }

    Vector *operator*=(double alpha) {
        for (int i = 0; i < this->size; i++) {
            this->data[i] *= alpha;
        }
        return this;
    }

    Vector *operator+=(Vector *b) {
        if (this->size != b->size) {
            return nullptr;
        }
        for (int i = 0; i < this->size; i++) {
            this->data[i] += b->data[i];
        }
        return this;
    }

    Vector *operator*=(Vector *b) {
        if (this->size != b->size) {
            return nullptr;
        }
        for (int i = 0; i < this->size; i++) {
            this->data[i] *= b->data[i];
        }
        return this;
    }

    Vector* updatePlus(int index, double v) {
        double* pDouble=new double[this->size];
        for(int i=0;i< this->size;i++){
            if(i==index){
                pDouble[i]=this->data[i]+v;
            }else{
                pDouble[i]=this->data[i];
            }
        }
        return new Vector(this->size,pDouble);
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector* v) {
        Vector a(v);
        if (a.trans) {
            out << " | ";
            for (int i = 0; i < a.size; i++) {
                out << a.data[i] << " | ";
            }
            out << "\n";
        } else {
            for (int i = 0; i < a.size; i++) {
                out << " | " << a.data[i] << " | " << "\n";
            }
        }
        return out;
    }

    double operator[](int i) const {
        double t = this->data[i];
        return t;
    }


    unsigned int getSize() const {
        return size;
    }

};


#endif //NN_VECTOR_H
