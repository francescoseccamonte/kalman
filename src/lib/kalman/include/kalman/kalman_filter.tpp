/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */

#include <iostream>
#include <stdexcept>

namespace kalman
{

    template<typename T, int n, int m, int h>
    KF<T, n, m, h>::KF(const Matrix& A, const Matrix& B, const Matrix& H):
            A_(A),
            B_(B),
            H_(H),
            initialized_(false)
    {
        if (A_.rows() != A_.cols() || A_.rows() != B_.rows() || A_.cols() != H_.cols() ||
            A_.rows() != n || B_.cols() != m || H_.rows() != h) {
            std::cout << "Throwing" << std::endl;
            throw std::invalid_argument("Wrong input sizes");
        }
        P_.setIdentity();
        Q_.setIdentity();
        R_.setIdentity();
        x_.setZero();
    }

    template<typename T, int n, int m, int h>
    void KF<T, n, m, h>::initializeKF(const KF::Vector& x0, const KF::Matrix& P0, const KF::Matrix& sigma2v, const KF::Matrix& sigma2w) {
        if (x0.rows() != n || sigma2v.rows() != sigma2v.cols() || sigma2v.rows() != n ||
            P0.rows() != P0.cols() || P0.rows() != n ||
            sigma2w.rows() != sigma2w.cols() || sigma2w.rows() != h) {
            throw std::invalid_argument("Wrong input sizes");
        }
        x_ = x0;
        P_ = P0;
        Q_ = sigma2v;
        R_ = sigma2w;
        initialized_ = true;
    }

    template<typename T, int n, int m, int h>
    void KF<T, n, m, h>::priorUpdate(const KF::Vectorm& u) {
        x_ = A_ * x_ + B_ * u;
        P_ = A_ * P_ * A_.transpose() + Q_;
    }

    template<typename T, int n, int m, int h>
    void KF<T, n, m, h>::measurementUpdate(const KF::Vectorh& z) {
        Vectorh innovation = z - H_*x_;
        Matrixnh Kk = P_ * H_.transpose() * (H_ * P_ * H_.transpose() + R_).inverse();
        x_ += Kk * innovation;
        // Covariance update in Joseph form
        P_ = ( Inn - Kk * H_) * P_ * (Inn - Kk * H_).transpose() + Kk * R_ * Kk.transpose();
    }

    template<typename T, int n, int m, int h>
    typename KF<T, n, m, h>::Vectorn KF<T, n, m, h>::getLatestState() const {
        if (!initialized_)
            this->error();
        return x_;
    }

    template<typename T, int n, int m, int h>
    typename KF<T, n, m, h>::Matrixnn KF<T, n, m, h>::getCovariance() const {
        return P_;
    }

    template<typename T, int n, int m, int h>
    void KF<T, n, m, h>::error() const {
        std::cout << "An error occurred: don't trust the return value!" << "\n";
    }

} // namespace kalman
