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
 * \file screen/memory/BufferManager.h
 * \brief Screen memory buffer manager header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_BUFFER_MANAGER_H
#define SCREEN_MEMORY_BUFFER_MANAGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Declaration.h>
#include <screen/utils/SmartPtr.h>
#include <screen/memory/Export.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <stack>
#include <set>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all memory classes
	 */
	namespace memory {

		/**
		 * \brief Internal buffer manager class for Screen/Memory
		 *
		 * Handle the BufferBase instances and policies
		 *
		 */
		class SCREEN_MEMORY_EXPORT BufferManager : public screen::utils::UniqueSingleton<BufferManager>{
			SCREEN_DECL_CLASS(screen::memory::BufferManager);
			SINGLETON_DECL(UniqueSingleton,BufferManager);
			friend class Buffer;
		public:

			/**
			 * \brief Default constructor
			 */
			BufferManager();

			/**
			 * \brief Destructor
			 */
			~BufferManager();

			/**
			 * \brief Attach a policy handler to the buffer manager
			 *
			 * Warning : do not change policy handler after first buffer allocation
			 * All allocated buffers will be destroyed
			 * Buffer transfert between policies should be implemented
			 *
			 * \param[in,out] ioPolicy Policy handler
			 */
			void attachPolicyHandler(screen::memory::policies::BufferPolicyHandlerInterface* ioPolicy);

			/**
			 * \brief Allocate an new buffer with a given size.
			 *
			 * If there is an unused buffer into the stack, it will reuse this buffer
			 * instead of create a new one.
			 *
			 * \param[in] iSize Size of the buffer that need to be allocated
			 * \return Returns the new buffer
			 */
			BufferBase* getNewBufferBase(unsigned int iSize);

			/**
			 * \brief Unlock a buffer.
			 *
			 * This method is called when the user want to desallocate a buffer.
			 * The buffer will not be desallocated but put in unlocked buffer stack
			 * in order to be reused.
			 *
			 * \param[in] iBufferBase buffer to unlock
			 */
			void addToUnlocked(BufferBase* iBufferBase);

			/**
			 * \brief Copy the current buffer into a bigger buffer.
			 *
			 * This method is called when the user want to increase the size of the buffer.
			 * If the current buffer is big enough, we keep this one.
			 * In other cases, the current buffer is cloned into a new bigger one
			 * and the old buffer is put into unlocked stack.
			 *
			 * \param[in] iOldBufferBase buffer to copy
			 * \param[in] iNewSize size of the new buffer
			 * \return Returns the new buffer
			 */
			BufferBase* replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize);

			/**
			 * \brief Clear unlocked stack and delete all unlocked buffers.
			 *
			 * \return Returns total buffer size that has been deleted
			 */
			unsigned int garbage();

			/**
			 * \brief Compute stack number from expected buffer size.
			 *
			 * \param[in] iSize expected buffer size
			 * \return Returns stack number
			 */
			int calculateStackNumber(unsigned int iSize);

			/**
			 * \brief Compute real buffer size from stack number.
			 *
			 * \param[in] iStackNumber stack number
			 * \return Returns real buffer size
			 */
			unsigned int calculateSizeFromStack(int iStackNumber);

			screen::utils::SmartPtr<
				screen::memory::policies::BufferPolicyHandlerInterface,
				screen::utils::ScopePolicy> _policy; ///< policy handler pointer
		};
	}
}

#endif
