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

#include <Screen/Utils/Policies.h>
#include <Screen/Utils/Logger.h>
#include <Screen/Utils/Profiler.h>
#include <Screen/Utils/ResourceManager.h>
#include <Screen/Core/Managers/TextureManager.h>

namespace Screen {
	namespace Utils {
		template <class T>
		SCREEN_EXPORT T* CreationWithNew<T>::Create() {
            return new T();
        }

		template <class T>
		SCREEN_EXPORT void CreationWithNew<T>::Delete(T* inst) {
            delete inst;
        }
        
		template <class T>
		SCREEN_EXPORT T* CreationWithStatic<T>::Create() {
            static T inst;
            return &inst;
        }

		template <class T>
		SCREEN_EXPORT void CreationWithStatic<T>::Delete(T* inst) {}
        
        template class SCREEN_EXPORT CreationWithStatic<Logger>;
        template class SCREEN_EXPORT CreationWithStatic<Profiler>;
        template class SCREEN_EXPORT CreationWithStatic<ResourceManager>;
        template class SCREEN_EXPORT CreationWithStatic<Screen::Core::TextureManager>;	
	}
}
