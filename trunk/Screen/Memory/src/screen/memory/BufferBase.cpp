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
 * \file screen/memory/BufferBase.cpp
 * \brief Screen memory buffer base source file
 * \author
 *
 */

#include <screen/memory/BufferBase.h>
#include <malloc.h>

namespace screen {
    namespace memory {
		BufferBase::BufferBase()
			:_bufferPtr(NULL),_size(0){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
		}
		BufferBase::BufferBase(void* iBufferPtr, unsigned int iSize)
			:_bufferPtr(iBufferPtr),_size(iSize){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
		}

		BufferBase::BufferBase(const BufferBase& iBufferBase)
			:_bufferPtr(iBufferBase._bufferPtr),_size(iBufferBase._size){
			SCREEN_DECL_CONSTRUCTOR(BufferBase)
			const_cast<BufferBase&>(iBufferBase)._bufferPtr = NULL;
		}
	
		const BufferBase& BufferBase::operator=(const BufferBase& iBufferBase){
			SCREEN_DECL_METHOD(operator=)
			BufferBase& aBase = const_cast<BufferBase&>(iBufferBase);
			std::swap(_bufferPtr,aBase._bufferPtr);
			std::swap(_size,aBase._size);
			return *this;
		}
		
        BufferBase::~BufferBase(){
			SCREEN_DECL_DESTRUCTOR(~BufferBase)
			if(_bufferPtr!=NULL)
				::free(_bufferPtr);
		}

		const void* BufferBase::getBuffer() const{
			SCREEN_DECL_METHOD(getBuffer)
			return _bufferPtr;
		}
		void* BufferBase::getBuffer(){
			SCREEN_DECL_METHOD(getBuffer)
			return _bufferPtr;
		}

		unsigned int BufferBase::getSize() const{
			SCREEN_DECL_METHOD(getSize)
			return _size;
		}
		void BufferBase::setSize(unsigned int iSize){
			SCREEN_DECL_METHOD(setSize)
			_size = iSize;
		}
	}
}
