#include "Matrix.hpp"
#include <vector>
using namespace std;
using namespace zich;
    
Matrix::Matrix(const vector<double> &values, int rows, int colums){
    if (rows < 0 || colums < 0)
    {
        throw runtime_error("cols and rows has to be positive");
    }
    if(rows * colums != values.size()){
        throw runtime_error("rows * columns has to be equals to the vectors size");
    }

    this->rows = rows;
    this->colums = colums;
    vector<vector<double>> mat;

    for (size_t row = 0; row < this->rows; row++){
        vector<double> res;
        res.reserve((unsigned long) this->colums);
        for (size_t column = 0; column < this->colums; column++) {
            res.push_back(values.at((unsigned long) (this->colums) * row + column));
        }
        mat.push_back(res);
    }
        this->mat = mat;
}

//plus operators
Matrix zich::operator + (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    vector<double> res;
    for (size_t row = 0; row < first_mat.rows; ++row){
        for (size_t column = 0; column < first_mat.colums; ++column){
            res.push_back(first_mat.mat.at(row).at(column) + second_mat.mat.at(row).at(column));
            }
        }
        return Matrix(res, first_mat.rows, first_mat.colums);
    }

Matrix Matrix::operator +() const{
    return *this;
}

//prefix
Matrix &Matrix:: operator ++() {
    for (size_t row = 0; row < this->rows; ++row) {
        for (size_t column = 0; column < this->colums; ++column) {
            this->mat.at(row).at(column)++;
        }
    }
    return *this;
}
//postfix
Matrix Matrix:: operator ++(int num) {
    Matrix res = *this;
    ++(*this);
    return res;
}

Matrix &Matrix::operator+=(const Matrix &mat){
    if(this->rows != mat.rows || this->colums != mat.colums){
        throw runtime_error("matrix has to be same size");
    }
    for (size_t row = 0; row < mat.rows; row++){
        for (size_t column = 0; column < mat.colums; column++){
            this->mat.at(row).at(column) += mat.mat.at(row).at(column);
        }
    }
    return *this;
}

//minus operators
Matrix zich::operator - (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    vector<double> res;
    for (size_t row = 0; row < first_mat.rows; ++row){
        for (size_t column = 0; column < first_mat.colums; ++column){
            res.push_back(first_mat.mat.at(row).at(column) - second_mat.mat.at(row).at(column));
        }
    }
    return Matrix(res, first_mat.rows, first_mat.colums);
}

Matrix Matrix::operator-() const {
    return -1 * *(this);
}

//prefix
Matrix &Matrix:: operator --() {
    for (size_t row = 0; row < this->rows; ++row) {
        for (size_t column = 0; column < this->colums; ++column) {
            this->mat.at(row).at(column)--;
        }
    }
    return *this;
}

//postfix
Matrix Matrix:: operator --(int num) {
    Matrix res = *this;
    --(*this);
    return res;
}

Matrix &Matrix::operator -= (const Matrix &mat){
    if(this->rows != mat.rows || this->colums != mat.colums){
        throw runtime_error("matrix has to be same size");
    }
    for (size_t row = 0; row < mat.rows; row++){
        for (size_t column = 0; column < mat.colums; column++){
            this->mat.at(row).at(column) -= mat.mat.at(row).at(column);
        }
    }
    return *this;
}
    

//multipication operators
Matrix &Matrix::operator*=(const double &num) {
    for (size_t row = 0; row < this->rows; ++row) {
        for (size_t column = 0; column < this->colums; ++column) {
            this->mat.at(row).at(column) *= num;
        }
    }
    return *this;
}

Matrix &Matrix::operator *= (const Matrix &mat) {
    if (this->colums != mat.rows) {
        throw invalid_argument("row of the inputted mat has to be equal to column of this mat");
    }
    vector<double> values;
    double value = 0;
    for (size_t row = 0; row < this->rows; ++row) {
        for (size_t column = 0; column < mat.colums; ++column) {
            value = 0;
            for (size_t pos = 0; pos < this->colums; ++pos) {
                value += this->mat.at(row).at(pos) * mat.mat.at(pos).at(column);
            }
            values.push_back(value);
        }
    }
    this->colums = mat.colums;
    vector<vector<double>> res;
    for (size_t row = 0; row < this->rows; row++) {
        vector<double> vec;
        vec.reserve((unsigned long) this->colums);
        for (size_t column = 0; column < this->colums; column++) {
            vec.push_back(values.at((unsigned long) (this->colums) * row + column));
        }
        res.push_back(vec);
    }
    this->mat = res;
    return *this;
}


Matrix zich::operator*(const Matrix &first_mat, const Matrix &second_mat) {
    if (first_mat.colums != second_mat.rows) {
        throw invalid_argument("Column of the first mat must be equal to row of the second mat");
    }
    vector<double> res;
    double value = 0;
    for (size_t row = 0; row < first_mat.rows; ++row) {
        for (size_t column = 0; column < second_mat.colums; ++column) {
            value = 0;
            for (size_t pos = 0; pos < first_mat.colums; ++pos) {
                value += first_mat.mat.at(row).at(pos) * second_mat.mat.at(pos).at(column);
            }
            res.push_back(value);
        }
    }
    return Matrix(res, first_mat.rows, second_mat.colums);
}
    

Matrix zich::operator*(const Matrix &first_mat, const double &num) {
    vector<double> res;
    for (size_t row = 0; row < first_mat.rows; ++row) {
        for (size_t column = 0; column < first_mat.colums; ++column) {
            res.push_back(first_mat.mat.at(row).at(column) * num);
        }
    }
    return Matrix(res, first_mat.rows, first_mat.colums);
}

Matrix zich::operator*(const double &num, const Matrix &first_mat) {
    vector<double> res;
    for (size_t row = 0; row < first_mat.rows; ++row) {
        for (size_t column = 0; column < first_mat.colums; ++column) {
            res.push_back(first_mat.mat.at(row).at(column) * num);
        }
    }
    return Matrix(res, first_mat.rows, first_mat.colums);
}


//comparsion operators:
bool zich::operator > (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    int sum1 =0;
    int sum2 = 0;
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            sum1 += first_mat.mat.at(row).at(column);
            sum2 += second_mat.mat.at(row).at(column);
        }
    }
    return sum1 > sum2;
}

bool zich::operator < (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    int sum1 =0;
    int sum2 = 0;
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            sum1 += first_mat.mat.at(row).at(column);
            sum2 += second_mat.mat.at(row).at(column);
        }
    }
    return sum1 < sum2;
}

bool zich::operator >= (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    int sum1 =0;
    int sum2 = 0;
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            sum1 += first_mat.mat.at(row).at(column);
            sum2 += second_mat.mat.at(row).at(column);
        }
    }
    return sum1 >= sum2;
}

bool zich::operator <= (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    int sum1 =0;
    int sum2 = 0;
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            sum1 += first_mat.mat.at(row).at(column);
            sum2 += second_mat.mat.at(row).at(column);
        }
    }
    return sum1 <= sum2;
}

bool zich::operator == (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            if (first_mat.mat.at(row).at(column) != second_mat.mat.at(row).at(column)){
                return false;
            }
        }
    }
    return true;
}

bool zich::operator != (const Matrix &first_mat, const Matrix &second_mat){
    if (first_mat.rows != second_mat.rows || first_mat.colums != second_mat.colums){
        throw runtime_error("the matrixs has to be in the same size");
    }
    for (size_t row = 0; row < first_mat.rows; row++){
        for (size_t column = 0; column < first_mat.colums; column++){
            if (first_mat.mat.at(row).at(column) != second_mat.mat.at(row).at(column)){
                return true;
            }
        }
    }
    return false;
}
        
istream &zich::operator >> (istream &in, Matrix &mat){
    string input;
    getline(in, input);
    string temp;

    int rows = 1;
    int columns = 1;
    bool flag = false;
    for (size_t pos = 0; pos < input.size() - 1; ++pos) {
        if (input.at(pos) == '[') {
            if (input.at(pos + 1) < '0' && input.at(pos + 1) > '9'){
                throw invalid_argument("after [ must come a number");
            }
        } 
 
        else if (input.at(pos) == ' ') {
            if (input.at(pos + 1) != '[') {
                if (input.at(pos + 1) < '0' && input.at(pos + 1) > '9') {
                    throw invalid_argument("after [ must come a number");
                }
                if (!flag) {
                    columns++;
                }
            }
        }

        else if (input.at(pos) == ',') {
            if (input.at(pos + 1) != ' ') {
                throw invalid_argument("after a , must come a space");
            }
        }

        else if (input.at(pos) == ']') {
            if (input.at(pos + 1) != ',') {
                throw invalid_argument("after ] must come ,");
            }
            flag = true;
            rows++;
        }

        else if (input.at(pos) == '.' || (input.at(pos) > '0' && input.at(pos) < '9')) {
            temp.push_back(input.at(pos));
        }

        else {
            throw invalid_argument("somthing wrong with the input");
        }
    }

    mat.rows = rows;
    mat.colums = columns;
    vector<vector<double>> the_mat;
    vector<double> vec;

    for (char pos: temp) {
        string str;
        str = pos;
        vec.push_back(stod(str));
    }

    for (size_t pos = 0; pos < rows; ++pos) {
        vector<double> temp;
        for (size_t i = 0; i < columns; ++i) {
            temp.push_back(vec.at((unsigned long) columns * pos + i));
        }
        the_mat.push_back(temp);
    }

    mat.mat = the_mat;
    return in;
}
    
ostream &zich::operator << (ostream &out, const Matrix &mat){
    bool finish = false;
    for (size_t row = 0; row < mat.mat.size(); ++row) {
        out << "[";
        for (size_t column = 0; column < mat.mat.at(row).size(); ++column) {
            out << mat.mat.at(row).at(column) << "";
            if (column == mat.colums - 1) {
                if (row == mat.rows - 1) {
                   finish = true;
                } 
                else {
                    out << "]\n";
                }
                break;
            }
            out << " ";
        }
        if (finish) {
            out << "]";
        }
    }
    return out;
}

