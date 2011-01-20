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

#ifndef SCREEN_SINGLETON_H
#define SCREEN_SINGLETON_H

#include <screen/utils/Policies.h>
#include <screen/utils/Thread.h>
#include <screen/utils/Export.h>
#include <screen/utils/SingletonLazyInstance.h>

namespace screen {
    namespace utils {

        /*!  \class SingletonModel
          *  \brief most generic singleton model.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  for multithreading, this singleton is not optimised for undestroyable singleton.\n
          *  in order to optimise in this case, use WeakSingletonModel
          */
        template <
        class T,
        template <class> class CreationPolicy,
        class ThreadingModel,
        class LifeTimePolicy >
        class SingletonModel {
        public:
            static T* instance();
            static void destroy();
        protected:
            SingletonModel() {}
            virtual ~SingletonModel() {}
        private:
            static LifeTimePolicy lifeTime;
            static typename ThreadingModel::MutexType mutex;
        };
        
        /*!  \class WeakSingletonModel
          *  \brief generic singleton model for multithread, unique and undestroyable singleton.
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <
        class T,
        template <class> class CreationPolicy,
        class ThreadingModel
        >
        class WeakSingletonModel {
        public:
            static T* instance();
        protected:
            WeakSingletonModel() {}
            virtual ~WeakSingletonModel() {}
        private:
            static typename ThreadingModel::MutexType mutex;
            static T* instancePtr;
        };
        
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    LifeTimePolicy SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::lifeTime;
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    typename ThreadingModel::MutexType SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::mutex;
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    T* SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::instance() {
			if(T::_policy_instance_ptr==NULL) {
				typename ThreadingModel::ScopeLockType guard(mutex);
    			if(T::_policy_instance_ptr==NULL) {
    				T::_policy_instance_ptr = CreationPolicy<T>::Create();
    				lifeTime.Instanciated();
    			}
			}
	        lifeTime.InstanceUsed();
	        return T::_policy_instance_ptr;
	    }
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    void SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::destroy() {
	        if(lifeTime.IsAuthorisedDeletion()) {
				typename ThreadingModel::ScopeLockType guard(mutex);
	        	if(lifeTime.IsAuthorisedDeletion()) {
	            	CreationPolicy<T>::Delete(T::_policy_instance_ptr);
	        	}
			}
			lifeTime.Deleted();
	    }

        template <class T, template <class> class CreationPolicy, class ThreadingModel>
        typename ThreadingModel::MutexType WeakSingletonModel<T, CreationPolicy, ThreadingModel>::mutex;

        template <class T, template <class> class CreationPolicy, class ThreadingModel>
        T* WeakSingletonModel<T, CreationPolicy, ThreadingModel>::instance() {
            if(T::_policy_instance_ptr==NULL) {
                typename ThreadingModel::ScopeLockType guard(mutex);
                if(T::_policy_instance_ptr==NULL) {
                	T::_policy_instance_ptr = CreationPolicy<T>::Create();
                }
            }
            return T::_policy_instance_ptr;
        }
	    
        /* Singleton Types*/

	    template <class T>
        class UniqueSingleton
                    : public WeakSingletonModel <
                    T,
					CreationWithLazy,
                    SingleThreadingModel> {
        protected:
            UniqueSingleton() {}
        }
        ;

        template <class T>
        class ThreadSafeUniqueSingleton
                    : public WeakSingletonModel <
                    T,
					CreationWithLazy,
                    MultipleThreadingModel>
        {}
        ;

        template <class T>
        class PhoenixSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    SingleThreadingModel,
                    DestroyableInstanceLifeTime >
    	{}
        ;

        template <class T>
        class ThreadSafePhoenixSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    MultipleThreadingModel,
                    DestroyableInstanceLifeTime >
        {}
        ;

        template <class T>
        class RefCountSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    SingleThreadingModel,
                    ReferenceCountLifeTime >
        {}
        ;

        template <class T>
        class ThreadRefCountSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    MultipleThreadingModel,
                    ReferenceCountLifeTime >
        {}
        ;
        
//        template <class T>
//	    class SharedSingleton
//	                : public WeakSingletonModel <
//	                T,
//	                CreationWithSharedMemory,
//	                MultipleThreadingModel >{
//        protected:
//        	SharedSingleton(){}
//        	~SharedSingleton(){}
//        };
    }
}

#define SINGLETON_DECL(singletonType,T) \
	SINGLETON_DECL_##singletonType(T)
	
#define SINGLETON_IMPL(singletonType,T) SINGLETON_IMPL_##singletonType(T)

//singleton macros

/*
#define SINGLETON_DECL_UniqueSingleton(T) \
		friend class screen::utils::WeakSingletonModel <T, \
						screen::utils::CreationWithStatic, \
						screen::utils::SingleThreadingModel>; \
		SINGLETON_DECL_CreationWithStatic(T)

#define SINGLETON_IMPL_UniqueSingleton(T) \
		SINGLETON_IMPL_CreationWithStatic(T)
*/
// under Linux, we can never predict the relative execution order of static initializers,
// so we use explicit lazy instanciation for unique singletons
#	define SINGLETON_DECL_UniqueSingleton(T) \
		friend class screen::utils::WeakSingletonModel <T, \
						screen::utils::CreationWithLazy, \
						screen::utils::SingleThreadingModel>; \
		SINGLETON_DECL_CreationWithLazy(T)

#	define SINGLETON_IMPL_UniqueSingleton(T) \
		SINGLETON_IMPL_CreationWithLazy(T)
//#endif

//policies macros

#define SINGLETON_DECL_CreationWithStatic(T) \
	friend class screen::utils::CreationWithStatic<T>; \
	static T _policy_instance; \
	static T* _policy_instance_ptr;

#define SINGLETON_IMPL_CreationWithStatic(T) \
	T T::_policy_instance; \
	T* T::_policy_instance_ptr = NULL;

#define SINGLETON_DECL_CreationWithLazy(T) \
	friend class screen::utils::CreationWithLazy<T>; \
	friend class screen::utils::SingletonLazyInstance<T>; \
	static T* _policy_instance_ptr;

#define SINGLETON_IMPL_CreationWithLazy(T) \
	T* T::_policy_instance_ptr = NULL;

#endif
