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

#ifndef SCREEN_MATRIX4X4F_H
#define SCREEN_MATRIX4X4F_H

#include <Screen/Math/Vector3f.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Math/Export.h>

namespace Screen {
	namespace Math {
        class SCREEN_MATH_EXPORT Matrix4x4f{
        	SCREEN_DECL_CLASS(Screen::Math::Matrix4x4f)
        public :
        	Matrix4x4f(	float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
        				float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
        				float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
        				float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f);

            void identity();
            Matrix4x4f transpose() const;
            
            void setTranslation(float x, float y, float z);
            void setScaling(float x, float y, float z);
            void setRotationX(float angle);
            void setRotationY(float angle);
            void setRotationZ(float angle);
            
            //view matrix
            void lookAt(const Vector3f& eye, const Vector3f& lookAt, const Vector3f& up = Vector3f(0,1,0) );
            
            //orthocenter matrix
            void orthoOffCenter(float left, float top, float right, float bottom);
            
            //perspective projection matrix
            void perspectiveFOV(float fov, float ratio, float near, float far);
            
            Matrix4x4f getInverseRotationTranslation() const;

            Matrix4x4f operator +() const;
            Matrix4x4f operator -() const;
            
            Matrix4x4f operator +(const Matrix4x4f& m) const;
            Matrix4x4f operator -(const Matrix4x4f& m) const;
            Matrix4x4f operator *(const Matrix4x4f& m) const;
            Matrix4x4f operator *(float t) const;
            Matrix4x4f operator /(float t) const;
            
            const Matrix4x4f& operator +=(const Matrix4x4f& m);
            const Matrix4x4f& operator -=(const Matrix4x4f& m);
            const Matrix4x4f& operator *=(const Matrix4x4f& m);
            const Matrix4x4f& operator *=(float t);
            const Matrix4x4f& operator /=(float t);
            
            bool operator ==(const Matrix4x4f& m) const;
            bool operator !=(const Matrix4x4f& m) const;
            
            float& operator ()(unsigned int i, unsigned int j);
            const float& operator()(unsigned int i, unsigned int j) const;
            
            operator float* ();
            operator const float* () const;
        private:
            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;
        };
        
        Matrix4x4f operator *(float t, const Matrix4x4f& m);
	}
}

#endif
