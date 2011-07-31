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

#ifndef SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H
#define SCREEN_MEMORY_POLICIES_BUFFER_POLICY_HANDLER_H

#include <screen/utils/Declaration.h>
#include <screen/memory/policies/CreateWithMalloc.h>
#include <screen/memory/policies/BasicStackSelector.h>
#include <screen/memory/policies/BasicStackHandler.h>

namespace screen{
	namespace memory{
		namespace policies{
			class BufferPolicyHandlerInterface{
			public:
				virtual void* createBuffer(size_t bufferSize) = 0;
				virtual int calculateStackNumber(unsigned int size) = 0;
				virtual unsigned int calculateSizeFromStack(int stackNumber) = 0;
				virtual BufferBase* getNewBufferBase(unsigned int size) = 0;
				virtual void addToUnlocked(BufferBase* bufferBase) = 0;
				virtual BufferBase* replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize) = 0;
				virtual unsigned int garbage() = 0;
			};

			template <class CreationPolicy = screen::memory::policies::CreateWithMalloc,
					  class StackSelectorPolicy = screen::memory::policies::BasicStackSelector,
					  class StackHandlerPolicy = screen::memory::policies::BasicStackHandler<
						  screen::memory::policies::BasicStackSelector>
					 >
			class BufferPolicyHandler : public BufferPolicyHandlerInterface{
				SCREEN_DECL_CLASS(screen::memory::policies::BufferPolicyHandler);
			public:
				BufferPolicyHandler()
					:creationPolicy(this),stackSelector(this),stackHandler(this)
				{
					SCREEN_DECL_CONSTRUCTOR(BufferPolicyHandler);
				}

				~BufferPolicyHandler(){
					SCREEN_DECL_DESTRUCTOR(~BufferPolicyHandler);
				}

				void* createBuffer(size_t bufferSize){
					SCREEN_DECL_METHOD(createBuffer);
					return creationPolicy.createBuffer(bufferSize);
				}

				int calculateStackNumber(unsigned int size){
					SCREEN_DECL_METHOD(calculateStackNumber);
					return stackSelector.calculateStackNumber(size);
				}

				unsigned int calculateSizeFromStack(int stackNumber){
					SCREEN_DECL_METHOD(calculateSizeFromStack);
					return stackSelector.calculateSizeFromStack(stackNumber);
				}

				BufferBase* getNewBufferBase(unsigned int size){
					SCREEN_DECL_METHOD(getNewBufferBase);
					return stackHandler.getNewBufferBase(size);
				}

				void addToUnlocked(BufferBase* bufferBase){
					SCREEN_DECL_METHOD(addToUnlocked);
					stackHandler.addToUnlocked(bufferBase);
				}

				BufferBase* replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize){
					SCREEN_DECL_METHOD(replaceBufferBase);
					return stackHandler.replaceBufferBase(oldBufferBase,newSize);
				}

				unsigned int garbage(){
					SCREEN_DECL_METHOD(garbage);
					return stackHandler.garbage();
				}

			private:
				CreationPolicy creationPolicy;
				StackSelectorPolicy stackSelector;
				StackHandlerPolicy stackHandler;
			};
		}
	}
}

#endif
