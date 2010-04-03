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

#ifndef SCREEN_PLUGIN_H
#define SCREEN_PLUGIN_H

#include <Screen/Utils/Export.h>
#include <Screen/Utils/Exception.h>
#include <Screen/Utils/Declaration.h>

#ifdef WIN32
#include <windows.h>
#endif

namespace Screen {
    namespace Utils {

		template <class T>
		class Plugin{
//			SCREEN_DECL_CLASS(Screen::Utils::Plugin)
		public:
			Plugin()
				:sharedLibrary(NULL){
//				SCREEN_DECL_CONSTRUCTOR(Plugin)
			}

			~Plugin(){
//				SCREEN_DECL_DESTRUCTOR(~Plugin)
				if(sharedLibrary!=NULL)
					FreeLibrary(sharedLibrary);
			}

			T* load(const std::string& fileName){
//				SCREEN_DECL_METHOD(load)
				sharedLibrary = LoadLibrary((fileName+".dll").c_str());
				if(sharedLibrary==NULL)
					throw LoadingException(fileName+".dll","Shared library load failed");
				LoadFunct ptr = reinterpret_cast<LoadFunct>(GetProcAddress(sharedLibrary,loadFunctionName));
				if(ptr==NULL)
					throw LoadingException(fileName+".dll",(std::string)"No function for loading instance ("+loadFunctionName+")");
				return (*ptr)();
			}
		private:
			typedef T* (*LoadFunct)();
			HMODULE sharedLibrary;
			static const char * loadFunctionName;
		};

		template <class T>
		const char * Plugin<T>::loadFunctionName = "getInstanceFromPlugin";
    }
}

#endif
