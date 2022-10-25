/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2022 Francesco Seccamonte. All rights reserved.  
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#include <mylib/myheader.hpp>

#include <iostream>

int main()
{
	MyClass<std::tuple<float>> myclass(1.0f);

	std::cout << "Hello my getter: " << myclass.mymember() << "\n";

	return 0;
}
