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
     * The non template parameters are state,
     * input and measurement vectors sizes, respectively.
     */
    template<typename T, int n, int m, int h>
    class KF
    {
        // convenience aliases
        using Matrix    = typename Eigen::Matrix<T, -1, -1>;
        using Matrixnn  = typename Eigen::Matrix<T, n, n>;
        using Matrixnm  = typename Eigen::Matrix<T, n, m>;
        using Matrixhn  = typename Eigen::Matrix<T, h, n>;
        using Matrixnh  = typename Eigen::Matrix<T, n, h>;
        using Matrixhh  = typename Eigen::Matrix<T, h, h>;
        using Vector    = typename Eigen::Matrix<T, -1, 1>;
        using Vectorn   = typename Eigen::Matrix<T, n, 1>;
        using Vectorm   = typename Eigen::Matrix<T, m, 1>;
        using Vectorh   = typename Eigen::Matrix<T, h, 1>;

     public:
         /* Class constructor.
          *
          */
         KF(const Matrix& A, const Matrix& B, const Matrix& H);

         /* Initialize Kalman Filter with
          * process, measurement covariance matrices,
          * and initial state.
          */
        void initializeKF(const Vector& x0, const KF::Matrix& P0, const Matrix& sigma2v, const Matrix& sigma2w);

        /* Prior update computation.
         *
         */
        void priorUpdate(const Vectorm& u);

        /* Measurement update computation.
         *
         */
        void measurementUpdate(const Vectorh& z);

         /* State getter.
          *
          */
         Vectorn getLatestState() const;

         /* Covariance getter.
          *
          */
         Matrixnn getCovariance() const;

     private:

         /* Custom error function
          * (not really useful in this context),
          * allows user to make class
          * exception-safe or not.
          */
         void error() const;

        // System parameters
        const Matrixnn A_;      // State matrix (n_ \times n_)
        const Matrixnm B_;      // Input matrix (n_ \times m_)
        const Matrixhn H_;      // Observation matrix (h_ \times n_)
        Matrixnn P_;            // state variance (n_ \times n_)
        Matrixnn Q_;            // process noise variance (n_ \times n_)
        Matrixhh R_;            // measurement noise variance (h_ \times h_)

        // Process variables
        Vectorn x_;         // state vector    (n_)
        bool initialized_; // whether the initialization has been provided

        // Identity of size n \times n conveniently defined
        const Matrixnn Inn = Eigen::Matrix<T, n, n>::Identity();
     };

}   // namespace kalman

#include "kalman_filter.tpp"

#endif // KALMAN_FILTER_HPP
