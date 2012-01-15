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
 * \file Other.h
 * \brief Other mathematical operations header file for screen::math
 * \author Ratouit Thomas
 *
 * Set of mathematical functions
 */

#ifndef SCREEN_MATH_OTHER_H
#define SCREEN_MATH_OTHER_H

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
	namespace math {

		/**
		 * \brief Returns the nearest power of two of the given value
		 * \param[in] value input value
		 * \return The nearest power of two of the given value
		 */
		unsigned int nearestPowerOfTwo(unsigned int value){
	        unsigned int tmp = value;
	        unsigned int ret = 1;

	        while (tmp > 1){
	            tmp >>= 1;
	            ret <<= 1;
	        }

	        return ret == value ? ret : ret << 1;
		}

		/**
		 * \brief Compute an integer power another
		 * \param[in] value1 base value
		 * \param[in] value2 power value
		 * \return value1 power value2
		 */
		unsigned int power(unsigned int value1, unsigned int value2){
	        unsigned int ret = 1;

	        for(int i=0; i<value2; i++){
				ret *= value1;
			}

	        return ret;
		}

	}
}

#endif // SCREEN_MATH_OTHER_H
