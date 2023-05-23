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

//// Test case for initializing the KF object
//TYPED_TEST(KFTest, Initialization) {
//    Eigen::Matrix<TypeParam, 2, 1> x0(1.0, 2.0);
//    Eigen::Matrix<TypeParam, 2, 2> P0 = Eigen::Matrix<TypeParam, 2, 2>::Identity();
//    Eigen::Matrix<TypeParam, 2, 2> sigma2v = Eigen::Matrix<TypeParam, 2, 2>::Identity();
//    Eigen::Matrix<TypeParam, 1, 1> sigma2w(1.0);
//
//    this->kf_.initializeKF(x0, P0, sigma2v, sigma2w);
//
//    // Assert that the KF object is initialized
//    EXPECT_TRUE(this->kf_.isInitialized());
//}
//
//// Test case for the prior update computation
//TYPED_TEST(KFTest, PriorUpdate) {
//    Eigen::Matrix<TypeParam, 1, 1> u(0.5);
//
//    this->kf_.priorUpdate(u);
//
//    // Perform assertions on the updated state vector or other outputs as needed
//    // For example:
//    // EXPECT_NEAR(this->kf_.getLatestState()(0), expectedValue, tolerance);
//}
//
//// Test case for the measurement update computation
//TYPED_TEST(KFTest, MeasurementUpdate) {
//    Eigen::Matrix<TypeParam, 1, 1> z(1.5);
//
//    this->kf_.measurementUpdate(z);
//
//    // Perform assertions on the updated state vector or other outputs as needed
//    // For example:
//    // EXPECT_NEAR(this->kf_.getLatestState()(0), expectedValue, tolerance);
//}
//
//// Test case for getting the latest state
//TYPED_TEST(KFTest, GetLatestState) {
//    // Perform assertions on the initial state vector
//    // For example:
//    // EXPECT_NEAR(this->kf_.getLatestState()(0), expectedValue, tolerance);
//}
//
//// Test case for getting the covariance
//TYPED_TEST(KFTest, GetCovariance) {
//    // Perform assertions on the initial covariance matrix
//    // For example:
//    // EXPECT_NEAR(this->kf_.getCovariance()(0, 0), expectedValue, tolerance);
//}


//template<typename T>
//class KalmanFilterTests : public ::testing::Test {};
//
//using Types = testing::Types<float, double>;
//TYPED_TEST_SUITE(KalmanFilterTests, Types, );
//
//TYPED_TEST(KalmanFilterTests, constructor1D)
//{
//    // Test constructor for 1D system, 1D input
//    const Eigen::Matrix<TypeParam, 1, 1> A {TypeParam(-1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> B {TypeParam(.9)};
//    const Eigen::Matrix<TypeParam, 1, 1> H {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructor2DA)
//{
//    // Test constructor for 2D system, 1D input
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 2, 1> B { {TypeParam(.9)}, {TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> sigma2v {{TypeParam(1.), TypeParam(0.)},
//                                                  {TypeParam(0.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructor2DB)
//{
//    // Test constructor for 2D system, 2D input
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
//                                             {TypeParam(.1), TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> sigma2v {{TypeParam(1.), TypeParam(0.)},
//                                                  {TypeParam(0.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_NO_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructorTA)
//{
//    // Test constructor throws
//    const Eigen::Matrix<TypeParam, 1, 2> A { {TypeParam(-1.), TypeParam(.1)} };
//    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
//                                             {TypeParam(.1), TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructorTB)
//{
//    // Test constructor throws
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 1, 2> B { {TypeParam(.9), TypeParam(0.)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)}};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructorTC)
//{
//    // Test constructor throws
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> B { {TypeParam(.9), TypeParam(0.)},
//                                             {TypeParam(.1), TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 1> H { TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructorTD)
//{
//    // Test constructor throws
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 2, 1> B { {TypeParam(.9)}, {TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, constructorTE)
//{
//    // Test constructor throws
//    const Eigen::Matrix<TypeParam, 2, 2> A { {TypeParam(-1.), TypeParam(.1)},
//                                             {TypeParam(.1), TypeParam(-2.)} };
//    const Eigen::Matrix<TypeParam, 2, 1> B { {TypeParam(.9)}, {TypeParam(.8)} };
//    const Eigen::Matrix<TypeParam, 1, 2> H { {TypeParam(1.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> sigma2v {{TypeParam(1.), TypeParam(0.)},
//                                                  {TypeParam(0.), TypeParam(1.)} };
//    const Eigen::Matrix<TypeParam, 2, 2> sigma2w {{TypeParam(1.), TypeParam(0.)},
//                                                  {TypeParam(0.), TypeParam(1.)} };
//
//    ASSERT_ANY_THROW(kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w));
//}
//
//TYPED_TEST(KalmanFilterTests, getMeasurement)
//{
//    // Test constructor for 1D system, 1D input
//    const Eigen::Matrix<TypeParam, 1, 1> A {TypeParam(-1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> B {TypeParam(.9)};
//    const Eigen::Matrix<TypeParam, 1, 1> H {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2v {TypeParam(1.)};
//    const Eigen::Matrix<TypeParam, 1, 1> sigma2w {TypeParam(1.)};
//
//    auto kf = kalman::KF<TypeParam>(A, B, H, sigma2v, sigma2w);
//    auto z = kf.getLatestMeasurement();
//}
