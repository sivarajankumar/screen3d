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
 * \file screen/utils/ResourceManager.cpp
 * \brief Screen/Utils resource manager source file
 * \author
 *
 */

#include <screen/utils/ResourceManager.h>
#include <screen/utils/Logger.h>
#include <screen/utils/Exception.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {
		SINGLETON_IMPL(UniqueSingleton,ResourceManager)
	
		ResourceManager::ResourceManager(){
			SCREEN_DECL_CONSTRUCTOR(ResourceManager)
		}
		
		ResourceManager::~ResourceManager(){
			//SCREEN_DECL_DESTRUCTOR(~ResourceManager)
			if (!_resourceMap.empty()){
				SCREEN_LOG_WARNING("Undeleted Resources :");
				for (ResourceMap::const_iterator aIt = _resourceMap.begin(); aIt != _resourceMap.end(); ++aIt){
					SCREEN_LOG_WARNING(" - " + aIt->second->getName());
		        }
		    }
		}
		
		void ResourceManager::add(const std::string& iName, ResourceBase* ioResource){
		    SCREEN_DECL_METHOD(add)
			SCREEN_ASSERT(ioResource != NULL);

			if (_resourceMap.find(iName) != _resourceMap.end()){
				SCREEN_LOG_WARNING(iName + " : Already loaded resource !");
		    }

			_resourceMap[iName] = ioResource;
			ioResource->_name = iName;
		}
		
		void ResourceManager::remove(const std::string& iName){
			SCREEN_DECL_METHOD(remove)
			ResourceMap::iterator aIt = _resourceMap.find(iName);

			if (aIt == _resourceMap.end()){
				SCREEN_LOG_WARNING(iName + " : Delete unloaded resource !");
		    } else
				_resourceMap.erase(aIt);
		}
	}
}
