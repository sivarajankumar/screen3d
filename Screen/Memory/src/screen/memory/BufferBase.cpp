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

#include <screen/memory/BufferBase.h>
#include <malloc.h>

namespace screen {
    namespace memory {
		BufferBase::BufferBase()
			:bufferPtr(NULL),size(0){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
		}
        BufferBase::BufferBase(void* bufferPtr, unsigned int size)
			:bufferPtr(bufferPtr),size(size){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
		}

		BufferBase::BufferBase(const BufferBase& bufferBase)
			:bufferPtr(bufferBase.bufferPtr),size(bufferBase.size){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
			const_cast<BufferBase&>(bufferBase).bufferPtr = NULL;
		}
	
		const BufferBase& BufferBase::operator=(const BufferBase& bufferBase){
			SCREEN_DECL_METHOD(operator=)
			BufferBase& base = const_cast<BufferBase&>(bufferBase);
			std::swap(bufferPtr,base.bufferPtr);
			std::swap(size,base.size);
		}
		
        BufferBase::~BufferBase(){
			SCREEN_DECL_DESTRUCTOR(~BufferBase)
			if(bufferPtr!=NULL)
				::free(bufferPtr);
		}

		const void* BufferBase::getBuffer() const{
			SCREEN_DECL_METHOD(getBuffer)
			return bufferPtr;
		}
		void* BufferBase::getBuffer(){
			SCREEN_DECL_METHOD(getBuffer)
			return bufferPtr;
		}

		unsigned int BufferBase::getSize() const{
			SCREEN_DECL_METHOD(getSize)
			return size;
		}
		void BufferBase::setSize(unsigned int size){
			SCREEN_DECL_METHOD(setSize)
			this->size = size;
		}
	}
}
