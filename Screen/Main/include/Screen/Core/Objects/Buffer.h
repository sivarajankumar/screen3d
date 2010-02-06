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

#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <Screen/Core/Objects/BufferBase.h>
#include <Screen/Core/Enums.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		namespace Objects {
		
			/** 
			 @brief
			 	This class defines a generic buffer for the render system
			 @remarks
			 	You can't use directly this class to send a buffer to the API.
			 	There are 2 sub-classes for this buffer class, VextexBuffer
			 	and IndexBuffer. Use those instead. 
			 */
		    template <class T>
		    class SCREEN_EXPORT Buffer{
		    	SCREEN_DECL_CLASS(Screen::Core::Object::Buffer)
		    public :
		        Buffer(BufferBase* buffer = NULL)
		        	:buffer(buffer){
		        	SCREEN_DECL_CONSTRUCTOR(Buffer)
		        }
		        
		        virtual ~Buffer(){
		        	SCREEN_DECL_DESTRUCTOR(~Buffer)
		        }

		        T* lock(unsigned long offset = 0, unsigned long size = 0, Screen::Core::LockFlag flags = Screen::Core::LOCK_READ_WRITE){
		        	SCREEN_DECL_METHOD(lock)
		        	return reinterpret_cast<T*>(buffer->lock(offset * sizeof(T), size * sizeof(T), flags));
		        }
		        
		        void unlock(){
		        	SCREEN_DECL_METHOD(unlock)
		        	buffer->unlock();
		        }
		        
		        void fill(const T* data, std::size_t count){
		        	SCREEN_DECL_METHOD(fill)
		        	Assert(data != NULL);
	
		        	T* myData = lock();
	        	    std::copy(data, data + count, myData);
	        	    unlock();
		        }
		        
		        void release(){
		        	SCREEN_DECL_METHOD(release)
		        	buffer = NULL;
		        }
		        
		        const BufferBase* getBuffer() const{
		        	SCREEN_DECL_METHOD(getBuffer)
		        	return buffer;
		        }
		        
		        unsigned long getCount() const{
		        	SCREEN_DECL_METHOD(getCount)
		        	return buffer->count;
		        }
		        
		        unsigned long getElementSize() const{
		        	SCREEN_DECL_METHOD(getElementSize)
		        	return sizeof(T);
		        }
	
		    private :
		        BufferBase::SmartPtr buffer;
		    };
		    
		    template <>
		    class SCREEN_EXPORT Buffer<void>{
		    	SCREEN_DECL_CLASS(Screen::Core::Object::Buffer)
		    public :
		        Buffer(BufferBase* buffer = NULL, unsigned int elementSize = 0)
		        	:buffer(buffer),elementSize(elementSize){
		        	SCREEN_DECL_CONSTRUCTOR(Buffer)
		        }
		        
		        virtual ~Buffer(){
		        	SCREEN_DECL_DESTRUCTOR(~Buffer)
		        }

		        void* lock(unsigned long offset = 0, unsigned long size = 0, Screen::Core::LockFlag flags = Screen::Core::LOCK_READ_WRITE){
		        	SCREEN_DECL_METHOD(lock)
		        	return buffer->lock(offset * elementSize, size * elementSize, flags);
		        }
		        
		        void unlock(){
		        	SCREEN_DECL_METHOD(unlock)
		        	buffer->unlock();
		        }
		        
		        void fill(const void* data, std::size_t count){
		        	SCREEN_DECL_METHOD(fill)
		        	Assert(data != NULL);
	
		        	void* myData = lock();
		        	memcpy(myData,data,count*elementSize);
	        	    //can't be used with void*
		        	//std::copy(data, data + count, myData);
	        	    unlock();
		        }
		        
		        void release(){
		        	SCREEN_DECL_METHOD(release)
		        	buffer = NULL;
		        }
		        
		        const BufferBase* getBuffer() const{
		        	SCREEN_DECL_METHOD(getBuffer)
		        	return buffer;
		        }
		        
		        unsigned long getCount() const{
		        	SCREEN_DECL_METHOD(getCount)
		        	return buffer->count;
		        }
		        
		        unsigned long getElementSize() const{
		        	SCREEN_DECL_METHOD(getElementSize)
		        	return elementSize;
		        }
	
		    private :
		        BufferBase::SmartPtr buffer;
		        unsigned int elementSize;
		    };
		}
	}
}

#endif
