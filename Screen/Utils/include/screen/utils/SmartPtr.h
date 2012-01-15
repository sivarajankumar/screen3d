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

#ifndef SCREEN_SMART_PTR_H
#define SCREEN_SMART_PTR_H

#include <screen/utils/SmartPolicies.h>
#include <screen/utils/Exception.h>
#include <screen/utils/Declaration.h>

namespace screen{
	namespace utils{
		template <class T, template <class> class SmartPolicy = RefCountSmartPolicy >
		class SmartPtr : protected SmartPolicy<T>{
			SCREEN_DECL_CLASS(screen::utils::SmartPtr)
		public:
			SmartPtr()
				:SmartPolicy<T>(),instance(NULL){
				SCREEN_DECL_CONSTRUCTOR(SmartPtr)
			}
			
			SmartPtr(const SmartPtr<T, SmartPolicy>& copy)
				:SmartPolicy<T>(copy),instance(SmartPolicy<T>::clone(copy.instance)){
				SCREEN_DECL_CONSTRUCTOR(SmartPtr)
			}
			
			SmartPtr(T* instance)
				:SmartPolicy<T>(),instance(instance){
				SCREEN_DECL_CONSTRUCTOR(SmartPtr)
			}
			
			~SmartPtr(){
				SCREEN_DECL_DESTRUCTOR(~SmartPtr)
				release(instance);
			}
			
			const SmartPtr<T, SmartPolicy>& operator =(const SmartPtr<T, SmartPolicy>& ptr){
				SCREEN_DECL_METHOD(operator=)
				SmartPtr<T, SmartPolicy>(ptr).swap(*this);
				return *this;
			}
			
			const SmartPtr<T, SmartPolicy>& operator =(T* ptr){
				SCREEN_DECL_METHOD(operator=)
				if(instance != ptr)
					SmartPtr<T, SmartPolicy>(ptr).swap(*this);
				return *this;
			}
			
			T& operator * (){
				SCREEN_DECL_METHOD(operator*)
                SCREEN_ASSERT(instance!=NULL);
				return *instance;
			}
			
			T* operator ->(){
				SCREEN_DECL_METHOD(operator->)
                SCREEN_ASSERT(instance!=NULL);
				return instance;
			}
			
			const T& operator * () const{
				SCREEN_DECL_METHOD(operator*)
                SCREEN_ASSERT(instance!=NULL);
				return *instance;
			}
			
			const T* operator ->() const{
				SCREEN_DECL_METHOD(operator->)
                SCREEN_ASSERT(instance!=NULL);
				return instance;
			}
			
			T* get(){
				SCREEN_DECL_METHOD(get)
                SCREEN_ASSERT(instance!=NULL);
				return instance;
			}
			
			const T* get() const{
				SCREEN_DECL_METHOD(get)
                SCREEN_ASSERT(instance!=NULL);
				return instance;
			}
			
			operator T*(){
				SCREEN_DECL_METHOD(operator T*)
				return instance;
			}
			
			operator const T*() const{
				SCREEN_DECL_METHOD(operator const T*)
				return instance;
			}
			
			void swap(SmartPtr<T, SmartPolicy>& ptr){
				SCREEN_DECL_METHOD(swap)
				SmartPolicy<T>::swap(ptr);
			    std::swap(instance, ptr.instance);
			}
			
		private:
			T* instance;
		};
	}
}

#endif
