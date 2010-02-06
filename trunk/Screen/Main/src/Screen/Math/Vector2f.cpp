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

#include <Screen/Math/Vector2f.h>

namespace Screen {
	namespace Math {
		Vector2f::Vector2f(float x, float y)
			:x(x),y(y){
			SCREEN_DECL_CONSTRUCTOR(Vector2f)
		}
			
		Vector2f::~Vector2f(){
			SCREEN_DECL_DESTRUCTOR(~Vector2f)
		}
		
		void Vector2f::set(float x, float y){
			SCREEN_DECL_METHOD(set)
			this->x = x;
			this->y = y;
		}
		
		void Vector2f::get(float& x, float& y) const{
			SCREEN_DECL_METHOD(get)
			x = this->x;
			y = this->y;
		}
		
		void Vector2f::setX(float x){
			SCREEN_DECL_METHOD(setX)
			this->x = x;
		}
		
		void Vector2f::setY(float y){
			SCREEN_DECL_METHOD(setY)
			this->y = y;
		}
		
		float Vector2f::getX() const{
			SCREEN_DECL_METHOD(getX)
			return x;
		}
		
		float Vector2f::getY() const{
			SCREEN_DECL_METHOD(getY)
			return y;
		}
		
		Vector2f Vector2f::operator +() const{
			SCREEN_DECL_METHOD(operator +)
			return *this;
		}
		
		Vector2f Vector2f::operator -() const{
			SCREEN_DECL_METHOD(operator -)
			return Vector2f(-x,-y);
		}
        
		Vector2f Vector2f::operator +(const Vector2f& v) const{
			SCREEN_DECL_METHOD(operator +)
			return Vector2f(x+v.x, y+v.y);
		}
		Vector2f Vector2f::operator -(const Vector2f& v) const{
			SCREEN_DECL_METHOD(operator -)
			return Vector2f(x-v.x, y-v.y);
		}
		
		Vector2f Vector2f::operator *(float t) const{
			SCREEN_DECL_METHOD(operator *)
			return Vector2f(x*t, y*t);
		}
		
		Vector2f Vector2f::operator /(float t) const{
			SCREEN_DECL_METHOD(operator /)
			return Vector2f(x/t, y/t);
		}
        
        const Vector2f& Vector2f::operator +=(const Vector2f& v){
        	SCREEN_DECL_METHOD(operator +=)
        	x+=v.x;
        	y+=v.y;
        	return *this;
        }
        const Vector2f& Vector2f::operator -=(const Vector2f& v){
        	SCREEN_DECL_METHOD(operator -=)
        	x-=v.x;
        	y-=v.y;
        	return *this;
        }
        const Vector2f& Vector2f::operator *=(float t){
        	SCREEN_DECL_METHOD(operator *=)
        	x*=t;
        	y*=t;
        	return *this;
        }
        const Vector2f& Vector2f::operator /=(float t){
        	SCREEN_DECL_METHOD(operator /=)
        	x/=t;
        	y/=t;
        	return *this;
        }
        
		bool Vector2f::operator == (const Vector2f& v) const{
			SCREEN_DECL_METHOD(operator ==)
			return (fabs(x - v.x) < std::numeric_limits<float>::epsilon() &&
					fabs(y - v.y) < std::numeric_limits<float>::epsilon());
		}
		bool Vector2f::operator != (const Vector2f& v) const{
			SCREEN_DECL_METHOD(operator !=)
			return !(*this == v);
		}
        
        float& Vector2f::operator ()(unsigned int i){
        	SCREEN_DECL_METHOD(operator ())
        	return operator float*()[i];
        }

#pragma warning( push )
#pragma warning( disable : 4717 )//disable a Visual Studio warning

        const float& Vector2f::operator()(unsigned int i) const{
        	SCREEN_DECL_METHOD(operator ())
        	return operator()(i);
        }

#pragma warning( pop ) 

        Vector2f::operator float* (){
        	SCREEN_DECL_METHOD(operator float*)
        	return &x;
        }
        
        Vector2f::operator const float* () const{
        	SCREEN_DECL_METHOD(operator const float*)
        	return &x;
        }
        
        Vector2f operator *(float t, const Vector2f& v){
        	SCREEN_DECL_FUNCTION(operator *)
        	return v*t;
        }
	}
}
