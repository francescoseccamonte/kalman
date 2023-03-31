/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.
 */

#include<kalman/kalman_filter.hpp>

#include <gtest/gtest.h>


template<typename T>
class KalmanFilterTests : public ::testing::Test {};

using Types = testing::Types<float, double>;
TYPED_TEST_SUITE(KalmanFilterTests, Types, );

TYPED_TEST(KalmanFilterTests, constructor1D)
{
    // Test constructor for 1D system, 1D input
    const Eigen::Matrix<TypeParam, 1, 1> A {TypeParam(-1.)};
    const Eigen::Matrix<TypeParam, 1, 1> B {TypeParam(.9)};
    const Eigen::Matrix<TypeParam, 1, 1> H {TypeParam(1.)};

    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H));
}

TYPED_TEST(KalmanFilterTests, constructor2DA)
{
    // Test constructor for 2D system, 1D input
    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
                                             {TypeParam(.1), TypeParam(-2.)} };
    const Eigen::Matrix<TypeParam, 2, 1> B { {TypeParam(.9)}, {TypeParam(.8)} };
    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };

    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H));
}

TYPED_TEST(KalmanFilterTests, constructor2DB)
{
    // Test constructor for 2D system, 2D input
    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
                                             {TypeParam(.1), TypeParam(-2.)} };
    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
                                             {TypeParam(.1), TypeParam(.8)} };
    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };

    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H));
}

TYPED_TEST(KalmanFilterTests, constructorTA)
{
    // Test constructor throws
    const Eigen::Matrix<TypeParam, 1, 2> A { {TypeParam(-1.), TypeParam(.1)} };
    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
                                             {TypeParam(.1), TypeParam(.8)} };
    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };

    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H));
}

TYPED_TEST(KalmanFilterTests, constructorTB)
{
    // Test constructor throws
    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
                                             {TypeParam(.1), TypeParam(-2.)} };
    const Eigen::Matrix<TypeParam, 1, 2> B { {TypeParam(.9), TypeParam(0.)} };
    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)}};

    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H));
}

TYPED_TEST(KalmanFilterTests, constructorTC)
{
    // Test constructor throws
    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
                                             {TypeParam(.1), TypeParam(-2.)} };
    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
                                             {TypeParam(.1), TypeParam(.8)} };
    const Eigen::Matrix<TypeParam, 1, 1> H { TypeParam(1.)};

    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H));
}
