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

#ifndef SCREEN_MEMORY_TYPED_BUFFER_H
#define SCREEN_MEMORY_TYPED_BUFFER_H

#include <Screen/Memory/Buffer.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Memory/Export.h>

namespace Screen {
    namespace Memory {
		template <class T>		
		class TypedBuffer {
        	SCREEN_DECL_CLASS(Screen::Memory::TypedBuffer)
        public:
			TypedBuffer(){
				SCREEN_DECL_CONSTRUCTOR(TypedBuffer)
			}
			TypedBuffer(const TypedBuffer& typedBuffer)
				:buffer(typedBuffer.buffer)
			{
				SCREEN_DECL_CONSTRUCTOR(TypedBuffer)
			}
			const TypedBuffer& operator= (const TypedBuffer& typedBuffer){
				SCREEN_DECL_METHOD(operator=)
				buffer = typedBuffer.buffer;
				return *this;
			}
			virtual ~TypedBuffer(){
				SCREEN_DECL_DESTRUCTOR(~TypedBuffer)
			}

			void setAt(unsigned int position,const T* _buffer, unsigned int size){
				SCREEN_DECL_METHOD(setAt)
				buffer.setAt(position*sizeof(T),_buffer,size*sizeof(T));
			}
			const T* getAt(unsigned int position) const{
				SCREEN_DECL_METHOD(getAt)
				return static_cast<const T*>(buffer.getAt(position*sizeof(T)));
			}
			unsigned int size() const{
				SCREEN_DECL_METHOD(size)
				return buffer.size()/sizeof(T);
			}
			unsigned int effectiveSize() const{
				SCREEN_DECL_METHOD(effectiveSize)
				return buffer.effectiveSize()/sizeof(T);
			}
			void unlock(){
				SCREEN_DECL_METHOD(unlock)
				buffer.unlock();
			}
		private:
			Buffer buffer;
        };
    }
}

#endif
