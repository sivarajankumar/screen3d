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
 * \file screen/memory/policies/BasicStackHandler.cpp
 * \brief Buffer stack handler source file
 * \author
 *
 */

#include <screen/memory/policies/BasicStackHandler.h>
#include <screen/memory/policies/BasicStackSelector.h>
#include <screen/memory/policies/BufferPolicyHandler.h>
#include <screen/utils/Exception.h>

#ifdef USE_SCREEN_LOG_DEBUG
#define LOG_STACKS \
	SCREEN_LOG_DEBUG("stacks :") \
	for(int aIter=0; aIter<NUMBER_OF_STACKS; aIter++){ \
		SCREEN_LOG_DEBUG("\tall  #" << aIter << " " << _buffers[aIter].size()); \
		SCREEN_LOG_DEBUG("\tfree #" << aIter << " " << _unlockedBuffers[aIter].size()); \
	}
#else
#define LOG_STACKS
#endif

namespace screen{
	namespace memory{
		namespace policies{

			template<class StackSelectorPolicy>
			SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::BasicStackHandler(BufferPolicyHandlerInterface* ioInterface)
				:_interface(ioInterface){
				SCREEN_DECL_CONSTRUCTOR(BasicStackHandler);
				LOG_STACKS;
			}

			template<class StackSelectorPolicy>
			SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::~BasicStackHandler(){
				SCREEN_DECL_DESTRUCTOR(~BasicStackHandler);
				LOG_STACKS;
			}

			template<class StackSelectorPolicy>
			BufferBase* SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::getNewBufferBase(unsigned int iSize){
				SCREEN_DECL_METHOD(getNewBufferBase)
				LOG_STACKS;
				int aStackNumber = _interface->calculateStackNumber(iSize);
				unsigned int aBufferSize = _interface->calculateSizeFromStack(aStackNumber);
				if(aStackNumber>=NUMBER_OF_STACKS) {
					//in case of asked buffer is larger than the maximum size of a buffer => new big buffer
					SCREEN_LOG_DEBUG("allocate big buffer of size " << iSize << " and effective size " << aBufferSize);
					void* aBuffer = _interface->createBuffer(aBufferSize);

					BufferBase& aBigBase = _bigBuffers[aBuffer];
					aBigBase._bufferPtr = aBuffer;
					aBigBase._size = iSize;
					return &aBigBase;

				} else if(_unlockedBuffers[aStackNumber].empty()){
					//if there aren't free buffers of the same size => new buffer
					SCREEN_LOG_DEBUG("allocate new buffer in stack " << aStackNumber << " of size " << iSize << " and effective size " << aBufferSize);
					void* aNewBuffer = _interface->createBuffer(aBufferSize);

					BufferBase& aBase = _buffers[aStackNumber][aNewBuffer];
					aBase._bufferPtr = aNewBuffer;
					aBase._size = iSize;
					return &aBase;
				} else {
					//if there are free buffers of the same size => reuse buffer
					SCREEN_LOG_DEBUG("reuse buffer in stack " << aStackNumber << ", buffer size " << iSize << " and effective size " << aBufferSize);

					BufferBase* aBase = _unlockedBuffers[aStackNumber].top();
					aBase->_size = iSize;
					_unlockedBuffers[aStackNumber].pop();

					return aBase;
				}
			}

			template<class StackSelectorPolicy>
			void SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::addToUnlocked(BufferBase* iBufferBase){
				SCREEN_DECL_METHOD(addToUnlocked)
				LOG_STACKS;
				if(iBufferBase->_size > MAX_BUFFER_SIZE){
					//if it's big buffer => delete this
					SCREEN_LOG_DEBUG("delete big buffer");
					_bigBuffers.erase(iBufferBase->_bufferPtr);
				} else {
					//if it isn't big buffer => add buffer to free stack
					int aStackNumber = _interface->calculateStackNumber(iBufferBase->_size);
					SCREEN_LOG_DEBUG("unlock buffer by adding to free stack " << aStackNumber);
					_unlockedBuffers[aStackNumber].push(iBufferBase);
					iBufferBase->_size = 0;
				}
			}

			template<class StackSelectorPolicy>
			BufferBase* SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::replaceBufferBase(BufferBase* iOldBufferBase, unsigned int iNewSize){
				SCREEN_DECL_METHOD(replaceBufferBase)
				LOG_STACKS;
				if(iOldBufferBase->_size>=iNewSize){
					//if the new buffer is smaller than the old, reuse the old
					SCREEN_LOG_DEBUG("no new buffer due to smaller input buffer size");
					return iOldBufferBase;
				}
				int aOldNumber = _interface->calculateStackNumber(iOldBufferBase->_size);
				int aNewNumber = _interface->calculateStackNumber(iNewSize);
				if(aOldNumber==aNewNumber){
					//if the effective old buffer size is the new one, reuse the old buffer
					SCREEN_LOG_DEBUG("no new buffer due to equal effective buffer sizes");
					iOldBufferBase->_size = iNewSize;
					return iOldBufferBase;
				} else {
					SCREEN_LOG_DEBUG("new buffer due to upper effective buffer size");
					//create a new buffer
					BufferBase* aNewBufferBase = getNewBufferBase(iNewSize);
					//copy old buffer into new
					::memcpy(aNewBufferBase->_bufferPtr, iOldBufferBase->_bufferPtr, iOldBufferBase->_size);
					//free old buffer
					addToUnlocked(iOldBufferBase);

					return aNewBufferBase;
				}
			}

			template<class StackSelectorPolicy>
			unsigned int SCREEN_MEMORY_EXPORT BasicStackHandler<StackSelectorPolicy>::garbage(){
				SCREEN_DECL_METHOD(garbage);
				LOG_STACKS;
				unsigned int aTotalFreeSize = 0;
				for(int aStackNumber=0; aStackNumber<NUMBER_OF_STACKS; aStackNumber++){
					while(!_unlockedBuffers[aStackNumber].empty()){
						BufferBase* aBase = _unlockedBuffers[aStackNumber].top();
						void* aBuffer = aBase->_bufferPtr;
						_buffers[aStackNumber].erase(aBuffer);
						_unlockedBuffers[aStackNumber].pop();
						aTotalFreeSize += _interface->calculateSizeFromStack(aStackNumber);
					}
				}
				SCREEN_LOG_DEBUG("garbage => free " << aTotalFreeSize << " bytes")
				return aTotalFreeSize;
			}

			template SCREEN_MEMORY_EXPORT class BasicStackHandler<screen::memory::policies::BasicStackSelector>;
		}
	}
}
