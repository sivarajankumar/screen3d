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
 * \file screen/memory/policies/BasicPolicyHandler.h
 * \brief Buffer manager policy interface header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H
#define SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/policies/CreateWithMalloc.h>
#include <screen/memory/policies/BasicStackSelector.h>
#include <screen/memory/policies/BasicStackHandler.h>

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

			/**
			 * \brief Interface for buffer policies handler.
			 *
			 * This is interface is used by BufferManager to hide implementation details
			 * and allow different policies
			 *
			 */
			class BufferPolicyHandlerInterface{
			public:
				/**
				 * \brief Simply allocate memory to give it to BufferBase instance.
				 *
				 * \param[in] iBufferSize Size to allocate
				 * \return allocated memory pointer
				 */
				virtual void* createBuffer(size_t iBufferSize) = 0;

				/**
				 * \brief Compute stack number from expected buffer size.
				 *
				 * \param[in] iSize expected buffer size
				 * \return Returns stack number
				 */
				virtual int calculateStackNumber(unsigned int iSize) = 0;

				/**
				 * \brief Compute real buffer size from stack number.
				 *
				 * \param[in] iStackNumber stack number
				 * \return Returns real buffer size
				 */
				virtual unsigned int calculateSizeFromStack(int iStackNumber) = 0;

				/**
				 * \brief Allocate an new buffer with a given size.
				 *
				 * If there is an unused buffer into the stack, it will reuse this buffer
				 * instead of create a new one.
				 *
				 * \param[in] iSize Size of the buffer that need to be allocated
				 * \return Returns the new buffer
				 */
				virtual BufferBase* getNewBufferBase(unsigned int iSize) = 0;

				/**
				 * \brief Unlock a buffer.
				 *
				 * This method is called when the user want to desallocate a buffer.
				 * The buffer will not be desallocated but put in unlocked buffer stack
				 * in order to be reused.
				 *
				 * \param[in] iBufferBase buffer to unlock
				 */
				virtual void addToUnlocked(BufferBase* iBufferBase) = 0;

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
				virtual BufferBase* replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize) = 0;

				/**
				 * \brief Clear unlocked stack and delete all unlocked buffers.
				 *
				 * \return Returns total buffer size that has been deleted
				 */
				virtual unsigned int garbage() = 0;
			};

			/**
			 * \brief Default implementation for buffer policies.
			 *
			 * \tparam CreationPolicy Policy for memory allocation. By default, allocator with malloc.
			 * \tparam StackSelectorPolicy Policy to compute stack and buffer sizes
			 * \tparam StackHandlerPolicy Policicy to handle buffers and buffer stacks
			 */
			template <class CreationPolicy = screen::memory::policies::CreateWithMalloc,
					  class StackSelectorPolicy = screen::memory::policies::BasicStackSelector,
					  class StackHandlerPolicy = screen::memory::policies::BasicStackHandler<
						  screen::memory::policies::BasicStackSelector>
					 >
			class BufferPolicyHandler : public BufferPolicyHandlerInterface{
				SCREEN_DECL_CLASS(screen::memory::policies::BufferPolicyHandler);
			public:
				/**
				 * \brief Default constructor.
				 */
				BufferPolicyHandler()
					:_creationPolicy(this),_stackSelector(this),_stackHandler(this)
				{
					SCREEN_DECL_CONSTRUCTOR(BufferPolicyHandler);
				}

				/**
				 * \brief Destructor.
				 */
				~BufferPolicyHandler(){
					SCREEN_DECL_DESTRUCTOR(~BufferPolicyHandler);
				}

				/**
				 * \brief Simply allocate memory to give it to BufferBase instance.
				 *
				 * \param[in] iBufferSize Size to allocate
				 * \return allocated memory pointer
				 */
				void* createBuffer(size_t iBufferSize){
					SCREEN_DECL_METHOD(createBuffer);
					return _creationPolicy.createBuffer(iBufferSize);
				}

				/**
				 * \brief Compute stack number from expected buffer size.
				 *
				 * \param[in] iSize expected buffer size
				 * \return Returns stack number
				 */
				int calculateStackNumber(unsigned int iSize){
					SCREEN_DECL_METHOD(calculateStackNumber);
					return _stackSelector.calculateStackNumber(iSize);
				}

				/**
				 * \brief Compute real buffer size from stack number.
				 *
				 * \param[in] iStackNumber stack number
				 * \return Returns real buffer size
				 */
				unsigned int calculateSizeFromStack(int iStackNumber){
					SCREEN_DECL_METHOD(calculateSizeFromStack);
					return _stackSelector.calculateSizeFromStack(iStackNumber);
				}

				/**
				 * \brief Allocate an new buffer with a given size.
				 *
				 * If there is an unused buffer into the stack, it will reuse this buffer
				 * instead of create a new one.
				 *
				 * \param[in] iSize Size of the buffer that need to be allocated
				 * \return Returns the new buffer
				 */
				BufferBase* getNewBufferBase(unsigned int iSize){
					SCREEN_DECL_METHOD(getNewBufferBase);
					return _stackHandler.getNewBufferBase(iSize);
				}

				/**
				 * \brief Unlock a buffer.
				 *
				 * This method is called when the user want to desallocate a buffer.
				 * The buffer will not be desallocated but put in unlocked buffer stack
				 * in order to be reused.
				 *
				 * \param[in] iBufferBase buffer to unlock
				 */
				void addToUnlocked(BufferBase* iBufferBase){
					SCREEN_DECL_METHOD(addToUnlocked);
					_stackHandler.addToUnlocked(iBufferBase);
				}

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
				BufferBase* replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize){
					SCREEN_DECL_METHOD(replaceBufferBase);
					return _stackHandler.replaceBufferBase(iOldBufferBase,iNewSize);
				}

				/**
				 * \brief Clear unlocked stack and delete all unlocked buffers.
				 *
				 * \return Returns total buffer size that has been deleted
				 */
				unsigned int garbage(){
					SCREEN_DECL_METHOD(garbage);
					return _stackHandler.garbage();
				}

			private:
				CreationPolicy _creationPolicy; ///< memory allocation policy instance
				StackSelectorPolicy _stackSelector; ///< buffer and stack size computing policy instance
				StackHandlerPolicy _stackHandler; ///< buffer and stack handling policy instance
			};
		}
	}
}

#endif
