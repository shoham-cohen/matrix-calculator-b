#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <iostream>
using namespace std;

namespace zich
{
    class Matrix
    {
    private:
        int rows, colums;
        vector<vector<double>> mat;

    public:
         Matrix(const vector<double> &values, int rows, int colums);
        
        //plus operators
        friend Matrix operator + (const Matrix &first_mat,const Matrix &second_mat);  
        Matrix operator+() const; //unary
        Matrix operator++(int num); //postfix
        Matrix& operator++(); //prefix
        Matrix &operator+=(const Matrix &mat);

        //minus operators
        friend Matrix operator-(const Matrix &first_mat,const Matrix &second_mat);  //
        Matrix operator-() const; //unary
        Matrix operator--(int num); //postfix
        Matrix& operator--(); //prefix
        Matrix &operator-=(const Matrix &mat);

        //multipication operators
        Matrix &operator*=(const double &num);
        Matrix &operator*=(const Matrix &first_mat);
        friend Matrix operator*(const Matrix &first_mat,const Matrix &second_mat);
        friend Matrix operator*(const Matrix &first_mat,const double &num);
        friend Matrix operator*(const double &num,const Matrix &first_mat);

        
        //comparison operators
        friend bool operator > (const Matrix &first_mat, const Matrix &second_mat);
        friend bool operator < (const Matrix &first_mat, const Matrix &second_mat);
        friend bool operator >= (const Matrix &first_mat, const Matrix &second_mat);
        friend bool operator <= (const Matrix &first_mat, const Matrix &second_mat);
        friend bool operator == (const Matrix &first_mat, const Matrix &second_mat);
        friend bool operator != (const Matrix &first_mat, const Matrix &second_mat);
        // cout and cin operatos:
        friend istream &operator >> (istream &in, Matrix &m);
        friend ostream &operator << (ostream &out, const Matrix &m);
    };
}
#endif