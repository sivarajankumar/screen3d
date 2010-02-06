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

#include <Screen/Utils/Singleton.h>
#include <Screen/Utils/Policies.h>
#include <Screen/Utils/Thread.h>
#include <Screen/Utils/Logger.h>
#include <Screen/Utils/Profiler.h>
#include <Screen/Utils/ResourceManager.h>
#include <Screen/Core/Managers/TextureManager.h>

namespace Screen {
	namespace Utils {
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    SCREEN_EXPORT T* SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::instancePtr = NULL;
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    SCREEN_EXPORT LifeTimePolicy SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::lifeTime;
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    SCREEN_EXPORT typename ThreadingModel::MutexType SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::mutex;
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    SCREEN_EXPORT T* SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::instance() {
	        typename ThreadingModel::ScopeLockType guard(mutex);
	        if(instancePtr==NULL) {
	            instancePtr = CreationPolicy<T>::Create();
	            lifeTime.Instanciated();
	        }
	        lifeTime.InstanceUsed();
	        return instancePtr;
	    }
	
	    template <class T, template <class> class CreationPolicy, class ThreadingModel, class LifeTimePolicy >
	    SCREEN_EXPORT void SingletonModel<T, CreationPolicy, ThreadingModel, LifeTimePolicy>::destroy() {
	        typename ThreadingModel::ScopeLockType guard(mutex);
	        if(lifeTime.IsAuthorisedDeletion()) {
	            CreationPolicy<T>::Delete(instancePtr);
	        }
	        lifeTime.Deleted();
	    }
	    
        template <class T, template <class> class CreationPolicy, class ThreadingModel>
        SCREEN_EXPORT T* WeakSingletonModel<T, CreationPolicy, ThreadingModel>::instancePtr = NULL;

        template <class T, template <class> class CreationPolicy, class ThreadingModel>
        SCREEN_EXPORT typename ThreadingModel::MutexType WeakSingletonModel<T, CreationPolicy, ThreadingModel>::mutex;

        template <class T, template <class> class CreationPolicy, class ThreadingModel>
        SCREEN_EXPORT T* WeakSingletonModel<T, CreationPolicy, ThreadingModel>::instance() {
            if(instancePtr==NULL) {
                typename ThreadingModel::ScopeLockType guard(mutex);
                if(instancePtr==NULL) {
                    instancePtr = CreationPolicy<T>::Create();
                }
            }
            return instancePtr;
        }
        
        template class SCREEN_EXPORT WeakSingletonModel<Logger,CreationWithStatic,SingleThreadingModel>;
        template class SCREEN_EXPORT WeakSingletonModel<Profiler,CreationWithStatic,SingleThreadingModel>;
        template class SCREEN_EXPORT WeakSingletonModel<ResourceManager,CreationWithStatic,SingleThreadingModel>;
        template class SCREEN_EXPORT WeakSingletonModel<Screen::Core::TextureManager,CreationWithStatic,SingleThreadingModel>;
        template class SCREEN_EXPORT UniqueSingleton<Logger>;
        template class SCREEN_EXPORT UniqueSingleton<Profiler>;
        template class SCREEN_EXPORT UniqueSingleton<ResourceManager>;
        template class SCREEN_EXPORT UniqueSingleton<Screen::Core::TextureManager>;	
	}
}
