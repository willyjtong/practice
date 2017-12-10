// test_lu_decomp.cc
#include <cassert>
#include <iostream>
#include <string>
#include <Eigen/Dense>

#include "lu_decomp.h"

using namespace std;
using namespace Eigen;

void test_lu_decomp()
{
    MatrixXf A(3,3);
    A << 1,2,5,
         2,1,4,
         3,0,3;
    cout << "The matrix is:\n" << A << endl;


    if (lu_decomp(A) == 0)
    {
        cout << "The matrix after decomp is:\n" << A << endl;
        MatrixXf L = A.triangularView<Lower>();
        L.diagonal() = ArrayXf::Ones(3);
        MatrixXf U = A.triangularView<Upper>();
        cout << "The L is:\n" << L << endl;
        cout << "The U is:\n" << U << endl;
        cout << "The LU is:\n" << L*U << endl;

    }
    else
    {
        cout << "Error lu_decomp()\n";
    }
}

void test_det()
{
    MatrixXf A(3,3);
    A << 1,2,5,
         2,1,4,
         3,0,3;
    cout << "The matrix is:\n" << A << endl;
    cout << "The det of A is: " << det(A) << endl;

}

void test_solve()
{
    MatrixXf A(3,3);
    A << 2, 3, 3,
         3, 4, 2,
        -2,-2, 3;
    VectorXf y(3);
    y << 9, 9, 2;
    cout << "The matrix is:\n" << A << endl;
    cout << "The vector is:\n" << y << endl;
    cout << "The solution should be:\n3\n-1\n2" << endl;
    VectorXf x;
    solve(A, y, x);
    cout << "The solution is:\n" << x << endl;
}

void test_plu_decomp()
{
    MatrixXf A(3,3);
    A << 1,2,5,
         2,1,4,
         3,0,3;
    cout << "The matrix is:\n" << A << endl;

    if (plu_decomp(A) == 0)
    {
        cout << "The matrix after decomp is:\n" << A << endl;
        MatrixXf L = A.triangularView<Lower>();
        L.diagonal() = ArrayXf::Ones(3);
        MatrixXf U = A.triangularView<Upper>();
        cout << "The L is:\n" << L << endl;
        cout << "The U is:\n" << U << endl;
        cout << "The LU is:\n" << L*U << endl;
    }
    else
    {
        cout << "Error lu_decomp()\n";
    }
}

int lu_tests(int nu)
{
    cout<< "Test " << nu << "\n";
    switch(nu)
    {
    case 1:
        test_lu_decomp();
        break;
    case 2:
        test_det();
        break;
    case 3:
        test_solve();
        break;
    case 4:
        test_plu_decomp();
        break;
    default:
        cout << "Wrong test\n";
    }
}

int main(int argc, char* argv[])
{
    assert(argc > 0);
    for (int i = 1; i < argc; ++i) {
        lu_tests(stoi(argv[i]));
    }
}

