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
 * \file screen/memory/Buffer.cpp
 * \brief Screen memory buffer source file
 * \author
 *
 */

#include <screen/memory/Buffer.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/Defaults.h>
#include <screen/utils/Exception.h>
#include <string.h>

namespace screen {
    namespace memory {
		Buffer::Buffer()
			:_bufferBase(NULL){
			SCREEN_DECL_CONSTRUCTOR(Buffer)
		}

		Buffer::Buffer(const Buffer& iBuffer)
			:_bufferBase(NULL){
			SCREEN_DECL_CONSTRUCTOR(Buffer)
			swap(iBuffer);
		}

		const Buffer& Buffer::operator= (const Buffer& iBuffer){
			SCREEN_DECL_METHOD(operator=)
			swap(iBuffer);
			return *this;
		}
		
		Buffer::~Buffer(){
			SCREEN_DECL_DESTRUCTOR(~Buffer)
			unlock();
		}

		void Buffer::setAt(unsigned int iPosition,const void* iBuffer, unsigned int iSize){
			SCREEN_DECL_METHOD(setAt)
			int aBufSize = iPosition+iSize;
			allocate(aBufSize);
            SCREEN_ASSERT(_bufferBase!=NULL);
            SCREEN_ASSERT(_bufferBase->getBuffer()!=NULL);
			::memcpy((char*)_bufferBase->getBuffer()+iPosition, iBuffer, iSize);
		}
		
		const void* Buffer::getAt(unsigned int iPosition) const{
			SCREEN_DECL_METHOD(getAt)
			if(_bufferBase != NULL){
                SCREEN_ASSERT(_bufferBase->getBuffer()!=NULL);
				return (char*)_bufferBase->getBuffer()+iPosition;
			}
			else{
				return NULL;
			}
		}

		void* Buffer::getAt(unsigned int iPosition){
			SCREEN_DECL_METHOD(getAt)
			if(_bufferBase != NULL){
                SCREEN_ASSERT(_bufferBase->getBuffer()!=NULL);
				return (char*)_bufferBase->getBuffer()+iPosition;
			}
			else{
				return NULL;
			}
		}

		
		unsigned int Buffer::size() const{
			SCREEN_DECL_METHOD(size)
			if(_bufferBase != NULL)
				return _bufferBase->getSize();
			else
				return 0;
		}

		unsigned int Buffer::effectiveSize() const{
			SCREEN_DECL_METHOD(effectiveSize)
			return BufferManager::Instance()->calculateSizeFromStack(
						BufferManager::Instance()->calculateStackNumber(size())
					);
		}

		void Buffer::allocate(unsigned int iSize){
			SCREEN_DECL_METHOD(allocate);
			if(!isLocked())
				_bufferBase = BufferManager::Instance()->getNewBufferBase(iSize);
			else
				_bufferBase = BufferManager::Instance()->replaceBufferBase(_bufferBase, iSize);
		}

		void Buffer::unlock(){
			SCREEN_DECL_METHOD(unlock)
			if(isLocked()){
				BufferManager::Instance()->addToUnlocked(_bufferBase);
				_bufferBase = NULL;
			}
		}
		
		bool Buffer::isLocked() const{
			SCREEN_DECL_METHOD(isLocked)
			return _bufferBase != NULL;
		}

		void Buffer::swap(const Buffer& iBuffer){
			SCREEN_DECL_METHOD(swap)
			Buffer& aModifBuffer = const_cast<Buffer&>(iBuffer);
			std::swap(_bufferBase, aModifBuffer._bufferBase);
		}
    }
}
