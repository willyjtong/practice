#ifndef LU_DECOMP_H
#define LU_DECOMP_H

#include <Eigen/Dense>

int lu_decomp(Eigen::MatrixXf& mat);

int plu_decomp(Eigen::MatrixXf& mat);

float det(Eigen::MatrixXf& mat);

int solve(Eigen::MatrixXf& A, Eigen::VectorXf& y, Eigen::VectorXf& x);

#endif
