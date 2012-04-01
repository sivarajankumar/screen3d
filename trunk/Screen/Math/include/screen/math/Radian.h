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
 * \file Radian.h
 * \brief The class used to represent the Radian unit
 * \author pjdemaret
 *
 * This class is used to represent the radian unit used for angles representation.
 */

#ifndef SCREEN_RADIAN_H
#define SCREEN_RADIAN_H

#include <screen/utils/Declaration.h>

/**
 * Namespace all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
	namespace math {

		class Degree;

		/**
		 * \brief Radian unit class
		 */
		class Radian{
			SCREEN_DECL_CLASS(screen::math::Radian)
		public:

			/**
			 * Constructor
			 */
			explicit Radian ( float iValue=0 ) : _value(iValue) {}
			/**
			 * Destructor
			 */
			virtual ~Radian() {}
			/**
			 * Constructor from a degree value
			 * Convert degree to radian
			 */
			Radian ( const Degree& iDegree );
			/**
			 * Assignation operator from a float
			 */
			Radian& operator = ( const float& iValue ) { _value = iValue; return *this; }
			/**
			 * Assignation operator from a radian
			 */
			Radian& operator = ( const Radian& iRadian ) { _value = iRadian._value; return *this; }
			/**
			 * Assignation operator from a degree: do the conversion
			 */
			Radian& operator = ( const Degree& iDegree );
			/**
			 * \brief Get the value converted in degree
			 * \return angle in degree
			 */
			float getDegreeValue() const;
			/**
			 * \brief Get value converted in radians
			 * \return radian value
			 */
			float getRadianValue() const { return _value; }
			/**
			 * \brief \see getRadianValue()
			 * \return radian value
			 */
			float getValue() const {return _value;}
			/**
			 * Conversion operator to float
			 */
			operator const float () {return _value;}
			/**
			 * \brief unary + operator
			 */
			const Radian& operator + () const { return *this; }
			/**
			 * \brief addition operator (radian + radian)
			 */
			Radian operator + ( const Radian& iRadian ) const { return Radian ( _value + iRadian._value ); }
			/**
			 * \brief addition operator (radian + degree)
			 */
			Radian operator + ( const Degree& iDegree ) const;
			/**
			 * \brief addition assignment operator (from radian)
			 */
			Radian& operator += ( const Radian& iRadian ) { _value += iRadian._value; return *this; }
			/**
			 * \brief addition assignment operator (from degree)
			 */
			Radian& operator += ( const Degree& iDegree );
			/**
			 * \brief unary - operator
			 */
			Radian operator - () const { return Radian(-_value); }
			/**
			 * \brief subtraction operator (radian - radian)
			 */
			Radian operator - ( const Radian& iRadian ) const { return Radian ( _value - iRadian._value ); }
			/**
			 * \brief subtraction operator (radian - degree)
			 */
			Radian operator - ( const Degree& iDegree ) const;
			/**
			 * \brief subtraction assignment operator (from radian)
			 */
			Radian& operator -= ( const Radian& iRadian ) { _value -= iRadian._value; return *this; }
			/**
			 * \brief subtraction assignment operator (from degree)
			 */
			Radian& operator -= ( const Degree& iDegree );
			/**
			 * \brief multiplication operator (radian * float)
			 */
			Radian operator * ( float iValue ) const { return Radian ( _value * iValue ); }
			/**
			 * \brief multiplication operator (radian * radian)
			 */
			Radian operator * ( const Radian& iRadian ) const { return Radian ( _value * iRadian._value ); }
			/**
			 * \brief multiplication assignment operator (from float)
			 */
			Radian& operator *= ( float iValue ) { _value *= iValue; return *this; }
			/**
			 * \brief division operator (radian / float)
			 */
			Radian operator / ( float iValue ) const { return Radian ( _value / iValue ); }
			/**
			 * \brief division assignment operator (from float)
			 */
			Radian& operator /= ( float iValue ) { _value /= iValue; return *this; }
			/**
			 * \brief less than operator
			 */
			bool operator <  ( const Radian& iRadian ) const { return _value <  iRadian._value; }
			/**
			 * \brief less than or equal to operator
			 */
			bool operator <= ( const Radian& iRadian ) const { return _value <= iRadian._value; }
			/**
			 * \brief equal to operator
			 */
			bool operator == ( const Radian& iRadian ) const { return _value == iRadian._value; }
			/**
			 * \brief not equal to operator
			 */
			bool operator != ( const Radian& iRadian ) const { return _value != iRadian._value; }
			/**
			 * \brief greater than or equal to operator
			 */
			bool operator >= ( const Radian& iRadian ) const { return _value >= iRadian._value; }
			/**
			 * \brief greater than operator
			 */
			bool operator >  ( const Radian& iRadian ) const { return _value >  iRadian._value; }

			/**
			 * \brief convert radian value to degree value
			 * \param[in] iRadian radian value
			 * \return degree value
			 */
			static float ToDegree(const float iRadian);

		private:

			float _value;		///< value in radian
		};
	}
}


#endif // SCREEN_RADIAN_H
