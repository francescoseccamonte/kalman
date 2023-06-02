/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#include <kalman/kalman_filter.hpp>

int main()
{
    constexpr int n = 1;
    constexpr int m = 1;
    constexpr int h = 1;
    const Eigen::Matrix<double, n, n> Ad {double(-1.)};
    const Eigen::Matrix<double, n, m> Bd {double(.9)};
    const Eigen::Matrix<double, h, n> Hd {double(1.)};

    kalman::KF<double, n, m, h> kfd(Ad, Bd, Hd);

    const Eigen::Matrix<float, n, n> Af {float(-1.)};
    const Eigen::Matrix<float, n, m> Bf {float(.9)};
    const Eigen::Matrix<float, h, n> Hf {float(1.)};

    kalman::KF<float, n, m, h> kff(Af, Bf, Hf);

    return 0;
}
