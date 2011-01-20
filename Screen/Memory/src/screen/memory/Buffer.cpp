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

#include <screen/memory/Buffer.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/Defaults.h>
#include <screen/utils/Exception.h>
#include <string.h>

namespace screen {
    namespace memory {
		Buffer::Buffer()
			:bufferBase(NULL){
			SCREEN_DECL_CONSTRUCTOR(Buffer)
		}

		Buffer::Buffer(const Buffer& buffer)
			:bufferBase(NULL){
			SCREEN_DECL_CONSTRUCTOR(Buffer)
			swap(buffer);
		}

		const Buffer& Buffer::operator= (const Buffer& buffer){
			SCREEN_DECL_METHOD(operator=)
			swap(buffer);
			return *this;
		}
		
		Buffer::~Buffer(){
			SCREEN_DECL_DESTRUCTOR(~Buffer)
			unlock();
		}

		void Buffer::setAt(unsigned int position,const void* buffer, unsigned int size){
			SCREEN_DECL_METHOD(setAt)
			int bufSize = position+size;
			if(!isLocked())
				bufferBase = BufferManager::instance()->getNewBufferBase(bufSize);
			else
				bufferBase = BufferManager::instance()->replaceBufferBase(bufferBase, bufSize);
			//Assert(bufferBase!=NULL);
			//Assert(bufferBase->getBuffer()!=NULL);
			::memcpy((char*)bufferBase->getBuffer()+position, buffer, size);
		}
		
		const void* Buffer::getAt(unsigned int position) const{
			SCREEN_DECL_METHOD(getAt)
			if(bufferBase != NULL){
				//Assert(bufferBase->getBuffer()!=NULL);
				return (char*)bufferBase->getBuffer()+position;
			}else
				return NULL;
		}
		
		unsigned int Buffer::size() const{
			SCREEN_DECL_METHOD(size)
			if(bufferBase != NULL)
				return bufferBase->getSize();
			else
				return 0;
		}

		unsigned int Buffer::effectiveSize() const{
			SCREEN_DECL_METHOD(effectiveSize)
			return BufferManager::calculateSizeFromStack(BufferManager::calculateStackNumber(size()));
		}

		void Buffer::unlock(){
			SCREEN_DECL_METHOD(unlock)
			if(isLocked()){
				BufferManager::instance()->addToUnlocked(bufferBase);
				bufferBase = NULL;
			}
		}
		
		bool Buffer::isLocked() const{
			SCREEN_DECL_METHOD(isLocked)
			return bufferBase != NULL;
		}

		void Buffer::swap(const Buffer& buffer){
			SCREEN_DECL_METHOD(swap)
			Buffer& modifBuffer = const_cast<Buffer&>(buffer);
			std::swap(bufferBase, modifBuffer.bufferBase);
		}
    }
}
