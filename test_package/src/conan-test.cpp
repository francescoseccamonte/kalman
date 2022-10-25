/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2022 Francesco Seccamonte. All rights reserved.  
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#include <mylib/myheader.hpp>

int main()
{
	const float a = 1.0;
	MyClass<std::tuple<float>> myclass(a);

	const auto b = myclass.mymember();
}
