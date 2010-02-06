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

#include <Screen/Utils/Policies.h>
#include <Screen/Utils/Thread.h>
#include <Screen/Utils/Export.h>
#include <cstdlib>

namespace Screen {
    namespace Utils {

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
        class SCREEN_EXPORT SingletonModel {
        public:
            static T* instance();
            static void destroy();
        protected:
            SingletonModel() {}
            virtual ~SingletonModel() {}
        private:
            static LifeTimePolicy lifeTime;
            static typename ThreadingModel::MutexType mutex;
            static T* instancePtr;
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
        class ThreadingModel>
        class SCREEN_EXPORT WeakSingletonModel {
        public:
            static T* instance();
        protected:
            WeakSingletonModel() {}
            virtual ~WeakSingletonModel() {}
        private:
            static typename ThreadingModel::MutexType mutex;
            static T* instancePtr;
        };

        /* Singleton Types*/

        template <class T>
        class SCREEN_EXPORT UniqueSingleton
                    : public WeakSingletonModel <
                    T,
                    CreationWithStatic,
                    SingleThreadingModel> {
        protected:
            UniqueSingleton() {}
        }
        ;

        template <class T>
        class SCREEN_EXPORT ThreadSafeUniqueSingleton
                    : public WeakSingletonModel <
                    T,
                    CreationWithStatic,
                    MultipleThreadingModel>
        {}
        ;

        template <class T>
        class SCREEN_EXPORT PhoenixSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    SingleThreadingModel,
                    DestroyableInstanceLifeTime >
    	{}
        ;

        template <class T>
        class SCREEN_EXPORT ThreadSafePhoenixSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    MultipleThreadingModel,
                    DestroyableInstanceLifeTime >
        {}
        ;

        template <class T>
        class SCREEN_EXPORT RefCountSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    SingleThreadingModel,
                    ReferenceCountLifeTime >
        {}
        ;

        template <class T>
        class SCREEN_EXPORT ThreadRefCountSingleton
                    : public SingletonModel <
                    T,
                    CreationWithNew,
                    MultipleThreadingModel,
                    ReferenceCountLifeTime >
        {}
        ;
        
//        template <class T>
//	    class SCREEN_EXPORT SharedSingleton
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

#endif
