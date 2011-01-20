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
#define SCREEN_HANDLER_DYN_LIB HMODULE
#define SCREEN_UNLOAD_DYN_LIB FreeLibrary
#define SCREEN_LOAD_DYN_LIB LoadLibrary
#define SCREEN_LOAD_FUNCTION_DYN_LIB GetProcAddress
#define SCREEN_EXT_DYN_LIB ".dll"
#else
#include <dlfcn.h>
#define SCREEN_HANDLER_DYN_LIB void*
#define SCREEN_UNLOAD_DYN_LIB dlclose
#define SCREEN_LOAD_DYN_LIB(a) dlopen(a, RTLD_LAZY)
#define SCREEN_LOAD_FUNCTION_DYN_LIB dlsym
#define SCREEN_EXT_DYN_LIB ".so"
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
					SCREEN_UNLOAD_DYN_LIB(sharedLibrary);
			}

			T* load(const std::string& fileName){
//				SCREEN_DECL_METHOD(load)
				sharedLibrary = SCREEN_LOAD_DYN_LIB((fileName+SCREEN_EXT_DYN_LIB).c_str());
				if(sharedLibrary==NULL)
					throw LoadingException(fileName+SCREEN_EXT_DYN_LIB,"Shared library load failed");
				LoadFunct ptr = reinterpret_cast<LoadFunct>(SCREEN_LOAD_FUNCTION_DYN_LIB(sharedLibrary,loadFunctionName));
				if(ptr==NULL)
					throw LoadingException(fileName+SCREEN_EXT_DYN_LIB,(std::string)"No function for loading instance ("+loadFunctionName+")");
				return (*ptr)();
			}
		private:
			typedef T* (*LoadFunct)();
			SCREEN_HANDLER_DYN_LIB sharedLibrary;
			static const char * loadFunctionName;
		};

		template <class T>
		const char * Plugin<T>::loadFunctionName = "getInstanceFromPlugin";
    }
}

#endif
