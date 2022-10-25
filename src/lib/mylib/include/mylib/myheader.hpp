/*
 * Author : Francesco Seccamonte
 * Copyright (c) 2022 Francesco Seccamonte. All rights reserved.  
 * Licensed under the Apache 2.0 License. See LICENSE file in the project root for full license information.  
 */ 

#ifndef MYHEADER_EXAMPLE_HPP
#define MYHEADER_EXAMPLE_HPP

#include <tuple>
#include <ostream>

/** \brief Accessor for MyClass.
 *
 * It is implemented leveraging
 * the return type of std::get
 * to avoid code duplication.
 */
struct MyClassAccessor {

	/** \brief Accessor function.
	 *
	 * Function performing access and
	 * mutation on the member of MyClass.
	 */
    template<class T>
    inline static
    decltype(auto) mymember(T& myclass) {
        return std::get<0>(myclass);
    }

};

/** \brief MyClass.
 *
 * Example class, inheriting from a template
 * tuple to leverage its functionalities.
 */
template<class Tuple>
struct MyClass : public Tuple {

	/** \brief Constructor.
	 *
	 * It takes one float as argument.
	 */
    explicit MyClass(float in) : Tuple(in) {}

    /** \brief Setter/Getter.
	 *
	 * Setter/Getter using the accessor.
	 */
    inline decltype(auto) mymember() {
        return MyClassAccessor::mymember(*this);
    }

    /** \brief Getter for const class.
	 *
	 * Getter employed when the manipulated object
	 * is marked as const.
	 */
    inline decltype(auto) mymember() const {
        return MyClassAccessor::mymember(*this);
    }

};

/** \brief ostream operator for MyClass.
 *
 * Prints member variables and a newline.
 */
template<class T>
std::ostream& operator<<(std::ostream &os, const MyClass<T>& m)
{
	os << m.mymember() << "\n";
	return os;
}

#endif //MYHEADER_EXAMPLE_HPP
