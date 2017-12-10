// arithmetic

#include <cassert>
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;


int vector_add(VectorXd& a, VectorXd& b, VectorXd& c)
{
    if ( a.rows() != b.rows() ) {
        std::cout << "Size mismatch\n";
        return 1;
    }

    c.resize(a.rows());
    std::cout << "Debug: \n" << c << std::endl;

    for (int i = 0; i < a.rows(); ++i)
        c(i) = a(i) + b(i);
    return 0;
}

int matrix_vector_prod(MatrixXd& A, VectorXd& x, VectorXd& y)
{
    if (A.cols() != x.rows()) {
        std::cout << "Size mismatch\n";
        return 1;
    }

    y.resize(A.rows());
    std::cout << "Debug:\n" << y << std::endl;

    for (int i = 0; i < A.rows(); ++i) {
        double tmp = 0;
        for (int j = 0; j < x.rows(); ++j) {
            tmp += A(i, j) * x(j);
        }
        y(i) = tmp;
    }
    return 0;
}

int matrix_prod(MatrixXd& U, MatrixXd& V, MatrixXd& C)
{
    if (U.cols() != V.rows()) {
        std::cout << "Size mismatch\n";
        return 1;
    }

    C.resize(U.rows(), V.cols());
    std::cout << "Debug:\n" << C << std::endl;

    for (int i = 0; i < U.rows(); ++i) {
        for (int j = 0; j < V.cols(); ++j) {
            double tmp = 0;
            for (int k = 0; k < U.cols(); ++k)
                tmp += U(i,k) * V(k,j);
            C(i,j) = tmp;
        }
    }
}

int main(int argc, char* argv[])
{
    // vector_add
    VectorXd a = VectorXd::Constant(3, 1);
    VectorXd b = VectorXd::Random(3);
    std::cout << "Vector a is:\n" << a << std::endl
        << "Vector b is:\n" << b << std::endl
        << "The a + b in Eigen is:\n" << a + b << std::endl;
    VectorXd c;
    if (vector_add(a, b, c) == 0) {
        std::cout << "Vector c is:\n" << c << "\n\n";
    }

    // matrix_vector_prod
    MatrixXd A = MatrixXd::Identity(4,4) * 0.5;
    VectorXd x = VectorXd::Constant(4,2);
    std::cout << "Matrix A is:\n" << A << std::endl
        << "Vector x is:\n" << x << std::endl
        << "The A * x in Eigen is:\n" << A * x << std::endl;
    VectorXd y;
    if (matrix_vector_prod(A, x, y) == 0) {
        std::cout << "Vector y is:\n" << y << "\n\n";
    }

    // matrix_matrix_prod
    MatrixXd U(3,3);
    U << 2, 3, 3,
         3, 4, 2,
        -2,-2, 3;
    MatrixXd V(3,3);
    V << -16, 15, 6,
          13,-12,-5,
          -2,  2, 1;
    std::cout << "Matrix U is:\n" << U << std::endl
        << "Matrix V is:\n" << V << std::endl
        << "The U * V in Eigen is:\n" << U * V << std::endl;
    MatrixXd C;
    if (matrix_prod(U, V, C) == 0) {
        std::cout << "Matrix C is:\n" << C << "\n\n";
    }
}
