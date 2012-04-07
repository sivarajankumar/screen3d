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
 * \file Vector2i.cpp
 * \brief Vector2i source code file for screen::math
 * \author Ratouit Thomas
 * \date 11 nov. 09
 *
 * Two-dimensional vector definition and mathematical definitions on 2-dimensional vectors
 */


#include <screen/math/Vector2i.h>

namespace screen {
	namespace math {
		Vector2i::Vector2i(int x, int y)
			:x(x),y(y){
			SCREEN_DECL_CONSTRUCTOR(Vector2i)
		}
			
		Vector2i::~Vector2i(){
			SCREEN_DECL_DESTRUCTOR(~Vector2i)
		}
		
		void Vector2i::set(int x, int y){
			SCREEN_DECL_METHOD(set)
			this->x = x;
			this->y = y;
		}
		
		void Vector2i::get(int& x, int& y) const{
			SCREEN_DECL_METHOD(get)
			x = this->x;
			y = this->y;
		}
		
		void Vector2i::setX(int x){
			SCREEN_DECL_METHOD(setX)
			this->x = x;
		}
		
		void Vector2i::setY(int y){
			SCREEN_DECL_METHOD(setY)
			this->y = y;
		}
		
		int Vector2i::getX() const{
			SCREEN_DECL_METHOD(getX)
			return x;
		}
		
		int Vector2i::getY() const{
			SCREEN_DECL_METHOD(getY)
			return y;
		}
		
		Vector2i Vector2i::operator +() const{
			SCREEN_DECL_METHOD(operator +)
			return *this;
		}
		
		Vector2i Vector2i::operator -() const{
			SCREEN_DECL_METHOD(operator -)
			return Vector2i(-x,-y);
		}
        
		Vector2i Vector2i::operator +(const Vector2i& v) const{
			SCREEN_DECL_METHOD(operator +)
			return Vector2i(x+v.x, y+v.y);
		}
		Vector2i Vector2i::operator -(const Vector2i& v) const{
			SCREEN_DECL_METHOD(operator -)
			return Vector2i(x-v.x, y-v.y);
		}
		
		Vector2i Vector2i::operator *(int t) const{
			SCREEN_DECL_METHOD(operator *)
			return Vector2i(x*t, y*t);
		}
		
		Vector2i Vector2i::operator /(int t) const{
			SCREEN_DECL_METHOD(operator /)
			return Vector2i(x/t, y/t);
		}
        
        const Vector2i& Vector2i::operator +=(const Vector2i& v){
        	SCREEN_DECL_METHOD(operator +=)
        	x+=v.x;
        	y+=v.y;
        	return *this;
        }
        const Vector2i& Vector2i::operator -=(const Vector2i& v){
        	SCREEN_DECL_METHOD(operator -=)
        	x-=v.x;
        	y-=v.y;
        	return *this;
        }
        const Vector2i& Vector2i::operator *=(int t){
        	SCREEN_DECL_METHOD(operator *=)
        	x*=t;
        	y*=t;
        	return *this;
        }
        const Vector2i& Vector2i::operator /=(int t){
        	SCREEN_DECL_METHOD(operator /=)
        	x/=t;
        	y/=t;
        	return *this;
        }
        
		bool Vector2i::operator == (const Vector2i& v) const{
			SCREEN_DECL_METHOD(operator ==)
			return (x==v.x) && (y==v.y);
		}
		bool Vector2i::operator != (const Vector2i& v) const{
			SCREEN_DECL_METHOD(operator !=)
			return !(*this == v);
		}
        
        int& Vector2i::operator ()(unsigned int i){
        	SCREEN_DECL_METHOD(operator ())
        	return operator int*()[i];
        }

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4717 )//disable a Visual Studio warning
#endif

        const int& Vector2i::operator()(unsigned int i) const{
        	SCREEN_DECL_METHOD(operator ())
        	return operator const int *()[i];
        }
 
#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

       
        Vector2i::operator int* (){
        	SCREEN_DECL_METHOD(operator int*)
        	return &x;
        }
        
        Vector2i::operator const int* () const{
        	SCREEN_DECL_METHOD(operator const int*)
        	return &x;
        }
        
        Vector2i operator *(int t, const Vector2i& v){
        	SCREEN_DECL_FUNCTION(operator *)
        	return v*t;
        }

	} // math namespace
} // screen namespace
