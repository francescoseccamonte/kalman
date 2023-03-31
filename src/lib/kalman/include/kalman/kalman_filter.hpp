/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include <Eigen/Dense>

namespace kalman
{

    /** \brief Kalman Filter (KF).
     *
     * Kalman filter for a discrete time
     * linear time invariant  (LTI) system
     * subject to Gaussian noise.
     * The discrete-time LTI system is given by:
     *      x_{k+dt} = A x_k + B u_k + v_k
     *      z_{k}    = H x_k + w_k ,
     * with v_k ~ N(0,\sigma^2_v), w_k ~ N(0,\sigma^2_w) Gaussian noise.
     *
     * The template parameter is the floating
     * point type (float or double).
     */
     template<typename T>
     class KF
     {
         using Matrix = typename Eigen::Matrix<T, -1, -1>;
         using Vector = typename Eigen::Matrix<T, -1, -1>;

     public:
         KF(const Matrix& A, const Matrix& B, const Matrix& H);

     private:

         // System parameters
         const long n_;      // state dimension
         const long m_;      // input dimension
         const long h_;      // output dimension
         const Matrix A_;   // State matrix (n_ \times n_)
         const Matrix B_;   // Input matrix (n_ \times m_)
         const Matrix H_;   // Observation matrix (h_ \times n_)

         // Process variables
         Vector x_;         // state vector    (n_)
         Vector z_;         // observation vector  (h_)
         Matrix Q_;         // process noise variance (n_ \times n_)
         Matrix R_;         // measurement noise variance (h_ \times h_)
         bool initialized_; // whether the initialization has been provided
     };

}   // namespace kalman

#endif // KALMAN_FILTER_HPP
