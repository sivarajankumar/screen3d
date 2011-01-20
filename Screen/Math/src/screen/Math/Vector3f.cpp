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

#include <Screen/Math/Vector3f.h>

namespace Screen {
	namespace Math {
		
		Vector3f::Vector3f(float x, float y, float z)
			:x(x),y(y),z(z){
			SCREEN_DECL_CONSTRUCTOR(Vector3f)
		}
			
		Vector3f::~Vector3f(){
			SCREEN_DECL_DESTRUCTOR(~Vector3f)
		}
		
		void Vector3f::set(float x, float y, float z){
			SCREEN_DECL_METHOD(set)
			this->x = x;
			this->y = y;
			this->z = z;
		}
		
		void Vector3f::get(float& x, float& y, float& z) const{
			SCREEN_DECL_METHOD(get)
			x = this->x;
			y = this->y;
			z = this->z;
		}
		
		void Vector3f::setX(float x){
			SCREEN_DECL_METHOD(setX)
			this->x = x;
		}
		
		void Vector3f::setY(float y){
			SCREEN_DECL_METHOD(setY)
			this->y = y;
		}
		
		void Vector3f::setZ(float y){
			SCREEN_DECL_METHOD(setZ)
			this->z = z;
		}
		
		float Vector3f::getX() const{
			SCREEN_DECL_METHOD(getX)
			return x;
		}
		
		float Vector3f::getY() const{
			SCREEN_DECL_METHOD(getY)
			return y;
		}
		
		float Vector3f::getZ() const{
			SCREEN_DECL_METHOD(getZ)
			return z;
		}
		
		Vector3f Vector3f::operator +() const{
			SCREEN_DECL_METHOD(operator +)
			return *this;
		}
		
		Vector3f Vector3f::operator -() const{
			SCREEN_DECL_METHOD(operator -)
			return Vector3f(-x,-y,-z);
		}
	    
		Vector3f Vector3f::operator +(const Vector3f& v) const{
			SCREEN_DECL_METHOD(operator +)
			return Vector3f(x+v.x, y+v.y, z+v.z);
		}
		Vector3f Vector3f::operator -(const Vector3f& v) const{
			SCREEN_DECL_METHOD(operator -)
			return Vector3f(x-v.x, y-v.y, z-v.z);
		}
		
		Vector3f Vector3f::operator *(float t) const{
			SCREEN_DECL_METHOD(operator *)
			return Vector3f(x*t, y*t, z*t);
		}
		
		Vector3f Vector3f::operator /(float t) const{
			SCREEN_DECL_METHOD(operator /)
			return Vector3f(x/t, y/t, z/t);
		}
	    
	    const Vector3f& Vector3f::operator +=(const Vector3f& v){
	    	SCREEN_DECL_METHOD(operator +=)
	    	x+=v.x;
	    	y+=v.y;
	    	z+=v.z;
	    	return *this;
	    }
	    const Vector3f& Vector3f::operator -=(const Vector3f& v){
	    	SCREEN_DECL_METHOD(operator -=)
	    	x-=v.x;
	    	y-=v.y;
	    	z-=v.z;
	    	return *this;
	    }
	    const Vector3f& Vector3f::operator *=(float t){
	    	SCREEN_DECL_METHOD(operator *=)
	    	x*=t;
	    	y*=t;
	    	z*=t;
	    	return *this;
	    }
	    const Vector3f& Vector3f::operator /=(float t){
	    	SCREEN_DECL_METHOD(operator /=)
	    	x/=t;
	    	y/=t;
	    	z/=t;
	    	return *this;
	    }
	    
		bool Vector3f::operator == (const Vector3f& v) const{
			SCREEN_DECL_METHOD(operator ==)
			return (fabs(x - v.x) < std::numeric_limits<float>::epsilon() &&
					fabs(y - v.y) < std::numeric_limits<float>::epsilon() &&
					fabs(z - v.z) < std::numeric_limits<float>::epsilon());
		}
		bool Vector3f::operator != (const Vector3f& v) const{
			SCREEN_DECL_METHOD(operator !=)
			return !(*this == v);
		}
	    
	    float& Vector3f::operator ()(unsigned int i){
	    	SCREEN_DECL_METHOD(operator ())
	    	return operator float*()[i];
	    }

#pragma warning( push )
#pragma warning( disable : 4717 )//disable a Visual Studio warning

	    const float& Vector3f::operator()(unsigned int i) const{
	    	SCREEN_DECL_METHOD(operator ())
	    	return operator const float*()[i];
	    }

#pragma warning( pop ) 

	    Vector3f::operator float* (){
	    	SCREEN_DECL_METHOD(operator float*)
	    	return &x;
	    }
	    
	    Vector3f::operator const float* () const{
	    	SCREEN_DECL_METHOD(operator const float*)
	    	return &x;
	    }
	    
	    Vector3f operator *(float t, const Vector3f& v){
	    	SCREEN_DECL_FUNCTION(operator *)
	    	return v*t;
	    }
        
	    float Vector3f::length() const{
	    	return std::sqrt(lengthSquare());
	    }
        float Vector3f::lengthSquare() const{
        	return x*x + y*y + z*z;
        }
        float Vector3f::dot(const Vector3f& v) const{
        	return x*v.x + y*v.y + z*v.z;
        }
        
        Vector3f Vector3f::cross(const Vector3f& v) const{
        	return Vector3f(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
        }
        
        void Vector3f::normalize(){
        	float len = length();
        	if(len > std::numeric_limits<float>::epsilon()){
        		x/=len;
        		y/=len;
        		z/=len;
        	}
        }
        
//        void Vector3f::print() const{
//        	SCREEN_LOG_INFO("Vector3f")
//			SCREEN_LOG_INFO(" | " << x << " | " << y << " | " << z << " | ")
//		}
	}
}
