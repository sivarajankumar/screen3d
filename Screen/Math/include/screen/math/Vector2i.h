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
 * \file Vector2i.h
 * \brief Vector2i header file for screen::math
 * \author Ratouit Thomas
 * \date 11 nov. 09
 *
 * Two-dimensional vector definition and mathematical definitions on 2-dimensional vectors
 */

#ifndef SCREEN_VECTOR_2_I_H
#define SCREEN_VECTOR_2_I_H

#include <screen/utils/Declaration.h>
#include <screen/math/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
	namespace math {

		class SCREEN_MATH_EXPORT Vector2i{
			SCREEN_DECL_CLASS(screen::math::Vector2i)
		public:
			Vector2i(int x=0, int y=0);
			~Vector2i();
			
			void set(int x, int y);
			void get(int& x, int& y) const;
			
			void setX(int x);
			void setY(int y);
			int getX() const;
			int getY() const;
			
			Vector2i operator +() const;
			Vector2i operator -() const;
            
			Vector2i operator +(const Vector2i& v) const;
			Vector2i operator -(const Vector2i& v) const;
			Vector2i operator *(int t) const;
			Vector2i operator /(int t) const;
            
            const Vector2i& operator +=(const Vector2i& v);
            const Vector2i& operator -=(const Vector2i& v);
            const Vector2i& operator *=(int t);
            const Vector2i& operator /=(int t);
            
			bool operator == (const Vector2i& v) const;
			bool operator != (const Vector2i& v) const;
            
            int& operator ()(unsigned int i);
            const int& operator()(unsigned int i) const;
            
            operator int* ();
            operator const int* () const;
		private:
			int x,y;
		};
		
		Vector2i operator *(int t, const Vector2i& v);
	}
}

#endif
