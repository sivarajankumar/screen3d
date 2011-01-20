/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2009 Ratouit Thomas                                    *
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

#include <screen/memory/BufferManager.h>
#include <screen/utils/Exception.h>
#include <screen/math/Other.h>
#include <malloc.h>

#define LOG_STACKS \
	SCREEN_LOG_DEBUG("stacks :") \
	for(int i=0; i<numberOfStack; i++){ \
		SCREEN_LOG_DEBUG("\tall  #" << i << " " << buffers[i].size()); \
		SCREEN_LOG_DEBUG("\tfree #" << i << " " << unlockedBuffers[i].size()); \
	}


namespace screen {
	namespace memory {
		SINGLETON_IMPL(UniqueSingleton,BufferManager)

		BufferManager::BufferManager(){
			SCREEN_DECL_CONSTRUCTOR(BufferManager)
			LOG_STACKS;
		}
		BufferManager::~BufferManager(){
			SCREEN_DECL_DESTRUCTOR(~BufferManager)
			LOG_STACKS;
		}

		int BufferManager::calculateStackNumber(unsigned int size){
			SCREEN_DECL_STATIC_METHOD(calculateStackNumber)
			unsigned int tmp = size;
			unsigned int ret = SCREEN_MEMORY_DEFAULT_MIN_SIZE;
			unsigned int number = 0;

			while (tmp > SCREEN_MEMORY_DEFAULT_MIN_SIZE){
			    tmp /= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
			    ret *= SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER;
				++number;
			}

			return ret >= size ? number : number+1;
		}

		unsigned int BufferManager::calculateSizeFromStack(int stackNumber){
			SCREEN_DECL_STATIC_METHOD(calculateSizeFromStack)
			return SCREEN_MEMORY_DEFAULT_MIN_SIZE*screen::math::power(SCREEN_MEMORY_DEFAULT_SIZE_MULTIPLIER,stackNumber);
		}

#define createBuffer(buffer,bufferSize) \
	void* buffer = ::malloc(bufferSize); \
	if(buffer==NULL){ \
		garbage(); \
		buffer = ::malloc(bufferSize); \
		if(buffer==NULL){ \
			std::stringstream ss; \
			ss << "Unable to allocate a buffer of size " << bufferSize; \
			throw screen::utils::Exception(ss.str()); \
		} \
	}
		

		BufferBase* BufferManager::getNewBufferBase(unsigned int size){
			SCREEN_DECL_METHOD(getNewBufferBase)
			LOG_STACKS;
			int i = calculateStackNumber(size);
			unsigned int bufferSize = calculateSizeFromStack(i);
			if(i>=numberOfStack) {
				//in case of asked buffer is larger than the maximum size of a buffer => new big buffer
				SCREEN_LOG_DEBUG("allocate big buffer of size " << size << " and effective size " << bufferSize);
				createBuffer(buffer,bufferSize);
				BufferBase bigBase(buffer, size);
				//Assert(buffer!=NULL);
				bigBuffers[buffer] = bigBase;
				//Assert(bigBuffers[buffer].getBuffer()==buffer);
				return &(bigBuffers[buffer]);
			} else if(unlockedBuffers[i].empty()){
				//if there aren't free buffers of the same size => new buffer
				SCREEN_LOG_DEBUG("allocate new buffer in stack " << i << " of size " << size << " and effective size " << bufferSize);
				createBuffer(newBuffer,bufferSize);
				buffers[i][newBuffer] = BufferBase(newBuffer, size);
				//Assert(buffers[i].top().getBuffer()!=NULL);
				return &(buffers[i][newBuffer]);
			} else {
				//if there are free buffers of the same size => reuse buffer
				SCREEN_LOG_DEBUG("reuse buffer in stack " << i << ", buffer size " << size << " and effective size " << bufferSize);
				BufferBase* base = unlockedBuffers[i].top();
				base->setSize(size);
				unlockedBuffers[i].pop();
				//Assert(base!=NULL);
				//Assert(base->getBuffer()!=NULL);
				return base;
			}
		}

#undef createBuffer
		
		void BufferManager::addToUnlocked(BufferBase* bufferBase){
			SCREEN_DECL_METHOD(addToUnlocked)
			LOG_STACKS;
			if(bufferBase->getSize()>SCREEN_MEMORY_DEFAULT_MAX_SIZE){
				//if it's big buffer => delete this
				SCREEN_LOG_DEBUG("delete big buffer");
				void* bigBuffer = bufferBase->getBuffer();
				//Assert(bigBuffer!=NULL);
				bigBuffers.erase(bigBuffer);
			} else {
				//if it isn't big buffer => add buffer to free stack
				int i = calculateStackNumber(bufferBase->getSize());
				SCREEN_LOG_DEBUG("unlock buffer by adding to free stack " << i);
				unlockedBuffers[i].push(bufferBase);
				bufferBase->setSize(0);
			}
		}
		
		BufferBase* BufferManager::replaceBufferBase(BufferBase* oldBufferBase, unsigned int newSize){
			SCREEN_DECL_METHOD(replaceBufferBase)
			if(oldBufferBase->getSize()>=newSize){
				//if the new buffer is smaller than the old, reuse the old
				SCREEN_LOG_DEBUG("no new buffer due to smaller input buffer size");
				return oldBufferBase;
			}
			int oldNumber = calculateStackNumber(oldBufferBase->getSize());
			int newNumber = calculateStackNumber(newSize);
			if(oldNumber==newNumber){
				//if the effective old buffer size is the new one, reuse the old buffer
				SCREEN_LOG_DEBUG("no new buffer due to equal effective buffer sizes");
				oldBufferBase->setSize(newSize);
				return oldBufferBase;
			} else {
				SCREEN_LOG_DEBUG("new buffer due to upper effective buffer size");
				//create a new buffer
				BufferBase* newBufferBase = getNewBufferBase(newSize);
				//copy old buffer into new
				::memcpy(newBufferBase->getBuffer(), oldBufferBase->getBuffer(), oldBufferBase->getSize());
				//free old buffer
				addToUnlocked(oldBufferBase);

				return newBufferBase;
			}
		}

		unsigned int BufferManager::garbage(){
			unsigned int totalFreeSize = 0;
			for(int i=0; i<numberOfStack; i++){
				while(!unlockedBuffers[i].empty()){
					BufferBase* bb = unlockedBuffers[i].top();
					void* buffer = bb->getBuffer();
					buffers[i].erase(buffer);
					unlockedBuffers[i].pop();
					totalFreeSize += calculateSizeFromStack(i);
				}
			}
			SCREEN_LOG_DEBUG("garbage => free " << totalFreeSize << " bytes")
			return totalFreeSize;
		}
	}
}
