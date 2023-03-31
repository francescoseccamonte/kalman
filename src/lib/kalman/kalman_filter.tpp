/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */

#include<kalman/kalman_filter.hpp>

#include <stdexcept>

namespace kalman
{

    template<typename T> KF<T>::KF(const Matrix& A, const Matrix& B, const Matrix& H):
    n_(A.rows()),
    m_(B.cols()),
    h_(H.rows()),
    A_(A),
    B_(B),
    H_(H)
    {
        if (A.rows() != A.cols() || A.rows() != B.rows() || A.rows() != H.cols()) {
            throw std::invalid_argument("Wrong input sizes");
        }
    }

} // namespace kalman
