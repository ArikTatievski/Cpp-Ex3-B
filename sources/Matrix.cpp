#include "Matrix.hpp"
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;
namespace zich{
    Matrix::Matrix(vector<double> m,int row, int col){
        if(m.size() != row*col || row<1 || col<1){
            throw std::invalid_argument("Matrix doesnt matches the row * col size OR Invalid row/col were entered");
        }
        this->mat = m;
        this->row = row;
        this->col = col;
    }
    Matrix::Matrix(const Matrix& m){
        for (unsigned int i = 0; i < m.col*m.row; ++i) {
            this->mat.push_back(m.mat[i]);
        }
        this->row = m.row;
        this->col = m.col;
    }
    Matrix::~Matrix(){}
    double Matrix::get(unsigned int i, unsigned int j) const{
        return this->mat[i* (unsigned int) (this->col) +j];
    }
    void Matrix::matSizeCheck(const Matrix& m2) const{
        if(this->row != m2.row || this->col != m2.col){
            throw std::invalid_argument("Not same size matrix");
        }
    }
    Matrix operator+ (const Matrix& m1,const Matrix& m2){
        m1.matSizeCheck(m2);
        vector<double> newMat;
        for (unsigned int i = 0; i < m1.row*m1.col; ++i) {
            newMat.push_back(m1.mat[i] + m2.mat[i]);
        }
        Matrix curr(newMat,m1.row,m1.col);
        return curr;
    }
    Matrix &operator+= (Matrix& m1,const Matrix& m2){
        Matrix curr = m1+m2;
        m1.mat = curr.mat;
        return m1;
    }
    Matrix operator+ (const Matrix& m){
        Matrix curr(m);
        return curr;
    }

    Matrix operator- (const Matrix& m1,const Matrix& m2){
        Matrix curr = -m2;
        curr += m1;
        return curr;
    }
    Matrix &operator-= (Matrix& m1,const Matrix& m2){
        Matrix curr = m1-m2;
        m1.mat = curr.mat;
        return m1;
    }
    Matrix operator- (const Matrix& m){
        Matrix curr(m);
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            curr.mat[i] = curr.mat[i]*(-1);
        }
        return curr;
    }

    bool operator< (const Matrix& m1,const Matrix& m2){
        m1.matSizeCheck(m2);
        double sumM1 = 0;
        double sumM2 = 0;
        for (unsigned int i = 0; i < m1.row*m1.col; ++i) {
            sumM1 += m1.mat[i];
            sumM2 += m2.mat[i];
        }
        return sumM1<sumM2;
    }
    bool operator<= (const Matrix& m1,const Matrix& m2){
        m1.matSizeCheck(m2);
        double sumM1 = 0;
        double sumM2 = 0;
        for (unsigned int i = 0; i < m1.row*m1.col; ++i) {
            sumM1 += m1.mat[i];
            sumM2 += m2.mat[i];
        }
        return sumM1<=sumM2;
    }
    bool operator> (const Matrix& m1,const Matrix& m2){
        return !(m1<=m2);
    }
    bool operator>= (const Matrix& m1,const Matrix& m2){
        return !(m1<m2);
    }
    bool operator== (const Matrix& m1,const Matrix& m2){
        m1.matSizeCheck(m2);
        for (unsigned int i = 0; i < m1.row*m1.col; ++i) {
            if(m1.mat[i] != m2.mat[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!= (const Matrix& m1,const Matrix& m2){
        return !(m1==m2);
    }

    Matrix &operator++ (Matrix& m){
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            m.mat[i] += 1;
        }
        return m;
    }
    Matrix operator++ (Matrix& m,int c){
        Matrix curr = m;
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            m.mat[i] += 1;
        }
        return curr;
    }
    Matrix &operator-- (Matrix& m){
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            m.mat[i] -= 1;
        }
        return m;
    }
    Matrix operator-- (Matrix& m,int c){
        Matrix curr = m;
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            m.mat[i] -= 1;
        }
        return curr;
    }

    Matrix operator* (Matrix& m1, Matrix& m2){
        if(m1.col != m2.row){
            throw std::invalid_argument("Invalid matrix sizes (should be (n*m)*(m*k)");
        }
        vector<double> newMat;
        for (unsigned int i = 0; i < m1.row*m2.col; ++i) {
            double sum = 0;
            for (unsigned int j = 0; j < m1.col; ++j) {
                sum+= m1.get(i/(unsigned int )(m2.col),j) * m2.get(j,i%(unsigned int )(m2.col));
            }
            newMat.push_back(sum);
        }
        Matrix curr(newMat,m1.row,m2.col);
        return curr;
    }
    Matrix operator* (Matrix& m, double c){
        vector<double> newMat = m.mat;
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            newMat[i] *= c;
        }
        Matrix curr(newMat,m.row,m.col);
        return curr;
    }
    Matrix operator* (double c, Matrix& m){
        return m*c;
    }

    Matrix &operator*= (Matrix& m,double c){
        vector<double> newMat = m.mat;
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            newMat[i] *= c;
        }
        m.mat = newMat;
        return m;
    }

    Matrix &operator*= (double c,Matrix& m){
        vector<double> newMat = m.mat;
        for (unsigned int i = 0; i < m.row*m.col; ++i) {
            newMat[i] *= c;
        }
        m.mat = newMat;
        return m;
    }

    Matrix &operator*= (Matrix& m1,const Matrix& m2){
        Matrix curr = m2;
        Matrix curr2 = m1*curr;
        m1.mat = curr2.mat;
        return m1;
    }

    std::ostream& operator<<(std::ostream& os,const Matrix& m){
        for (unsigned int i = 0; i < m.row; ++i) {
            os<<"[";
            for (unsigned int j = 0; j < m.col; ++j) {
                if(j == (unsigned int)(m.col -1)){
                    os<<m.get(i,j);
                    continue;
                }
                os<<m.get(i,j) ;
                os<<" ";
            }
            if ( i == m.row-1){
                os<<"]";
            } else{
                os<<"]\n";
            }
        }
        return os;
    }

    std::istream& operator>>(std::istream& is,  Matrix& m){
        int row = 0;
        int col = 0;
        string curr = "";
        while(!is.eof()){
            string small_data;
            is>>small_data;
            if(small_data[0] == '['){
                if(small_data[1] < 48 || small_data[1] > 57){
                    throw std::invalid_argument("Invalid Matrix enteredA\n");
                }
            }
            else if(small_data[1] == ']'){
                if(small_data[2] == 0){}
                else{
                    if(small_data[2] != ',' ){
                        throw std::invalid_argument("Invalid Matrix entered\n");
                    }
                    if(small_data[3] != 0){
                        throw std::invalid_argument("Invalid Matrix entered\n");
                    }
                }
            }
            curr += small_data;
        }
        for (unsigned int i = 0; i < curr.length(); ++i) {
            if (curr[i] != '['){
                throw std::invalid_argument("Invalid Matrix entered\n");
            }
            row++;
            i++;
            while (curr[i] != ']'){
                if(curr[i] < 48 || curr[i] > 57){
                    throw std::invalid_argument("Invalid Matrix entered\n");
                }
                string value="";
                value += curr[i];
                m.mat.push_back(std::stod(value));
                i++;
            }
            i++;
            if (curr[i] == '\0'){
                break;
            }
            if (curr[i] != ','){
                throw std::invalid_argument("Invalid Matrix entered\n");
            }
        }
        m.row = row;
        if (row == 0){
            throw std::invalid_argument("Invalid Matrix entered\n");
        }
        m.col = (int)(m.mat.size()) / row;
        return is;
    }
}