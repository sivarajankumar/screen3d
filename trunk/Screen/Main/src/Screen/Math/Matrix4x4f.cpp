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

#include <Screen/Math/Matrix4x4f.h>
#include <Screen/Utils/Exception.h>
#include <cmath>
#include <limits>

namespace Screen {
	namespace Math {
		Matrix4x4f::Matrix4x4f(	float m11, float m12, float m13, float m14,
		                        float m21, float m22, float m23, float m24,
		                        float m31, float m32, float m33, float m34,
		                        float m41, float m42, float m43, float m44)
						:	m11(m11), m12(m12), m13(m13), m14(m14),
							m21(m21), m22(m22), m23(m23), m24(m24),
							m31(m31), m32(m32), m33(m33), m34(m34),
							m41(m41), m42(m42), m43(m43), m44(m44){
			SCREEN_DECL_CONSTRUCTOR(Matrix4x4f)
		}
		
		void Matrix4x4f::identity(){
			SCREEN_DECL_METHOD(identity)
		    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
		    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
		    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
		    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
		}
		
		Matrix4x4f Matrix4x4f::transpose() const{
			SCREEN_DECL_METHOD(transpose)
			return Matrix4x4f(m11, m21, m31, m41,
		                    m12, m22, m32, m42,
		                    m13, m23, m33, m43,
		                    m14, m24, m34, m44);
		}
		
		void Matrix4x4f::setTranslation(float x, float y, float z){
			SCREEN_DECL_METHOD(setTranslation)
		    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
		    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
		    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
		    m41 = x;    m42 = y;    m43 = z; m44 = 1.0f;
		}
		
		void Matrix4x4f::setScaling(float x, float y, float z){
			SCREEN_DECL_METHOD(setScaling)
		    m11 = x;    m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
		    m21 = 0.0f; m22 = y;    m23 = 0.0f; m24 = 0.0f;
		    m31 = 0.0f; m32 = 0.0f; m33 = z;    m34 = 0.0f;
		    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
		}
		
		void Matrix4x4f::setRotationX(float angle){
			SCREEN_DECL_METHOD(setRotationX)
		    float tCos = std::cos(angle);
		    float tSin = std::sin(angle);
		
		    m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f; m14 = 0.0f;
		    m21 = 0.0f; m22 = tCos;  m23 = tSin; m24 = 0.0f;
		    m31 = 0.0f; m32 = -tSin; m33 = tCos; m34 = 0.0f;
		    m41 = 0.0f; m42 = 0.0f;  m43 = 0.0f; m44 = 1.0f;
		}
		
		void Matrix4x4f::setRotationY(float angle){
			SCREEN_DECL_METHOD(setRotationY)
		    float tCos = std::cos(angle);
		    float tSin = std::sin(angle);
		
		    m11 = tCos; m12 = 0.0f; m13 = -tSin; m14 = 0.0f;
		    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;  m24 = 0.0f;
		    m31 = tSin; m32 = 0.0f; m33 = tCos;  m34 = 0.0f;
		    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f;  m44 = 1.0f;
		}
		
		void Matrix4x4f::setRotationZ(float angle){
			SCREEN_DECL_METHOD(setRotationZ)
		    float tCos = cos(angle);
		    float tSin = sin(angle);
		
		    m11 = tCos;  m12 = tSin; m13 = 0.0f; m14 = 0.0f;
		    m21 = -tSin; m22 = tCos; m23 = 0.0f; m24 = 0.0f;
		    m31 = 0.0f;  m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
		    m41 = 0.0f;  m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
		}
		
		void Matrix4x4f::lookAt(const Vector3f& from, const Vector3f& to, const Vector3f& up){
			SCREEN_DECL_METHOD(lookAt)
			
			Assert((from - to).length() >= std::numeric_limits<float>::epsilon());
			
			Vector3f zAxis = from - to;
			zAxis.normalize();
			Vector3f yAxis = up - zAxis * zAxis.dot(up);
			yAxis.normalize();
			Vector3f xAxis = yAxis.cross(zAxis);
			
			m11 = xAxis.getX();     m12 = yAxis.getX();     m13 = zAxis.getX();     m14 = 0.0f;
			m21 = xAxis.getY();     m22 = yAxis.getY();     m23 = zAxis.getY();     m24 = 0.0f;
			m31 = xAxis.getZ();     m32 = yAxis.getZ();     m33 = zAxis.getZ();     m34 = 0.0f;
			m41 = -xAxis.dot(from); m42 = -yAxis.dot(from); m43 = -zAxis.dot(from); m44 = 1.0f;
		}
		
		void Matrix4x4f::orthoOffCenter(float left, float top, float right, float bottom){
			SCREEN_DECL_METHOD(orthoOffCenter)
//			m11 = 2 / (right - left); m12 = 0.0f;               m13 = 0.0f; m14 = (left + right) / (left - right);
//		    m21 = 0.0f;               m22 = 2 / (top - bottom); m23 = 0.0f; m24 = (bottom + top) / (bottom - top);
//		    m31 = 0.0f;               m32 = 0.0f;               m33 = 1.0f; m34 = 0.0f;
//		    m41 = 0.0f;               m42 = 0.0f;               m43 = 0.0f; m44 = 1.0f;
		}
		            
        void Matrix4x4f::perspectiveFOV(float fov, float ratio, float _near, float _far){
        	SCREEN_DECL_METHOD(perspectiveFOV)
        	
        	float yScale = 1.0f / std::tan(fov / 2);
    	    float xScale = yScale / ratio;
    	    float coeff  = _far / (_near - _far);

    	    m11 = xScale; m12 = 0.0f;   m13 = 0.0f;         m14 = 0.0f;
    	    m21 = 0.0f;   m22 = yScale; m23 = 0.0f;         m24 = 0.0f;
    	    m31 = 0.0f;   m32 = 0.0f;   m33 = coeff;        m34 = -1.0f;
    	    m41 = 0.0f;   m42 = 0.0f;   m43 = coeff*_near;  m44 = 0.0f;
        }
        
        Matrix4x4f Matrix4x4f::getInverseRotationTranslation() const{
        	return Matrix4x4f(
        		m11, m21, m31, 0,
        		m12, m22, m32, 0,
        		m13, m23, m33, 0,
        		-m11 * m41 - m12 * m42 - m13 * m43,
        		-m21 * m41 - m22 * m42 - m23 * m43,
        		-m31 * m41 - m32 * m42 - m33 * m43, 1);
        }
		
		Matrix4x4f Matrix4x4f::operator +() const{
			SCREEN_DECL_METHOD(operator+)
		    return *this;
		}
		
		Matrix4x4f Matrix4x4f::operator -() const{
			SCREEN_DECL_METHOD(operator-)
		    return Matrix4x4f(-m11, -m12, -m13, -m14,
		                    -m21, -m22, -m23, -m24,
		                    -m31, -m32, -m33, -m34,
		                    -m41, -m42, -m43, -m44);
		}
		
		Matrix4x4f Matrix4x4f::operator +(const Matrix4x4f& m) const{
			SCREEN_DECL_METHOD(operator+)
		    return Matrix4x4f(m11 + m.m11, m12 + m.m12, m13 + m.m13, m14 + m.m14,
		                    m21 + m.m21, m22 + m.m22, m23 + m.m23, m24 + m.m24,
		                    m31 + m.m31, m32 + m.m32, m33 + m.m33, m34 + m.m34,
		                    m41 + m.m41, m42 + m.m42, m43 + m.m43, m44 + m.m44);
		}
		
		Matrix4x4f Matrix4x4f::operator -(const Matrix4x4f& m) const{
			SCREEN_DECL_METHOD(operator-)
		    return Matrix4x4f(m11 - m.m11, m12 - m.m12, m13 - m.m13, m14 - m.m14,
		                    m21 - m.m21, m22 - m.m22, m23 - m.m23, m24 - m.m24,
		                    m31 - m.m31, m32 - m.m32, m33 - m.m33, m34 - m.m34,
		                    m41 - m.m41, m42 - m.m42, m43 - m.m43, m44 - m.m44);
		}
		
		Matrix4x4f Matrix4x4f::operator *(const Matrix4x4f& m) const{
			SCREEN_DECL_METHOD(operator*)
		    return Matrix4x4f(
		    		// first row
		    		m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41,
		    		m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42,
		    		m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43,
		    		m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44,
		    		// second row
		    		m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41,
		    		m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42,
		    		m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43,
		    		m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44,
		    		// third row
		    		m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41,
		    		m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42,
		    		m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43,
		    		m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44,
		    		// fourth row
		    		m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41,
		    		m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42,
		    		m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43,
		    		m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44);
		}
		
		Matrix4x4f Matrix4x4f::operator *(float t) const{
			SCREEN_DECL_METHOD(operator*)
		    return Matrix4x4f(m11 * t, m12 * t, m13 * t, m14 * t,
		                    m21 * t, m22 * t, m23 * t, m24 * t,
		                    m31 * t, m32 * t, m33 * t, m34 * t,
		                    m41 * t, m42 * t, m43 * t, m44 * t);
		
		}
		
		Matrix4x4f Matrix4x4f::operator /(float t) const{
			SCREEN_DECL_METHOD(operator/)
		    return Matrix4x4f(m11 / t, m12 / t, m13 / t, m14 / t,
		                    m21 / t, m22 / t, m23 / t, m24 / t,
		                    m31 / t, m32 / t, m33 / t, m34 / t,
		                    m41 / t, m42 / t, m43 / t, m44 / t);
		}
		
		const Matrix4x4f& Matrix4x4f::operator +=(const Matrix4x4f& m){
			SCREEN_DECL_METHOD(operator+=)
		    m11 += m.m11; m12 += m.m12; m13 += m.m13; m14 += m.m14;
		    m21 += m.m21; m22 += m.m22; m23 += m.m23; m24 += m.m24;
		    m31 += m.m31; m32 += m.m32; m33 += m.m33; m34 += m.m34;
		    m41 += m.m41; m42 += m.m42; m43 += m.m43; m44 += m.m44;
		
		    return *this;
		}
		
		const Matrix4x4f& Matrix4x4f::operator -=(const Matrix4x4f& m){
			SCREEN_DECL_METHOD(operator-=)
		    m11 -= m.m11; m12 -= m.m12; m13 -= m.m13; m14 -= m.m14;
		    m21 -= m.m21; m22 -= m.m22; m23 -= m.m23; m24 -= m.m24;
		    m31 -= m.m31; m32 -= m.m32; m33 -= m.m33; m34 -= m.m34;
		    m41 -= m.m41; m42 -= m.m42; m43 -= m.m43; m44 -= m.m44;
		
		    return *this;
		}
		
		const Matrix4x4f& Matrix4x4f::operator *=(float t){
			SCREEN_DECL_METHOD(operator*=)
		    m11 *= t; m12 *= t; m13 *= t; m14 *= t;
		    m21 *= t; m22 *= t; m23 *= t; m24 *= t;
		    m31 *= t; m32 *= t; m33 *= t; m34 *= t;
		    m41 *= t; m42 *= t; m43 *= t; m44 *= t;
		
		    return *this;
		}
		
		const Matrix4x4f& Matrix4x4f::operator /=(float t){
			SCREEN_DECL_METHOD(operator/=)
		    m11 /= t; m12 /= t; m13 /= t; m14 /= t;
		    m21 /= t; m22 /= t; m23 /= t; m24 /= t;
		    m31 /= t; m32 /= t; m33 /= t; m34 /= t;
		    m41 /= t; m42 /= t; m43 /= t; m44 /= t;
		
		    return *this;
		}
		
		const Matrix4x4f& Matrix4x4f::operator *=(const Matrix4x4f& m){
			SCREEN_DECL_METHOD(operator*=)
		    *this = *this * m;
		    return *this;
		}
		
		bool Matrix4x4f::operator ==(const Matrix4x4f& m) const{
			SCREEN_DECL_METHOD(operator==)
		    return ((fabs(m11 - m.m11) < std::numeric_limits<float>::epsilon()) && (fabs(m12 - m.m12) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m13 - m.m13) < std::numeric_limits<float>::epsilon()) && (fabs(m14 - m.m14) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m21 - m.m21) < std::numeric_limits<float>::epsilon()) && (fabs(m22 - m.m22) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m23 - m.m23) < std::numeric_limits<float>::epsilon()) && (fabs(m24 - m.m24) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m31 - m.m31) < std::numeric_limits<float>::epsilon()) && (fabs(m32 - m.m32) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m33 - m.m33) < std::numeric_limits<float>::epsilon()) && (fabs(m34 - m.m34) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m41 - m.m41) < std::numeric_limits<float>::epsilon()) && (fabs(m42 - m.m42) < std::numeric_limits<float>::epsilon()) &&
		            (fabs(m43 - m.m43) < std::numeric_limits<float>::epsilon()) && (fabs(m44 - m.m44) < std::numeric_limits<float>::epsilon()));
		}
		
		bool Matrix4x4f::operator !=(const Matrix4x4f& m) const{
			SCREEN_DECL_METHOD(operator!=)
		    return !(*this == m);
		}
		
		float& Matrix4x4f::operator ()(unsigned int i, unsigned int j){
			SCREEN_DECL_METHOD(operator())
		    return operator float*()[i + 4 * j];
		}
		
		const float& Matrix4x4f::operator ()(unsigned int i, unsigned int j) const{
			SCREEN_DECL_METHOD(operator())
			return operator ()(i, j);
		}
		
		Matrix4x4f::operator float* (){
			SCREEN_DECL_METHOD(operator float*)
		    return &m11;
		}
		
		Matrix4x4f::operator const float* () const{
			SCREEN_DECL_METHOD(operator const float*)
		    return &m11;
		}
		
//		void Matrix4x4f::print() const{
//			SCREEN_LOG_INFO("Matrix4x4f")
//			SCREEN_LOG_INFO(" | " << m11 << " | " << m12 << " | " << m13 << " | " << m14 << " | ")
//			SCREEN_LOG_INFO(" | " << m21 << " | " << m22 << " | " << m23 << " | " << m24 << " | ")
//			SCREEN_LOG_INFO(" | " << m31 << " | " << m32 << " | " << m33 << " | " << m34 << " | ")
//			SCREEN_LOG_INFO(" | " << m41 << " | " << m42 << " | " << m43 << " | " << m44 << " | ")
//		}
		
		Matrix4x4f operator *(float t, const Matrix4x4f& m){
			SCREEN_DECL_FUNCTION(operator*)
		    return m * t;
		}
	}
}
