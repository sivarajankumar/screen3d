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

#ifndef SCREEN_MEMORY_ALLOCATOR_H
#define SCREEN_MEMORY_ALLOCATOR_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/AllocBufferMap.h>
#include <new>

namespace screen{
	namespace memory{
		/*!  \class Allocator
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 8 avr. 11
		 */
		template<typename T>
		class Allocator {
			SCREEN_DECL_CLASS(screen::memory::Allocator)
		public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T* const_pointer;
			typedef const T& const_reference;
			typedef ::size_t size_type;
			typedef ::ptrdiff_t difference_type;
			
			Allocator(){
				SCREEN_DECL_CONSTRUCTOR(Allocator)
			}
			
			~Allocator(){
				SCREEN_DECL_DESTRUCTOR(~Allocator)
			}
			
			Allocator(const Allocator&) throw() { }
			
			template<typename U>
			Allocator(const Allocator<U>&) throw() { }

			pointer address(reference ref) const { return &ref; }
			const_pointer address(const_reference ref) const { return &ref; }
			
			pointer allocate(size_type n, const void* p = NULL){
				SCREEN_DECL_METHOD(allocate)
				size_type neededSize = n*sizeof(T);
				SCREEN_LOG_DEBUG("Size to allocate = " << neededSize);
				
				//allocate new buffer
				BufferBase* bufferBase = BufferManager::instance()->getNewBufferBase(neededSize);
				
				//register buffer in order to retrieve it into deallocate
				void * ptr = bufferBase->bufferPtr;
				AllocBufferMap::instance()->addBufferBase(ptr,bufferBase);
				
				SCREEN_LOG_DEBUG("Allocated address = " << ptr);
				SCREEN_LOG_DEBUG("Allocated buffer base = " << bufferBase);
				
				return static_cast<pointer>(ptr);
			}
			
			void deallocate( pointer p, size_type n ){
				SCREEN_DECL_METHOD(deallocate)
				BufferBase* bufferBase = AllocBufferMap::instance()->popBufferBase(p);

				SCREEN_LOG_DEBUG("Desallocated address = " << p);
				SCREEN_LOG_DEBUG("Desallocated buffer base = " << bufferBase);

				BufferManager::instance()->addToUnlocked(bufferBase);
			}
			
			size_type max_size() const throw(){
				SCREEN_DECL_METHOD(max_size)
				return std::numeric_limits<size_type>::max;
			}
			
			void construct(pointer p, const_reference val){
				SCREEN_DECL_METHOD(construct)
				new (p) T(val);
			}
			
			void destroy(pointer p){
				SCREEN_DECL_METHOD(destroy)
				p->~T();
			}
			
			template<typename U>
			struct rebind{
				typedef screen::memory::Allocator<U> other;
			};
		};
		
		template<typename T>
		inline bool operator==(const screen::memory::Allocator<T>&, const screen::memory::Allocator<T>&){
			SCREEN_DECL_FUNCTION(operator==)
			return true;
		}
		
		template<typename T>
		inline bool operator!=(const screen::memory::Allocator<T>&, const screen::memory::Allocator<T>&){
			SCREEN_DECL_FUNCTION(operator!=)
			return false;
		}
	}
}

#endif
