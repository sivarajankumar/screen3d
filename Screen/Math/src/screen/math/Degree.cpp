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
 * \file Degree.cpp
 * \brief The class used to represent the Degree unit
 * \author pjdemaret
 *
 * This class is used to represent the Degree unit used for angles representation.
 */

// Math includes
#include <screen/math/Degree.h>
#include <screen/math/Radian.h>

// Utils include
#include <screen/utils/Constants.h>

namespace screen {

	using namespace utils;

	namespace math {

		Degree::Degree ( const Radian& iRadian )
			: _value(iRadian.getDegreeValue()){
			SCREEN_DECL_CONSTRUCTOR(Degree);
		}

		inline
		Degree& Degree::operator = ( const Radian& iRadian ){
			SCREEN_DECL_METHOD(operator =);
			_value = iRadian.getDegreeValue();
			return *this;
		}

		float Degree::getRadianValue() const{
			SCREEN_DECL_METHOD(getRadianValue);
			return Degree::ToRadian(_value);
		}

		inline
		Degree Degree::operator + ( const Radian& iRadian ) const{
			SCREEN_DECL_METHOD(operator +);
			return Degree( _value + iRadian.getDegreeValue());
		}

		inline
		Degree& Degree::operator += ( const Radian& iRadian ){
			SCREEN_DECL_METHOD(operator +=);
			_value += iRadian.getDegreeValue();
			return *this;
		}

		inline
		Degree Degree::operator - ( const Radian& iRadian ) const{
			SCREEN_DECL_METHOD(operator -);
			return Degree( _value + iRadian.getDegreeValue());
		}

		inline
		Degree& Degree::operator -= ( const Radian& iRadian ){
			SCREEN_DECL_METHOD(operator -=);
			_value -= iRadian.getDegreeValue();
			return *this;
		}

		inline
		float Degree::ToRadian(const float iDegree) {
			SCREEN_DECL_METHOD(ToRadian);
			return iDegree / 180 * Pi;
		}

	}
}
