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
 * \file screen/memory/BufferBase.h
 * \brief Screen memory buffer base header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_BUFFER_BASE_H
#define SCREEN_MEMORY_BUFFER_BASE_H

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
		 * \brief Internal buffer handling class for Screen/Memory
		 *
		 * Handle the internal real buffer instance and size
		 *
		 */
		class SCREEN_MEMORY_EXPORT BufferBase {
        	SCREEN_DECL_CLASS(screen::memory::BufferBase)
        public:

			/**
			 * \brief Default constructor
			 */
			BufferBase();

			/**
			 * \brief Constructor with buffer and buffer size
			 *
			 * \param[in] iBufferPtr Buffer pointer
			 * \param[in] iSize Buffer size
			 */
			BufferBase(void* iBufferPtr, unsigned int iSize);

			/**
			 * \brief Copy constructor
			 *
			 * \param[in] iBufferBase BufferBase instance to copy
			 */
			BufferBase(const BufferBase& iBufferBase);

			/**
			 * \brief Copy operator
			 *
			 * \param[in] iBufferBase BufferBase instance to copy
			 * \return Copied BufferBase instance
			 */
			const BufferBase& operator=(const BufferBase& iBufferBase);

			/**
			 * \brief Destructor
			 */
			~BufferBase();

			/**
			 * \brief Buffer pointer getter
			 *
			 * \return Buffer pointer
			 */
			const void* getBuffer() const;

			/**
			 * \brief Buffer pointer accessor
			 *
			 * \return Buffer pointer
			 */
			void* getBuffer();

			/**
			 * \brief Buffer size getter
			 *
			 * \return Buffer size
			 */
			unsigned int getSize() const;

			/**
			 * \brief Buffer size setter
			 *
			 * \param[in] iSize Buffer size
			 */
			void setSize(unsigned int iSize);

		public:
			void* _bufferPtr; ///< Buffer pointer
			unsigned int _size; ///< Buffer size
        };
    }
}

#endif
