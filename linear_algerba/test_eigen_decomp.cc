// lu.cc

#include <cassert>
#include <iostream>
#include <string>

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int example1()
{
    Matrix3f A;
    Vector3f b;
    A << 1,2,3, 4,5,6, 7,8,10;
    b << 3,3,4;
    cout << "Matrix A:\n" << A << endl
        << "Vector b:\n" << b << endl;

    ColPivHouseholderQR<Matrix3f> dec(A);
    Vector3f x = dec.solve(b);

    cout << "The solution is:\n" << x << endl;
}

int example2()
{
    Matrix2f A, b;
    A << 2, -1, -1, 3;
    b << 1, 2, 3, 1;
    cout << "Matrix A:\n" << A << endl
        << "the right hand side b:\n" << b << endl;
    Matrix2f x = A.ldlt().solve(b);
    cout << "The solutions is:\n" << x << endl;
}

int example3()
{
    MatrixXd A = MatrixXd::Random(100,100);
    MatrixXd b = MatrixXd::Random(100,50);
    MatrixXd x = A.fullPivLu().solve(b);
    double relative_error = (A*x - b).norm() / b.norm();
    cout << "The relative error is: " << relative_error << endl;

}

int example4()
{
    Matrix2f A;
    A << 1, 2, 2, 3;
    cout << "Matrix A:\n" << A << endl;

    SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
    if (eigensolver.info() != Success) abort();

    cout << "The eigenvalues of A is:\n"
        << eigensolver.eigenvalues() << endl;
    cout << "A matrix whose columns are eigenvalues of A\n"
        << "corresponding to these eigenvalues:\n"
        << eigensolver.eigenvectors() << endl;

}

int example5()
{
    Matrix3f A;
    A << 1, 2, 1,
         2, 1, 0,
        -1, 1, 2;
    cout << "Matrix A is:\n" << A << endl;

    cout << "The determinant of A is:\n"
        << A.determinant() << endl;
    cout << "The inverse of A is:\n"
        << A.inverse() << endl;
}

int example6()
{
    MatrixXf A = MatrixXf::Random(3,2);
    VectorXf b = VectorXf::Random(3);
    cout << "Matrix A is:\n" << A << endl;
    cout << "Vector b is:\n" << b << endl;

    cout << "The least squares solutions is:\n"
        << A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
}

int example7()
{
    Matrix2f A, b;
    LLT<Matrix2f> llt;
    A << 2, -1 , -1 , 3;
    b << 1, 2, 3, 1;
    cout << "Matrix A is:\n" << A << endl;
    cout << "Matrix b is:\n" << b << endl;
    llt.compute(A);
    cout << "The solutions is:\n" << llt.solve(b) << endl;

    A(1,1)++;
    cout << "The A is now:\n" << A << endl;
    cout << "Computing llt decomposition\n";
    llt.compute(A);
    cout << "The solution is now:\n" << llt.solve(b) << endl;
}

int example8()
{
    Matrix3f A;
    A <<1,2,5,
        2,1,4,
        3,0,3;
    cout << "The matrix is:\n" << A << endl;
    FullPivLU<Matrix3f> lu_decomp(A);
    cout << "Rank of A is:\n" << lu_decomp.rank() << endl;
    cout << "Matrix whose columns form a basis of the null-space of A:\n"
         << lu_decomp.kernel() << endl;
    cout << "Matrix whose columns form a basis of the column-space of A:\n"
         << lu_decomp.image(A) << endl;
}

int example9()
{
    Matrix2d A;
    A << 2, 1,
         2, 0.9999999999;
    FullPivLU<Matrix2d> lu(A);
    cout << "By default, the rank of A is " << lu.rank() << endl;
    lu.setThreshold(1e-5);
    cout << "With threshold 1e-5, the rank of A is  " << lu.rank() << endl;
}

int example_lu() {}

int eigen_examples(int nu)
{
    cout<< "Example " << nu << "\n";
    switch(nu)
    {
    case 1:
        example1();
        break;
    case 2:
        example2();
        break;
    case 3:
        example3();
        break;
    case 4:
        example4();
        break;
    case 5:
        example5();
        break;
    case 6:
        example6();
        break;
    case 7:
        example7();
        break;
    case 8:
        example8();
        break;
    case 9:
        example9();
        break;
    default:
        example_lu();

    }
}

int main(int argc, char* argv[])
{
    assert(argc > 0);
    for (int i = 1; i < argc; ++i) {
        eigen_examples(stoi(argv[i]));
    }
}
