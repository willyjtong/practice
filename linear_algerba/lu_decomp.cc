// lu_decomp.h

#include <algorithm>
#include <cassert>
#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "lu_decomp.h"

using namespace std;
using namespace Eigen;


// LU decomposition
// The L and U will be stored in original matrix,
// So the original matrix will be changed.
int lu_decomp(MatrixXf& mat)
{
    int s = std::min(mat.rows(), mat.cols());
    for (int k = 0; k < s - 1; ++k)
    {
        if (std::abs(mat(k,k)) < 10e-4)
            return -1;
        float x = 1.0 / mat(k,k);
        for (int i =  k+1; i < mat.rows(); ++i)
        {
            mat(i,k) = mat(i,k) * x;
        }
        for (int i = k+1; i < mat.rows(); ++i)
        {
            for (int j = k+1; j < mat.cols(); ++j)
            {
                mat(i,j) = mat(i,j) - mat(i,k) * mat(k,j);
            }
        }
    }
    return 0;
}

float det(MatrixXf& mat)
{
    assert(mat.rows() == mat.cols());

    lu_decomp(mat);

    float x = 1;
    for (int i = 0; i < mat.rows(); ++i)
        x *= mat(i,i);
    return x;
}

int solve_l(MatrixXf& LU, VectorXf& y, VectorXf& z)
{
    for (int i = 0; i < z.rows(); ++i)
    {
        z[i] = y[i];
        for (int j = 0; j < i; ++j)
            z[i] -= LU(i, j) * z[j];
    }
    return 0;
}

int solve_u(MatrixXf& LU, VectorXf& z, VectorXf& x)
{
    for (int i = z.rows() - 1; i >=0; --i)
    {
        x[i] = z[i];
        for (int j = i+1; j < z.rows(); ++j)
            x[i] -= LU(i,j) * x[j];
        x[i] /= LU(i,i);
    }
    return 0;
}

int solve_lu(MatrixXf& LU, VectorXf& y, VectorXf& x)
{
    assert(LU.rows() == y.rows());
    VectorXf z(std::min(LU.rows(), LU.cols()));
    if (solve_l(LU, y , z) != 0)
        return -1;
    x.resize(LU.cols());
    if (solve_u(LU, z, x) != 0)
        return -1;
    return 0;
}

int solve(MatrixXf& A, VectorXf& y, VectorXf& x)
{
    assert(A.rows() == y.rows());
    lu_decomp(A);
    solve_lu(A, y, x);
}

float p_ref(MatrixXf& mat, int i, int j, int *p)
{
    return mat(p[i], j);
}

int p_set(MatrixXf& mat, int i, int j, int *p, float val)
{
    mat(p[i], j) = val;
}

int p_update(MatrixXf& mat, int k, int *p)
{
    if (k+1 == mat.rows()) return 0;
    int idx = -1;
    for (int i = k; i < mat.rows(); ++i)
    {
        float x = p_ref(mat,i,k,p);
        if (std::abs(x) > 10e-4) {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        return -1;  // no pivot, failed
    int pk = p[k];
    p[k] = p[idx];
    p[idx] = pk;
    return 0;
}

int plu_decomp(MatrixXf& mat)
{
    cout << "plu_decomp\n";
    int *p = new int[mat.rows()];
    for (int i = 0; i < mat.rows(); ++i)
        p[i] = i;

    int s = std::min(mat.rows(), mat.cols());

    for (int k = 0; k < s; ++k)
    {
        if (p_update(mat, k, p) != 0)
            return -1;
        float x = 1.0 / p_ref(mat, k, k, p);
        for (int i = k+1; i < mat.rows(); ++i)
        {
            float y = p_ref(mat,i,k,p) * x;
            p_set(mat,i,k,p,y);
        }
        for (int i = k+1; i < mat.rows(); ++i)
            for (int j = k+1; j < mat.cols(); ++j)
            {
                float z = p_ref(mat,i,j,p)
                    - p_ref(mat,i,k,p) *p_ref(mat,k,j,p);
                p_set(mat, i, j, p, z);
            }
    }
    delete p;
    return 0;
}
