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
 * \file screen/utils/SingletonLazyInstance.h
 * \brief Screen/Utils singleton lazy instance handler header file
 * \author
 *
 */

#ifndef SCREEN_SINGLETON_LAZY_INSTANCE_H
#define SCREEN_SINGLETON_LAZY_INSTANCE_H

#include <screen/utils/Thread.h>
#include <screen/utils/SingletonLazyInstanceManager.h>
#include <screen/utils/Export.h>
#include <iostream>
// separate from others Lazy classes
// only used for singleton lazy instanciation

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        /**
         * \brief Singleton lazy instance interface.
         *
         *  The goal of this class is to have a common interface all instances handled by SingletonLazyInstanceManager
         */
		class SCREEN_UTILS_EXPORT SingletonLazyInstanceInterface {
		public:
            /**
             * \brief Default constructor
             */
			SingletonLazyInstanceInterface();

            /**
             * \brief Destructor
             */
			virtual ~SingletonLazyInstanceInterface();

            /**
             * \brief Destroy lazy instance method
             *
             * Must only be called by SingletonLazyInstanceManager
             */
			virtual void destroy() = 0;
		};
		
        /**
         * \brief Singleton lazy instance class.
         *
         * \tparam T Instance type
         * \tparam ThreadingModel Single or multiple threading policy
         */
        template <class T,
				  class ThreadingModel = SingleThreadingModel>
		class SingletonLazyInstance : public SingletonLazyInstanceInterface {
		public:
            /**
             * \brief Default constructor
             */
		    SingletonLazyInstance()
				:SingletonLazyInstanceInterface(),_instance(NULL){}
		
            /**
             * \brief Destructor
             */
            virtual ~SingletonLazyInstance(){}
		
            /**
             * \brief Method to retrieve the lazy instance
             *
             * Create the instance on the first call
             *
             * \return Returns the singleton lazy instance reference
             */
            T& get() {
				if(_instance==NULL) {
					typename ThreadingModel::ScopeLockType aGuard(_mutex);
					if(_instance==NULL) {
						_instance = new T();
						SingletonLazyInstanceInterface* aBase = this;
						SingletonLazyInstanceManager::registerLazy(aBase);
		            }
		        }
				return (*_instance);
		    }

            /**
             * \brief Destroy lazy instance method
             *
             * Must only be called by SingletonLazyInstanceManager
             */
            void destroy(){
				delete _instance;
                _instance = NULL;
			}
		
		private:
            typename ThreadingModel::MutexType _mutex; ///< Mutex instance for lazy instantiation
            T* _instance; ///< lazy instance pointer
		};
	}
}


#endif

