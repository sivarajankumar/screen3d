/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2009 Ratouit Thomas                                    *
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

#ifndef SCREEN_VECTOR_2_F_H
#define SCREEN_VECTOR_2_F_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Math {

		class SCREEN_EXPORT Vector2f{
			SCREEN_DECL_CLASS(Screen::Math::Vector2f)
		public:
			Vector2f(float x=0, float y=0);
			~Vector2f();
			
			void set(float x, float y);
			void get(float& x, float& y) const;
			
			void setX(float x);
			void setY(float y);
			float getX() const;
			float getY() const;
			
			Vector2f operator +() const;
			Vector2f operator -() const;
            
			Vector2f operator +(const Vector2f& v) const;
			Vector2f operator -(const Vector2f& v) const;
			Vector2f operator *(float t) const;
			Vector2f operator /(float t) const;
            
            const Vector2f& operator +=(const Vector2f& v);
            const Vector2f& operator -=(const Vector2f& v);
            const Vector2f& operator *=(float t);
            const Vector2f& operator /=(float t);
            
			bool operator == (const Vector2f& v) const;
			bool operator != (const Vector2f& v) const;
            
            float& operator ()(unsigned int i);
            const float& operator()(unsigned int i) const;
            
            operator float* ();
            operator const float* () const;
		private:
			float x,y;
		};
		
		Vector2f operator *(float t, const Vector2f& v);
	}
}

#endif
