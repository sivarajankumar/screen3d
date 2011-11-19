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
 * \file screen/memory/policies/BasicStackHandler.h
 * \brief Buffer stack handler header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_POLICIES_BASIC_STACK_HANDLER_H
#define SCREEN_MEMORY_POLICIES_BASIC_STACK_HANDLER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferBase.h>
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
		 * Namespace for all policies classes
		 */
		namespace policies{
			class BufferPolicyHandlerInterface;

			/**
			 * \brief Class to basically handle buffer stacks.
			 *
			 * Handle buffer stacks and buffer allocations into those stacks
			 * The main role of this class is to hidden stack handling from other processes
			 *
			 * \tparam StackSelectorPolicy Policy to compute number of stacks and buffer size of each stack
			 */
			template<class StackSelectorPolicy>
			class SCREEN_MEMORY_EXPORT BasicStackHandler{
				SCREEN_DECL_CLASS(screen::memory::policies::BasicStackHandler);
			public:

				/**
				 * \brief Constructor with common buffer policy interface.
				 *
				 * \param[in,out] ioInterface Common buffer policy interface
				 */
				BasicStackHandler(BufferPolicyHandlerInterface* ioInterface);

				/**
				 * \brief Destructor. Completely erase buffer stack content.
				 */
				~BasicStackHandler();

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
				 * and the old buffer is put into unlocked stack
				 *
				 * \param[in] iOldBufferBase buffer to copy
				 * \param[in] iNewSize size of the new buffer
				 * \return Returns the new buffer
				 */
				BufferBase* replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize);

				/**
				 * \brief Clear unlocked stack and delete all unlocked buffers
				 *
				 * \return Returns total buffer size that has been deleted
				 */
				unsigned int garbage();

				enum {
					MIN_BUFFER_SIZE = StackSelectorPolicy::MIN_BUFFER_SIZE, ///< minimum buffer size
					MAX_BUFFER_SIZE = StackSelectorPolicy::MAX_BUFFER_SIZE, ///< maximum buffer size
					NUMBER_OF_STACKS = StackSelectorPolicy::NUMBER_OF_STACKS ///< number of stacks in stack handler
				};
			private:
				BufferPolicyHandlerInterface* _interface; ///< common buffer policy interface

				std::map<void*,BufferBase> _buffers[NUMBER_OF_STACKS]; ///< buffer stacks
				std::stack<BufferBase*> _unlockedBuffers[NUMBER_OF_STACKS]; ///< unlocked buffer stacks
				std::map<void*,BufferBase> _bigBuffers; ///< big buffer (upper than maximum buffer size) stack
			};
		}
	}
}

#endif
