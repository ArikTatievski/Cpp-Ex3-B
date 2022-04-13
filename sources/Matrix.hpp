#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
namespace zich
{
    class Matrix
    {
    public:
        int row;
        int col;
        vector<double> mat;

        Matrix(vector<double> m, int row, int col);
        Matrix(const Matrix& m);
        ~Matrix();

        double get(unsigned int i, unsigned int j) const;
        void matSizeCheck(const Matrix& m2) const;

        friend Matrix operator+ (const Matrix& m1,const Matrix& m2);
        friend Matrix &operator+= (Matrix& m1,const Matrix& m2);
        friend Matrix operator+ (const Matrix& m);

        friend Matrix operator- (const Matrix& m1,const Matrix& m2);
        friend Matrix &operator-= (Matrix& m1,const Matrix& m2);
        friend Matrix operator- (const Matrix& m);

        friend bool operator< (const Matrix& m1,const Matrix& m2);
        friend bool operator<= (const Matrix& m1,const Matrix& m2);
        friend bool operator> (const Matrix& m1,const Matrix& m2);
        friend bool operator>= (const Matrix& m1,const Matrix& m2);
        friend bool operator== (const Matrix& m1,const Matrix& m2);
        friend bool operator!= (const Matrix& m1,const Matrix& m2);

        friend Matrix &operator++ (Matrix& m);
        friend Matrix operator++ (Matrix& m,int c);
        friend Matrix &operator-- (Matrix& m);
        friend Matrix operator-- (Matrix& m,int c);

        friend Matrix operator* ( Matrix& m1,  Matrix& m2);
        friend Matrix operator* (Matrix& m, double c);
        friend Matrix operator* (double c, Matrix& m);

        friend Matrix &operator*= (Matrix& m,double c);
        friend Matrix &operator*= (double c,Matrix& m);
        friend Matrix &operator*= (Matrix& m1,const Matrix& m2);

        friend std::ostream& operator<<(std::ostream& os,const Matrix& m);
        friend std::istream& operator>>(std::istream& is, Matrix& m);
    };
}
