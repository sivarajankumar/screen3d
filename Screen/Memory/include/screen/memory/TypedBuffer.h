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
 * \file screen/memory/TypedBuffer.h
 * \brief Screen memory typed buffer header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_TYPED_BUFFER_H
#define SCREEN_MEMORY_TYPED_BUFFER_H

#include <screen/memory/Buffer.h>
#include <screen/utils/Declaration.h>
#include <screen/memory/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all memory classes
	 */
	namespace memory {

		/**
		 * \brief Generic buffer implementation for Screen/Memory component
		 *
		 * It represents the minimalistic user interface to handle a buffer instance
		 * for a given type.
		 * It hides all explicit BufferBase instance handling and allocation
		 *
		 * \tparam T Content instance type
		 */
		template <class T>
		class TypedBuffer {
        	SCREEN_DECL_CLASS(screen::memory::TypedBuffer)
        public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T* const_pointer;
			typedef const T& const_reference;

			/**
			 * \brief Default constructor
			 */
			TypedBuffer(){
				SCREEN_DECL_CONSTRUCTOR(TypedBuffer)
			}

			/**
			 * \brief Copy contructor
			 *
			 * \param[in] iTypedBuffer Buffer instance to copy
			 */
			TypedBuffer(const TypedBuffer& iTypedBuffer)
				:_buffer(iTypedBuffer._buffer)
			{
				SCREEN_DECL_CONSTRUCTOR(TypedBuffer)
			}

			/**
			 * \brief Copy operator
			 *
			 * \param[in] iBuffer Buffer instance to copy
			 * \return copied buffer instance
			 */
			const TypedBuffer& operator= (const TypedBuffer& iTypedBuffer){
				SCREEN_DECL_METHOD(operator=)
				_buffer = iTypedBuffer._buffer;
				return *this;
			}

			/**
			 * \brief Destructor
			 *
			 * Release BufferBase instance
			 */
			virtual ~TypedBuffer(){
				SCREEN_DECL_DESTRUCTOR(~TypedBuffer)
			}

			/**
			 * \brief Copy an input buffer content into a memory buffer part
			 *
			 * It automatically handles BufferBase instance allocation and replacement
			 *
			 * \param[in] iPosition position into memory buffer to copy the input buffer
			 * \param[in] iBuffer Input buffer to copy
			 * \param[in] iSize Buffer size to copy
			 */
			void setAt(unsigned int iPosition,const T* iBuffer, unsigned int iSize){
				SCREEN_DECL_METHOD(setAt)
				_buffer.setAt(iPosition*sizeof(T),iBuffer,iSize*sizeof(T));
			}

			/**
			 * \brief Retrieve memory buffer pointer
			 *
			 * \param[in] iPosition position into memory buffer to retrieve
			 * \return Memory buffer pointer
			 */
			const T* getAt(unsigned int iPosition) const{
				SCREEN_DECL_METHOD(getAt)
				return static_cast<const T*>(_buffer.getAt(iPosition*sizeof(T)));
			}

			/**
			 * \brief Retrieve memory buffer pointer
			 *
			 * \param[in] iPosition position into memory buffer to retrieve
			 * \return Memory buffer pointer
			 */
			T* getAt(unsigned int iPosition){
				SCREEN_DECL_METHOD(getAt)
				return static_cast<T*>(_buffer.getAt(iPosition*sizeof(T)));
			}

			/**
			 * \brief Retrieve memory buffer size
			 *
			 * \return Memory buffer size
			 */
			unsigned int size() const{
				SCREEN_DECL_METHOD(size)
				return _buffer.size()/sizeof(T);
			}

			/**
			 * \brief Retrieve the effective memory buffer size
			 *
			 * It represents the size internal allocated size for a buffer,
			 * depending of the chosen policies.
			 * The effective size is always upper than the user-side size.
			 *
			 * \return Memory buffer size
			 */
			unsigned int effectiveSize() const{
				SCREEN_DECL_METHOD(effectiveSize)
				return _buffer.effectiveSize()/sizeof(T);
			}

			/**
			 * \brief Allocate a minimal size for the buffer
			 *
			 * Could be used if the user know the final size, or at least the minimal one.
			 * Could also be uses to manually set the buffer content without use setAt
			 * method.
			 *
			 * \param[in] iSize size to allocate
			 */
			void allocate(unsigned int iSize){
				SCREEN_DECL_METHOD(allocate);
				_buffer.allocate(iSize*sizeof(T));
			}

			/**
			 * \brief Release the BufferBase instance
			 *
			 * All buffer content is lost
			 */
			void unlock(){
				SCREEN_DECL_METHOD(unlock)
				_buffer.unlock();
			}
		private:
			Buffer _buffer; ///< internal buffer instance with no type
        };
    }
}

#endif
