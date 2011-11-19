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
 * \file screen/memory/AllocBufferMap.h
 * \brief Screen memory allocation buffer map header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_ALLOC_BUFFER_MAP_H
#define SCREEN_MEMORY_ALLOC_BUFFER_MAP_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferBase.h>

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
		 * \brief Mapping between allocated memory by Allocator and BufferBase instance
		 *
		 * On some implementations, allocator are stateless.
		 * The purpose of this mapping is to keep the state
		 * thanks to the fact the allocated pointer remains.
		 *
		 */
		class SCREEN_MEMORY_EXPORT AllocBufferMap : public screen::utils::UniqueSingleton<AllocBufferMap>{
				SCREEN_DECL_CLASS(screen::memory::AllocBufferMap)
				SINGLETON_DECL(UniqueSingleton,AllocBufferMap)
			public:

				/**
				 * \brief Store the mapping between the pointer and the BufferBase.
				 *
				 * \param[in] iPtr Allocated pointer
				 * \param[in] iBuf Buffer base pointer
				 */
				void addBufferBase(const void* iPtr, BufferBase* iBuf);

				/**
				 * \brief Retrieve and pop from mapping the buffer base.
				 *
				 * \param[in] iPtr allocated pointer
				 * \return Buffer base pointer
				 */
				BufferBase* popBufferBase(const void* iPtr) const;
			private:
				std::map<const void*, BufferBase*> _bufferBaseMap; ///< allocated pointer / buffer base map
		};		
	}
}

#endif
