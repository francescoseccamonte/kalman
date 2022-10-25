/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2022 Francesco Seccamonte. All rights reserved.  
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#include <gtest/gtest.h>

#include <mylib/myheader.hpp>

#include <sstream>  // to test operator<<

template<class T>
void test_getter_eq(const MyClass<T>& in, float a)
{
	EXPECT_FLOAT_EQ(in.mymember(), a);
}

TEST(mylibtest, members)
{
	const float a = 1.0;
	MyClass<std::tuple<float>> myclass(a);

	// test accessor
    EXPECT_FLOAT_EQ(myclass.mymember(), a);

    // test accessor (const)
    test_getter_eq(myclass, a);

    // test mutator
    const float b = 2.0;
    myclass.mymember() = b;
    EXPECT_FLOAT_EQ(myclass.mymember(), b);

}

TEST(mylibtest, ostreamoperator)
{
    const float a = 1.1f;
    MyClass<std::tuple<float>> myclass(a);

    std::stringstream out;
    out << myclass;

    EXPECT_EQ(out.str(), "1.1\n");
}
