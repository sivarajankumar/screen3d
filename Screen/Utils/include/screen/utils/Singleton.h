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
 * \file screen/utils/Singleton.h
 * \brief Screen/Utils singleton implementation header file
 * \author
 *
 */

#ifndef SCREEN_SINGLETON_H
#define SCREEN_SINGLETON_H

#include <screen/utils/Policies.h>
#include <screen/utils/Thread.h>
#include <screen/utils/Export.h>
#include <screen/utils/SingletonLazyInstance.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {

		/**
		 * \brief Most generic singleton model.
		 *
         *  For multithreading, this singleton is not optimised for undestroyable singleton.
         *  In order to optimise in this case, use WeakSingletonModel.
		 *
		 * \tparam T Instance type
		 * \tparam TCreationPolicy Policy to choose the way to create the instance
		 * \tparam TThreadingModel Single or multiple threading policy
		 * \tparam TLifeTimePolicy Policy to determine if a singleton could be manually destroyed, ...
		 */
		template <	class T,
					template <class> class TCreationPolicy,
					class TThreadingModel,
					class TLifeTimePolicy >
        class SingletonModel {
        public:
			/**
			 * \brief Return the singleton instance pointer
			 *
			 * This method will create the instance
			 * if it does not exist
			 *
			 * \return Returns a singleton instance pointer
			 */
			static T* Instance();

			/**
			 * \brief Destroy the instance depending on the lifetime policy
			 */
			static void Destroy();

			typedef TLifeTimePolicy LifeTimePolicy;
			typedef TThreadingModel ThreadingModel;
		protected:
			/**
			 * \brief Default constructor
			 */
            SingletonModel() {}

			/**
			 * \brief Destructor
			 */
			virtual ~SingletonModel() {}
        };
        
		/**
		 * \brief Generic singleton model for multithread, unique and undestroyable singleton.
		 *
		 * \tparam T Instance type
		 * \tparam TCreationPolicy Policy to choose the way to create the instance
		 * \tparam TThreadingModel Single or multiple threading policy
		 */
		template <
        class T,
		template <class> class TCreationPolicy,
		class TThreadingModel
        >
        class WeakSingletonModel {
        public:
			/**
			 * \brief Return the singleton instance pointer
			 *
			 * This method will create the instance
			 * if it does not exist
			 *
			 * \return Returns a singleton instance pointer
			 */
			static T* Instance();

			typedef NoDestructionLifeTime LifeTimePolicy;
			typedef TThreadingModel ThreadingModel;
		protected:
			/**
			 * \brief Default constructor
			 */
			WeakSingletonModel() {}

			/**
			 * \brief Default constructor
			 */
			virtual ~WeakSingletonModel() {}
        };
        		
		template <	class T,
					template <class> class CreationPolicy,
					class ThreadingModel,
					class LifeTimePolicy >
		T* SingletonModel<	T,
							CreationPolicy,
							ThreadingModel,
							LifeTimePolicy
		>::Instance() {
			if(T::_PolicyInstancePtr==NULL) {
				typename ThreadingModel::ScopeLockType aGuard(T::_Mutex);
				if(T::_PolicyInstancePtr==NULL) {
					T::_PolicyInstancePtr = CreationPolicy<T>::Create();
					T::_LifeTime.instanciated();
    			}
			}
			T::_LifeTime.instanceUsed();
			return T::_PolicyInstancePtr;
	    }
	
		template <	class T,
					template <class> class CreationPolicy,
					class ThreadingModel,
					class LifeTimePolicy >
		void SingletonModel<	T,
								CreationPolicy,
								ThreadingModel,
								LifeTimePolicy
		>::Destroy() {
			if(T::_LifeTime.isAuthorisedDeletion()) {
				typename ThreadingModel::ScopeLockType aGuard(T::_Mutex);
				if(T::_LifeTime.isAuthorisedDeletion()) {
					CreationPolicy<T>::Delete(T::_PolicyInstancePtr);
	        	}
			}
			T::_LifeTime.Deleted();
	    }

		template <	class T,
					template <class> class CreationPolicy,
					class ThreadingModel>
		T* WeakSingletonModel<	T,
								CreationPolicy,
								ThreadingModel
		>::Instance() {
			if(T::_PolicyInstancePtr==NULL) {
				typename ThreadingModel::ScopeLockType aGuard(T::_Mutex);
				if(T::_PolicyInstancePtr==NULL) {
					T::_PolicyInstancePtr = CreationPolicy<T>::Create();
                }
            }
			return T::_PolicyInstancePtr;
        }
	    
        /* Singleton Types*/

		/**
		 * \brief Classical singleton class
		 *
		 * The singleton instanciation is thread safe
		 * Destroy method is not available
		 * The instanciation is a lazy one (i.e not created as program start)
		 *
		 */
	    template <class T>
		class UniqueSingleton : public WeakSingletonModel <	T,
															CreationWithLazy,
															MultipleThreadingModel> {
        };

		/**
		 * \brief Classical singleton class (not thread safe)
		 *
		 * The singleton instanciation is thread safe
		 * Destroy method is not available
		 * The instanciation is a lazy and safe one
		 * (i.e not created as program start and automatic destruction)
		 *
		 */
		template <class T>
		class ThreadUnsafeUniqueSingleton : public WeakSingletonModel <	T,
																		CreationWithLazy,
																		SingleThreadingModel>{
		};

		/**
		 * \brief Destroyable singleton class
		 *
		 * The singleton instanciation/destruction is thread safe
		 * Destroy method is available and always destroy the instance (if it exists)
		 * The instanciation/destruction is a dynamic one
		 *
		 */
		template <class T>
		class PhoenixSingleton : public SingletonModel <	T,
															CreationWithNew,
															MultipleThreadingModel,
															DestroyableInstanceLifeTime >{
		};

		/**
		 * \brief Destroyable singleton class (not thread safe)
		 *
		 * The singleton instanciation/destruction is thread safe
		 * Destroy method is available and always destroy the instance (if it exists)
		 * The instanciation/destruction is a dynamic one
		 *
		 */
		template <class T>
		class ThreadUnsafeSafePhoenixSingleton : public SingletonModel <	T,
																	CreationWithNew,
																	SingleThreadingModel,
																	DestroyableInstanceLifeTime >{
		};

		/* Dangerous class, so no support about this for now
		template <class T>
		class RefCountSingleton : public SingletonModel <	T,
															CreationWithNew,
															MultipleThreadingModel,
															ReferenceCountLifeTime >{
		};

        template <class T>
		class ThreadUnsafeRefCountSingleton : public SingletonModel <	T,
																CreationWithNew,
																SingleThreadingModel,
																ReferenceCountLifeTime >{
		};
		*/
    }
}

/* Common macros */

#define SINGLETON_DECL(SingletonType,T) \
	SINGLETON_DECL_COMMON(T) \
	SINGLETON_DECL_##SingletonType(T)

#define SINGLETON_IMPL(SingletonType,T) \
	SINGLETON_IMPL_COMMON(T) \
	SINGLETON_IMPL_##SingletonType(T)

#define SINGLETON_DECL_COMMON(T) \
    static T::ThreadingModel::MutexType _Mutex; \
    static T::LifeTimePolicy _LifeTime;

#define SINGLETON_IMPL_COMMON(T) \
    T::ThreadingModel::MutexType T::_Mutex; \
    T::LifeTimePolicy T::_LifeTime;

/* UniqueSingleton macros */

#define SINGLETON_DECL_UniqueSingleton(T) \
	friend class screen::utils::WeakSingletonModel <T, \
						screen::utils::CreationWithLazy, \
						screen::utils::MultipleThreadingModel>; \
	SINGLETON_DECL_CreationWithLazy(T)

#define SINGLETON_IMPL_UniqueSingleton(T) \
	SINGLETON_IMPL_CreationWithLazy(T)

/* ThreadUnsafeUniqueSingleton macros */

#define SINGLETON_DECL_ThreadUnsafeUniqueSingleton(T) \
	friend class screen::utils::WeakSingletonModel <T, \
						screen::utils::CreationWithLazy, \
						screen::utils::SingleThreadingModel>; \
	SINGLETON_DECL_CreationWithLazy(T)

#define SINGLETON_IMPL_ThreadUnsafeUniqueSingleton(T) \
	SINGLETON_IMPL_CreationWithLazy(T)

/* PhoenixSingleton macros */

#define SINGLETON_DECL_PhoenixSingleton(T) \
	friend class screen::utils::SingletonModel <T, \
						screen::utils::CreationWithNew, \
						screen::utils::MultipleThreadingModel, \
						screen::utils::DestroyableInstanceLifeTime>; \
	SINGLETON_DECL_CreationWithNew(T)

#define SINGLETON_IMPL_PhoenixSingleton(T) \
	SINGLETON_IMPL_CreationWithNew(T)

/* ThreadUnsafePhoenixSingleton macros */

#define SINGLETON_DECL_ThreadUnsafePhoenixSingleton(T) \
	friend class screen::utils::SingletonModel <T, \
						screen::utils::CreationWithNew, \
						screen::utils::SingleThreadingModel, \
						screen::utils::DestroyableInstanceLifeTime>; \
	SINGLETON_DECL_CreationWithNew(T)

#define SINGLETON_IMPL_PhoenixSingleton(T) \
	SINGLETON_IMPL_CreationWithNew(T)

/* Policy macros */

#define SINGLETON_DECL_CreationWithStatic(T) \
	friend class screen::utils::CreationWithStatic<T>; \
	static T _PolicyInstance; \
	static T* _PolicyInstancePtr;

#define SINGLETON_IMPL_CreationWithStatic(T) \
	T T::_PolicyInstance; \
	T* T::_PolicyInstancePtr = NULL;

#define SINGLETON_DECL_CreationWithLazy(T) \
	friend class screen::utils::CreationWithLazy<T>; \
	friend class screen::utils::SingletonLazyInstance<T>; \
	static T* _PolicyInstancePtr;

#define SINGLETON_IMPL_CreationWithLazy(T) \
	T* T::_PolicyInstancePtr = NULL;

#define SINGLETON_DECL_CreationWithNew(T) \
	friend class screen::utils::CreationWithNew<T>; \
	static T* _PolicyInstancePtr;

#define SINGLETON_IMPL_CreationWithNew(T) \
	T* T::_PolicyInstancePtr = NULL;

#endif
