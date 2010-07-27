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

#ifndef MATRIX_H
#define MATRIX_H

#include <Screen/Utils/Reference_restriction.h>
#include <Screen/Utils/Declaration.h>

namespace Screen {
    namespace Math {

        using Screen::Utils::ConstReference;
        using Screen::Utils::Reference;

        /*!  \class StaticArray
          *  \brief Structure for generic unidimensional arrays.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template<class T, unsigned int I>
        struct StaticArray {
            T object[I];
            typedef T ElementType;
            enum {
                Size=I
            };
        };

        /*!  \class Matrix
         *   \brief Compile-Time Sized Matrix
         *  \author Ratouit Thomas
         *  \version 1.0
         *  \date 2008
         */
        template <class T, unsigned int I, unsigned int J>
        class Matrix {
        	SCREEN_DECL_CLASS(Screen::Math::Matrix)
        public:
            inline Matrix() {
            	SCREEN_DECL_CONSTRUCTOR(Matrix)
            }
            inline virtual ~Matrix() {
            	SCREEN_DECL_DESTRUCTOR(~Matrix)
            }

            inline typename Reference<T>::Type get(unsigned int i, unsigned int j) const {
            	SCREEN_DECL_METHOD(get)
                return matrixArray.object[i*J+j];
            }

            inline void set(unsigned int i, unsigned int j, typename ConstReference<T>::Type value) {
            	SCREEN_DECL_METHOD(set)
                matrixArray.object[i*J+j]=value;
            }

            inline Matrix<T,I,J> operator+ (const Matrix<T,I,J>& m2) const { //binary +
            	SCREEN_DECL_METHOD(operator+)
                Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = this->matrixArray.object[i] + m2.matrixArray.object[i];
                }
                return result;
            }

            inline Matrix<T,I,J> operator- (const Matrix<T,I,J>& m2) const { //binary -
            	SCREEN_DECL_METHOD(operator-)
                Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = this->matrixArray.object[i] - m2.matrixArray.object[i];
                }
                return result;
            }

            inline Matrix<T,I,J> operator- () const { //unary -
            	SCREEN_DECL_METHOD(operator-)
            	Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = - this->matrixArray.object[i];
                }
                return result;
            }

            template <unsigned int K>
            inline Matrix<T,I,K> operator* (const Matrix<T,J,K>& m2) const { //binary *
            	SCREEN_DECL_METHOD(operator*)
            	Matrix<T,I,K> result;
                for(register unsigned int i=0; i<I; i++)
                    for(register unsigned int k=0; k<K; k++) {
                        result.set(i,k,this->get(i,0) * m2.get(0,k))
                        ;
                        for(register unsigned int j=1; j<J; j++)
                            result.set(i,k,result.get(i,k) + this->get(i,j) * m2.get(j,k))
                            ;
                    }
                return result;
            }

            inline Matrix<T,J,I> transpose() const {
            	SCREEN_DECL_METHOD(transpose)
                Matrix<T,J,I> result;
                for(register unsigned int i=0; i<I; i++)
                    for(register unsigned int j=0; j<J; j++)
                        result.set(j,i,this->get(i,j))
                        ;
                return result;
            }

            inline const Matrix<T,I,J>& operator= (const Matrix<T,I,J>& m2) {
            	SCREEN_DECL_METHOD(operator=)
                for(register unsigned int i=0; i<I*J; i++) {
                    this->matrixArray.object[i] = m2.matrixArray.object[i];
                }
                return (*this);
            }

            template <unsigned int I1, unsigned int J1, unsigned int I2, unsigned int J2>
            inline Matrix<T,I2-I1+1,J2-J1+1> subMatrix() {
            	SCREEN_DECL_METHOD(subMatrix)
                Matrix<T,I2-I1+1,J2-J1+1> result;
                for(register unsigned int i=I1; i<=I2; i++)
                    for(register unsigned int j=J1; j<=J2; j++)
                        result.set(i-I1,j-J1,this->get(i,j));
                return result;
            }

            enum{
                nbLine = I,
                nbColumn = J
            };
        protected:
            StaticArray<T,I*J> matrixArray;
        };
        
        /*!  \class Matrix
         *   \brief Compile-Time Sized Matrix
         *  \author Ratouit Thomas
         *  \version 1.0
         *  \date 2008
         */
        template <class T, unsigned int I>
        class Vector {
        	SCREEN_DECL_CLASS(Screen::Math::Vector)
        public:
            inline Vector() {
            	SCREEN_DECL_CONSTRUCTOR(Vector)
            }
            inline virtual ~Vector() {
            	SCREEN_DECL_DESTRUCTOR(~Vector)
            }

            inline typename Reference<T>::Type get(unsigned int i) const {
            	SCREEN_DECL_METHOD(get)
                return vectorArray.object[i];
            }

            inline void set(unsigned int i, typename ConstReference<T>::Type value) {
            	SCREEN_DECL_METHOD(set)
            	vectorArray.object[i]=value;
            }

            inline Vector<T,I> operator+ (const Vector<T,I>& m2) const { //binary +
            	SCREEN_DECL_METHOD(operator+)
            	Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = this->vectorArray.object[i] + m2.vectorArray.object[i];
                }
                return result;
            }

            inline Vector<T,I> operator- (const Vector<T,I>& m2) const { //binary -
            	SCREEN_DECL_METHOD(operator-)
                Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = this->vectorArray.object[i] - m2.vectorArray.object[i];
                }
                return result;
            }

            inline Vector<T,I> operator- () const { //unary -
            	SCREEN_DECL_METHOD(operator-)
            	Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = - this->vectorArray.object[i];
                }
                return result;
            }

            inline const Vector<T,I>& operator= (const Vector<T,I>& m2) {
            	SCREEN_DECL_METHOD(operator=)
                for(register unsigned int i=0; i< StaticArray<T,I>::Size; i++) {
                    this->vectorArray.object[i] = m2.vectorArray.object[i];
                }
                return (*this);
            }

            enum{
                nbLine = I,
                nbColumn = 1
            };
        protected:
            StaticArray<T,I> vectorArray;
        };
    }
}

#endif
