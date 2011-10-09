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

#ifndef SCREEN_LAZY_H
#define SCREEN_LAZY_H

#include <screen/utils/Thread.h>
#include <screen/utils/Policies.h>
#include <screen/utils/Declaration.h>

namespace screen {
	namespace utils {
		template <class T, class ThreadingModel = SingleThreadingModel>
		class Lazy {
			SCREEN_DECL_CLASS(screen::utils::Lazy)
		public:
		    Lazy()
				:computed(false){
		    	SCREEN_DECL_CONSTRUCTOR(Lazy)
		    }
		
		    virtual ~Lazy(){
		    	SCREEN_DECL_DESTRUCTOR(~Lazy)
		    }
		
		    T get() {
		    	SCREEN_DECL_METHOD(getValue)
		        if(!computed) {
		            typename ThreadingModel::ScopeLockType guard(mutex);
		            if(!computed) {
		                _value = value();
		                computed=true;
		            }
		        }
		        return _value;
		    }
		
		protected:
		    virtual T value() =0;
		private:
		    typename ThreadingModel::MutexType mutex;
		    T _value;
		    bool computed;
		};
		
		template <class T, class Funct, class ThreadingModel = SingleThreadingModel>
		class LazyWithFunctor {
			SCREEN_DECL_CLASS(screen::utils::LazyWithFunctor)
		public:
		    LazyWithFunctor(Funct* funct)
				:computed(false),funct(funct){
		    	SCREEN_DECL_CONSTRUCTOR(LazyWithFunctor)
		    }
		
		    ~LazyWithFunctor() {
		    	SCREEN_DECL_DESTRUCTOR(~LazyWithFunctor)
				if(funct!=NULL)
					delete funct;
		    }
		
		    T get() {
		    	SCREEN_DECL_METHOD(getValue)
		        if(!computed) {
		            typename ThreadingModel::ScopeLockType guard(mutex);
		            if(!computed) {
		                value = (*funct)();
		                computed=true;
		            }
		        }
		        return value;
		    }
		
		protected:
		private:
			bool computed;
			Funct* funct;
		    typename ThreadingModel::MutexType mutex;
		    T value;
		};
	}
}


#endif

