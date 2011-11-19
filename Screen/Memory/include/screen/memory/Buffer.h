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
 * \file screen/memory/Buffer.h
 * \brief Screen memory buffer header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_BUFFER_H
#define SCREEN_MEMORY_BUFFER_H

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
		class BufferBase;
		
		/**
		 * \brief Basic buffer implementation for Screen/Memory component
		 *
		 * It represents the minimalistic user interface to handle a buffer instance.
		 * It hides all explicit BufferBase instance handling and allocation
		 * Be careful : This implementation uses void* to handle buffer content.
		 * If you want to use a real type inferface, prefer TypedBuffer.
		 *
		 */
		class SCREEN_MEMORY_EXPORT Buffer {
        	SCREEN_DECL_CLASS(screen::memory::Buffer)
        public:
			typedef void* pointer;
			typedef const void* const_pointer;

			/**
			 * \brief Default constructor
			 */
			Buffer();

			/**
			 * \brief Copy contructor
			 *
			 * \param[in] iBuffer Buffer instance to copy
			 */
			Buffer(const Buffer& iBuffer);

			/**
			 * \brief Copy operator
			 *
			 * \param[in] iBuffer Buffer instance to copy
			 * \return copied buffer instance
			 */
			const Buffer& operator= (const Buffer& iBuffer);

			/**
			 * \brief Destructor
			 *
			 * Release BufferBase instance
			 */
            virtual ~Buffer();

			/**
			 * \brief Copy an input buffer content into a memory buffer part
			 *
			 * It automatically handles BufferBase instance allocation and replacement
			 *
			 * \param[in] iPosition position into memory buffer to copy the input buffer
			 * \param[in] iBuffer Input buffer to copy
			 * \param[in] iSize Buffer size to copy
			 */
			void setAt(unsigned int iPosition,const void* iBuffer, unsigned int iSize);

			/**
			 * \brief Retrieve memory buffer pointer
			 *
			 * \param[in] iPosition position into memory buffer to retrieve
			 * \return Memory buffer pointer
			 */
			const void* getAt(unsigned int iPosition) const;

			/**
			 * \brief Retrieve memory buffer pointer
			 *
			 * \param[in] iPosition position into memory buffer to retrieve
			 * \return Memory buffer pointer
			 */
			void* getAt(unsigned int iPosition);

			/**
			 * \brief Retrieve memory buffer size
			 *
			 * \return Memory buffer size
			 */
			unsigned int size() const;

			/**
			 * \brief Retrieve the effective memory buffer size
			 *
			 * It represents the size internal allocated size for a buffer,
			 * depending of the chosen policies.
			 * The effective size is always upper than the user-side size.
			 *
			 * \return Memory buffer size
			 */
			unsigned int effectiveSize() const;

			/**
			 * \brief Allocate a minimal size for the buffer
			 *
			 * Could be used if the user know the final size, or at least the minimal one.
			 * Could also be uses to manually set the buffer content without use setAt
			 * method.
			 *
			 * \param[in] iSize size to allocate
			 */
			void allocate(unsigned int iSize);
				
			/**
			 * \brief Release the BufferBase instance
			 *
			 * All buffer content is lost
			 */
			void unlock();
		protected:

			/**
			 * \brief Method to know if a BufferBase instance is attached to this Buffer instance
			 */
			bool isLocked() const;

			/**
			 * \brief Swap two buffer contents
			 *
			 * \param[in] iBuffer second buffer to swap
			 */
			void swap(const Buffer& iBuffer);

			BufferBase* _bufferBase; ///< BufferBase instance attached to this Buffer
        };
    }
}

#endif
