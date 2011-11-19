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
/**
 * \file screen/memory/Allocator.h
 * \brief Screen memory allocator header file
 * \author
 *
 */

#ifndef SCREEN_MEMORY_ALLOCATOR_H
#define SCREEN_MEMORY_ALLOCATOR_H

#include <screen/utils/Declaration.h>
#include <screen/memory/BufferBase.h>
#include <screen/memory/BufferManager.h>
#include <screen/memory/AllocBufferMap.h>
#include <new>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all memory classes
	 */
	namespace memory {

		/**
		 * \brief Screen/Memory implementation for standard allocator
		 *
		 * Specific implementation that could replace std::allocator
		 * This implementation is especially effective for std::vector
		 *
		 * \tparam T Allocated instance type
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
			
			/**
			 * \brief Default constructor.
			 */
			Allocator(){
				SCREEN_DECL_CONSTRUCTOR(Allocator)
			}
			
			/**
			 * \brief Destructor.
			 */
			~Allocator(){
				SCREEN_DECL_DESTRUCTOR(~Allocator)
			}
			
			/**
			 * \brief Copy constructor.
			 */
			Allocator(const Allocator&) throw() { }
			
			/**
			 * \brief Rebind copy constructor.
			 */
			template<typename U>
			Allocator(const Allocator<U>&) throw() { }

			/**
			 * \brief Method to transform a reference into a pointer.
			 *
			 * \param[in] iRef Input const reference
			 * \return Pointer of this reference
			 */
			pointer address(reference iRef) const { return &iRef; }

			/**
			 * \brief Method to transform a const reference into a const pointer.
			 *
			 * \param[in] iRef Input const reference
			 * \return Const pointer of this reference
			 */
			const_pointer address(const_reference iRef) const { return &iRef; }
			
			/**
			 * \brief Method to allocate memory from size.
			 *
			 * \param[in] iN Size to allocate
			 * \param[in] iP Optional pointer (not used)
			 * \return Pointer to allocated memory
			 */
			pointer allocate(size_type iN, const void* iP = NULL){
				SCREEN_DECL_METHOD(allocate)
				size_type aNeededSize = iN*sizeof(T);
				SCREEN_LOG_DEBUG("Size to allocate = " << aNeededSize);
				
				//allocate new buffer
				BufferBase* aBufferBase = BufferManager::instance()->getNewBufferBase(aNeededSize);
				
				//register buffer in order to retrieve it into deallocate
				void * aPtr = aBufferBase->_bufferPtr;
				AllocBufferMap::instance()->addBufferBase(aPtr,aBufferBase);
				
				SCREEN_LOG_DEBUG("Allocated address = " << aPtr);
				SCREEN_LOG_DEBUG("Allocated buffer base = " << aBufferBase);
				
				return static_cast<pointer>(aPtr);
			}
			
			/**
			 * \brief Method to deallocate memory
			 *
			 * \param[in] iP Pointer for memory to deallocate
			 * \param[in] iN Size to deallocate (not used)
			 * \return Pointer to allocated memory
			 */
			void deallocate( pointer iP, size_type iN ){
				SCREEN_DECL_METHOD(deallocate)
				BufferBase* aBufferBase = AllocBufferMap::instance()->popBufferBase(iP);

				SCREEN_LOG_DEBUG("Desallocated address = " << iP);
				SCREEN_LOG_DEBUG("Desallocated buffer base = " << aBufferBase);

				BufferManager::instance()->addToUnlocked(aBufferBase);
			}

			/**
			 * \brief Maximum allocation size
			 *
			 * \return Maximum size
			 */
			size_type max_size() const throw(){
				SCREEN_DECL_METHOD(max_size)
				  return std::numeric_limits<size_type>::max();
			}
			
			/**
			 * \brief Method to construct an instance in memory
			 *
			 * \param[in] iP Pointer for memory
			 * \param[in] iVal Reference for instance to copy
			 */
			void construct(pointer iP, const_reference iVal){
				SCREEN_DECL_METHOD(construct)
				new (iP) T(iVal);
			}
			
			/**
			 * \brief Method to destroy an instance in memory
			 *
			 * \param[in] iP Pointer for memory instance to destroy
			 */
			void destroy(pointer p){
				SCREEN_DECL_METHOD(destroy)
				p->~T();
			}
			
			/**
			 * \brief Rebind type (not used)
			 *
			 * \tparam U Type to rebind
			 */
			template<typename U>
			struct rebind{
				typedef screen::memory::Allocator<U> other;
			};
		};
		
		/**
		 * \brief Equal operator for Allocator (not used)
		 *
		 * \tparam T Allocated instance type
		 * \return Always true
		 */
		template<typename T>
		inline bool operator==(const screen::memory::Allocator<T>&, const screen::memory::Allocator<T>&){
			SCREEN_DECL_FUNCTION(operator==)
			return true;
		}
		
		/**
		 * \brief Not equal operator for Allocator (not used)
		 *
		 * \tparam T Allocated instance type
		 * \return Always false
		 */
		template<typename T>
		inline bool operator!=(const screen::memory::Allocator<T>&, const screen::memory::Allocator<T>&){
			SCREEN_DECL_FUNCTION(operator!=)
			return false;
		}
	}
}

#endif
