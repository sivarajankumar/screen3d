/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2012 Ratouit Thomas                                    *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Lesser General Public License as published by  *
 * the Free Software Foundation; either version 3 of the License, or (at     *
 * your option) any later version.                                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser   *
 * General Public License for more details.                                  *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this program; if not, write to the Free Software Foundation,   *
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA, or go to   *
 * http://www.gnu.org/copyleft/lesser.txt.                                   *
 *****************************************************************************/
/**
 * \file Radian.cpp
 * \brief The class used to represent the Radian unit
 * \author pjdemaret
 *
 * This class is used to represent the radian unit used for angles representation.
 */

// Math includes
#include <screen/math/Radian.h>
#include <screen/math/Degree.h>

// Utils include
#include <screen/utils/Constants.h>

namespace screen {

	using namespace utils;

	namespace math {

		Radian::Radian ( const Degree& iDegree )
			: _value(iDegree.getRadianValue()){
			SCREEN_DECL_CONSTRUCTOR(Radian);
		}

		inline
		Radian& Radian::operator = ( const Degree& iDegree ){
			SCREEN_DECL_METHOD(operator =);
			_value = iDegree.getRadianValue();
			return *this;
		}

		float Radian::getDegreeValue() const{
			SCREEN_DECL_METHOD(getDegreeValue);
			return Radian::ToDegree(_value);
		}

		inline
		Radian Radian::operator + ( const Degree& iDegree ) const{
			SCREEN_DECL_METHOD(operator +);
			return Radian( _value + iDegree.getRadianValue());
		}

		inline
		Radian& Radian::operator += ( const Degree& iDegree ){
			SCREEN_DECL_METHOD(operator +=);
			_value += iDegree.getRadianValue();
			return *this;
		}

		inline
		Radian Radian::operator - ( const Degree& iDegree ) const{
			SCREEN_DECL_METHOD(operator -);
			return Radian( _value + iDegree.getRadianValue());
		}

		inline
		Radian& Radian::operator -= ( const Degree& iDegree ){
			SCREEN_DECL_METHOD(operator -=);
			_value -= iDegree.getRadianValue();
			return *this;
		}

		inline
		float Radian::ToDegree(const float iRadian) {
			SCREEN_DECL_METHOD(ToDegree);
			return iRadian / Pi * 180;
		}

	}
}
