/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2023 Francesco Seccamonte. All rights reserved.
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.
 */

#include<kalman/kalman_filter.hpp>

#include <gtest/gtest.h>

using namespace kalman;


struct KFTestParams {
    static constexpr int n = 3;
    static constexpr int m = 1;
    static constexpr int h = 2;
};


template<typename T>
class KFTest : public ::testing::Test {
protected:
    // Store common parameters
    void SetUp() override {
        // Set up the default parameters for the KF object
        A_.setIdentity();
        B_.setIdentity();
        H_.setIdentity();
    }

    // System parameters
    Eigen::Matrix<T, KFTestParams::n, KFTestParams::n> A_; // State matrix
    Eigen::Matrix<T, KFTestParams::n, KFTestParams::m> B_; // Input matrix
    Eigen::Matrix<T, KFTestParams::h, KFTestParams::n> H_; // Observation matrix
};

// Define the types to be used in the typed tests
using TestTypes = ::testing::Types<float, double>;

TYPED_TEST_SUITE(KFTest, TestTypes,);

// Test case for constructing the KF object
TYPED_TEST(KFTest, Constructor) {

    using Filter = KF<TypeParam, KFTestParams::n, KFTestParams::m, KFTestParams::h>;

    ASSERT_NO_THROW(Filter(this->A_, this->B_, this->H_));
}

// Test case for initializing matrices in the KF object
TYPED_TEST(KFTest, Initialization) {
    Eigen::Matrix<TypeParam, KFTestParams::n, 1> x0;
    Eigen::Matrix<TypeParam, KFTestParams::n, KFTestParams::n> P0;
    Eigen::Matrix<TypeParam, KFTestParams::n, KFTestParams::n> sigma2v;
    Eigen::Matrix<TypeParam, KFTestParams::h, KFTestParams::h> sigma2w;

    x0.setZero();
    P0.setIdentity();
    sigma2v.setIdentity();
    sigma2w.setIdentity();

    using Filter = KF<TypeParam, KFTestParams::n, KFTestParams::m, KFTestParams::h>;

    Filter kf(this->A_, this->B_, this->H_);
    kf.initializeKF(x0, P0, sigma2v, sigma2w);

    ASSERT_TRUE(x0.isApprox(kf.getLatestState()));
    ASSERT_TRUE(P0.isApprox(kf.getCovariance()));
}
