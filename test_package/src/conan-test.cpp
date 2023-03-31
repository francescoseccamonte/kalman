/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#include <kalman/kalman_filter.hpp>

int main()
{
    const Eigen::Matrix<double, 1, 1> Ad {double(-1.)};
    const Eigen::Matrix<double, 1, 1> Bd {double(.9)};
    const Eigen::Matrix<double, 1, 1> Hd {double(1.)};

    kalman::KF<TypeParam> kfd(Ad, Bd, Hd);

    const Eigen::Matrix<float, 1, 1> Af {double(-1.)};
    const Eigen::Matrix<float, 1, 1> Bf {double(.9)};
    const Eigen::Matrix<float, 1, 1> Hf {double(1.)};

    kalman::KF<TypeParam> kff(Af, Bf, Hf);

    return 0;
}
