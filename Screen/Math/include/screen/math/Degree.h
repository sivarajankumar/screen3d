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
 * \file Degree.h
 * \brief The class used to represent the Degree unit
 * \author pjdemaret
 *
 * This class is used to represent the Degree unit used for angles representation.
 */

#ifndef SCREEN_DEGREE_H
#define SCREEN_DEGREE_H

#include <screen/utils/Declaration.h>

/**
 * Namespace all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
	namespace math {

		class Radian;

		/**
		 * \brief Degree unit class
		 */
		class Degree{
			SCREEN_DECL_CLASS(screen::math::Degree)
		public:

			/**
			 * Constructor
			 */
			explicit Degree ( float iValue=0 ) : _value(iValue) {}
			/**
			 * Destructor
			 */
			virtual ~Degree() {}
			/**
			 * Constructor from a Radian value
			 * Convert Radian to Degree
			 */
			Degree ( const Radian& iRadian );
			/**
			 * Assignation operator from a float
			 */
			Degree& operator = ( const float& iValue ) { _value = iValue; return *this; }
			/**
			 * Assignation operator from a Degree
			 */
			Degree& operator = ( const Degree& iDegree ) { _value = iDegree._value; return *this; }
			/**
			 * Assignation operator from a Radian: do the conversion
			 */
			Degree& operator = ( const Radian& iRadian );
			/**
			 * \brief Get the value converted in Radian
			 * \return angle in Radian
			 */
			float getRadianValue() const;
			/**
			 * \brief Get value converted in Degrees
			 * \return Degree value
			 */
			float getDegreeValue() const { return _value; }
			/**
			 * \brief \see getDegreeValue()
			 * \return Degree value
			 */
			float getValue() const {return _value;}
			/**
			 * Conversion operator to float
			 */
			operator const float () {return _value;}
			/**
			 * \brief unary + operator
			 */
			const Degree& operator + () const { return *this; }
			/**
			 * \brief addition operator (Degree + Degree)
			 */
			Degree operator + ( const Degree& iDegree ) const { return Degree ( _value + iDegree._value ); }
			/**
			 * \brief addition operator (Degree + Radian)
			 */
			Degree operator + ( const Radian& iRadian ) const;
			/**
			 * \brief addition assignment operator (from Degree)
			 */
			Degree& operator += ( const Degree& iDegree ) { _value += iDegree._value; return *this; }
			/**
			 * \brief addition assignment operator (from Radian)
			 */
			Degree& operator += ( const Radian& iRadian );
			/**
			 * \brief unary - operator
			 */
			Degree operator - () const { return Degree(-_value); }
			/**
			 * \brief subtraction operator (Degree - Degree)
			 */
			Degree operator - ( const Degree& iDegree ) const { return Degree ( _value - iDegree._value ); }
			/**
			 * \brief subtraction operator (Degree - Radian)
			 */
			Degree operator - ( const Radian& iRadian ) const;
			/**
			 * \brief subtraction assignment operator (from Degree)
			 */
			Degree& operator -= ( const Degree& iDegree ) { _value -= iDegree._value; return *this; }
			/**
			 * \brief subtraction assignment operator (from Radian)
			 */
			Degree& operator -= ( const Radian& iRadian );
			/**
			 * \brief multiplication operator (Degree * float)
			 */
			Degree operator * ( float iValue ) const { return Degree ( _value * iValue ); }
			/**
			 * \brief multiplication operator (Degree * Degree)
			 */
			Degree operator * ( const Degree& iDegree ) const { return Degree ( _value * iDegree._value ); }
			/**
			 * \brief multiplication assignment operator (from float)
			 */
			Degree& operator *= ( float iValue ) { _value *= iValue; return *this; }
			/**
			 * \brief division operator (Degree / float)
			 */
			Degree operator / ( float iValue ) const { return Degree ( _value / iValue ); }
			/**
			 * \brief division assignment operator (from float)
			 */
			Degree& operator /= ( float iValue ) { _value /= iValue; return *this; }
			/**
			 * \brief less than operator
			 */
			bool operator <  ( const Degree& iDegree ) const { return _value <  iDegree._value; }
			/**
			 * \brief less than or equal to operator
			 */
			bool operator <= ( const Degree& iDegree ) const { return _value <= iDegree._value; }
			/**
			 * \brief equal to operator
			 */
			bool operator == ( const Degree& iDegree ) const { return _value == iDegree._value; }
			/**
			 * \brief not equal to operator
			 */
			bool operator != ( const Degree& iDegree ) const { return _value != iDegree._value; }
			/**
			 * \brief greater than or equal to operator
			 */
			bool operator >= ( const Degree& iDegree ) const { return _value >= iDegree._value; }
			/**
			 * \brief greater than operator
			 */
			bool operator >  ( const Degree& iDegree ) const { return _value >  iDegree._value; }

			/**
			 * \brief convert Degree value to Radian value
			 * \param[in] iDegree Degree value
			 * \return Radian value
			 */
			static float ToRadian(const float iDegree);

		private:

			float _value;		///< value in Degree
		};
	}
}


#endif // SCREEN_DEGREE_H
