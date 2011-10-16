/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2011 Ratouit Thomas                                    *
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
 * \file Matrix.h
 * \brief Matrix header file for screen::math
 * \author Ratouit Thomas
 * \version 1.0
 * \date 2008
 *
 * Matrix and Vector definition and operations on Matrices and Vectors
 */


#ifndef MATRIX_H
#define MATRIX_H

#include <screen/utils/Reference_restriction.h>
#include <screen/utils/Declaration.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all math classes
	 */
    namespace math {

        using screen::utils::ConstReference;
        using screen::utils::Reference;

		/**
		 * \brief Structure for generic unidimensional arrays.
		 * \tparam T class of the elements stored in the array
		 * \tparam I size of the array
		 */
        template<class T, unsigned int I>
        struct StaticArray {
            T object[I];
            typedef T ElementType;
            enum {
				Size=I ///< size of the array
            };
		};

		/**
		 * \brief Compile-Time Sized Matrix
		 * \tparam T class of the elements stored in the matrix
		 * \tparam I number of lines in the matrix
		 * \tparam J number of columns in the matrix
         */
        template <class T, unsigned int I, unsigned int J>
        class Matrix {

        	SCREEN_DECL_CLASS(screen::math::Matrix)

        public:

			/**
			 * \brief Contructor
			 */
            inline Matrix() {
            	SCREEN_DECL_CONSTRUCTOR(Matrix)
            }

			/**
			 * \brief Destructor
			 */
            inline virtual ~Matrix() {
            	SCREEN_DECL_DESTRUCTOR(~Matrix)
            }

			/**
			 * \brief Getter
			 *
			 * Get the data at line i, column j from the matrix
			 *
			 * \param[in] i line index
			 * \param[in] j column index
			 * \return Returns the data at line i, column j
			 */
            inline typename Reference<T>::Type get(unsigned int i, unsigned int j) const {
            	SCREEN_DECL_METHOD(get)
                return matrixArray.object[i*J+j];
            }

			/**
			 * \brief Setter
			 *
			 * Set the data at line i, column j to the matrix
			 *
			 * \param[in] i line index
			 * \param[in] j column index
			 * \param[in] value data to add in the matrix
			 */
            inline void set(unsigned int i, unsigned int j, typename ConstReference<T>::Type value) {
            	SCREEN_DECL_METHOD(set)
                matrixArray.object[i*J+j]=value;
            }

			/**
			 * \brief binary + operator
			 *
			 * Add two matrices
			 *
			 * \param[in] m2 matrix to add
			 * \return Returns the sum of the two matrices
			 */
			inline Matrix<T,I,J> operator+ (const Matrix<T,I,J>& m2) const {
            	SCREEN_DECL_METHOD(operator+)
                Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = this->matrixArray.object[i] + m2.matrixArray.object[i];
                }
                return result;
            }

			/**
			 * \brief binary - operator
			 *
			 * Substract a matrix to another
			 *
			 * \param[in] m2 matrix to substract
			 * \return Returns the substraction of the two matrices
			 */
			inline Matrix<T,I,J> operator- (const Matrix<T,I,J>& m2) const {
            	SCREEN_DECL_METHOD(operator-)
                Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = this->matrixArray.object[i] - m2.matrixArray.object[i];
                }
                return result;
            }

			/**
			 * \brief unary - operator
			 *
			 * negate a matrix (i.e. negate all values in the matrix)
			 *
			 * \return Returns the negated matrix
			 */
			inline Matrix<T,I,J> operator- () const {
            	SCREEN_DECL_METHOD(operator-)
            	Matrix<T,I,J> result;
                for(register int i=0; i < StaticArray<T,I*J>::Size; i++) {
                    result.matrixArray.object[i] = - this->matrixArray.object[i];
                }
                return result;
            }

			/**
			 * \brief binary * operator
			 *
			 * Multiplication of two matrices with the same number of columns
			 *
			 * \param[in] m2 matrix use for multiplication
			 * \tparam K column size
			 * \return Returns the result of the multiplication of two matrices
			 */
            template <unsigned int K>
			inline Matrix<T,I,K> operator* (const Matrix<T,J,K>& m2) const {
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

			/**
			 * \brief Matrix transposition
			 *
			 * \return Returns the transposition of the matrix
			 */
            inline Matrix<T,J,I> transpose() const {
            	SCREEN_DECL_METHOD(transpose)
                Matrix<T,J,I> result;
                for(register unsigned int i=0; i<I; i++)
                    for(register unsigned int j=0; j<J; j++)
                        result.set(j,i,this->get(i,j))
                        ;
                return result;
            }

			/**
			 * \brief Copy operator
			 * \return Returns the copied matrix
			 */
            inline const Matrix<T,I,J>& operator= (const Matrix<T,I,J>& m2) {
            	SCREEN_DECL_METHOD(operator=)
                for(register unsigned int i=0; i<I*J; i++) {
                    this->matrixArray.object[i] = m2.matrixArray.object[i];
                }
                return (*this);
            }

			/**
			 * \brief Get a sub matrix of a matrix
			 *
			 * \tparam I1 first line of the sub-matrix in the current matrix
			 * \tparam J1 first column of the sub-matrix in the current matrix
			 * \tparam I2 last line of the sub-matrix in the current matrix
			 * \tparam J2 last column of the sub-matrix in the current matrix
			 * \return Returns the sub matrix
			 */
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
				nbLine = I,		///< Number of lines in the matrix
				nbColumn = J	///< Number of columns in the matrix
            };

        protected:

			StaticArray<T,I*J> matrixArray; ///< Internal array representing the matrix

		}; // matrix class
        

		/**
		 * \brief Compile-Time Sized vector
		 * \tparam T class of the elements stored in the vector
		 * \tparam I size of the vector
		 * \sa Matrix , Vector2i
         */
        template <class T, unsigned int I>
        class Vector {

        	SCREEN_DECL_CLASS(screen::math::Vector)

        public:

			/**
			 * \brief Contructor
			 */
            inline Vector() {
            	SCREEN_DECL_CONSTRUCTOR(Vector)
            }

			/**
			 * \brief Destructor
			 */
            inline virtual ~Vector() {
            	SCREEN_DECL_DESTRUCTOR(~Vector)
            }

			/**
			 * \brief Getter
			 *
			 * Get the data at position i
			 *
			 * \param[in] i index
			 * \return Returns the data at line position i
			 */
            inline typename Reference<T>::Type get(unsigned int i) const {
            	SCREEN_DECL_METHOD(get)
                return vectorArray.object[i];
            }

			/**
			 * \brief Setter
			 *
			 * Set the data at position i
			 *
			 * \param[in] i index
			 * \param[in] value data to set
			 */
            inline void set(unsigned int i, typename ConstReference<T>::Type value) {
            	SCREEN_DECL_METHOD(set)
            	vectorArray.object[i]=value;
            }

			/**
			 * \brief binary + operator
			 *
			 * Add two vectors
			 *
			 * \param[in] m2 vector to add
			 * \return Returns the sum of the two vectors
			 */
			inline Vector<T,I> operator+ (const Vector<T,I>& m2) const {
            	SCREEN_DECL_METHOD(operator+)
            	Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = this->vectorArray.object[i] + m2.vectorArray.object[i];
                }
                return result;
            }

			/**
			 * \brief binary - operator
			 *
			 * Substract a matrix to another
			 *
			 * \param[in] m2 vector to substract
			 * \return Returns the substraction of the two vectors
			 */
			inline Vector<T,I> operator- (const Vector<T,I>& m2) const {
            	SCREEN_DECL_METHOD(operator-)
                Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = this->vectorArray.object[i] - m2.vectorArray.object[i];
                }
                return result;
            }

			/**
			 * \brief unary - operator
			 *
			 * negate a vector (i.e. negate all values in the vector)
			 *
			 * \return Returns the negated vector
			 */
			inline Vector<T,I> operator- () const {
            	SCREEN_DECL_METHOD(operator-)
            	Vector<T,I> result;
                for(register int i=0; i < StaticArray<T,I>::Size; i++) {
                    result.vectorArray.object[i] = - this->vectorArray.object[i];
                }
                return result;
            }

			/**
			 * \brief Copy operator
			 * \return Returns the copied vector
			 */
            inline const Vector<T,I>& operator= (const Vector<T,I>& m2) {
            	SCREEN_DECL_METHOD(operator=)
                for(register unsigned int i=0; i< StaticArray<T,I>::Size; i++) {
                    this->vectorArray.object[i] = m2.vectorArray.object[i];
                }
                return (*this);
            }

            enum{
				nbLine = I,		///< Number of lines in the vector (i.e. size of the vector)
				nbColumn = 1	///< Number of columns in the vector (1)
            };
        protected:

			StaticArray<T,I> vectorArray;	///< Internal array of representing vector

		}; // Vector class

	} // math namespace
} // screen namespace

#endif // MATRIX_H
