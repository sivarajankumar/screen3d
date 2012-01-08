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

#include <screen/utils/SingletonLazyInstanceManager.h>
#include <screen/utils/SingletonLazyInstance.h>

namespace screen {
	namespace utils {
		SingletonLazyInstanceManager SingletonLazyInstanceManager::_Instance;
		
		void SingletonLazyInstanceManager::registerLazy(SingletonLazyInstanceInterface* ioBase){
			_Instance._stack.push(ioBase);
		}

		SingletonLazyInstanceManager::SingletonLazyInstanceManager(){}
		SingletonLazyInstanceManager::~SingletonLazyInstanceManager(){
			while(!_stack.empty()){
				SingletonLazyInstanceInterface* ioBase = _stack.top();
				ioBase->destroy();
				delete ioBase;
				_stack.pop();
			}				
		}
	}
}
