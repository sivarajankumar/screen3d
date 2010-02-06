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

#include <Screen/Utils/ResourceManager.h>
#include <Screen/Utils/Logger.h>
#include <Screen/Utils/Exception.h>

namespace Screen {
	namespace Utils {
		ResourceManager::ResourceManager(){
			SCREEN_DECL_CONSTRUCTOR(ResourceManager)
		}
		
		ResourceManager::~ResourceManager(){
			SCREEN_DECL_DESTRUCTOR(~ResourceManager)
		    if (!resourceMap.empty()){
		        SCREEN_LOG_WARNING("Undeleted Resources :")
		        for (ResourceMap::const_iterator i = resourceMap.begin(); i != resourceMap.end(); ++i){
		            SCREEN_LOG_WARNING(" - " + i->second->getName())
		        }
		    }
		}
		
		void ResourceManager::add(const std::string& name, ResourceBase* resource){
		    SCREEN_DECL_METHOD(add)
			Assert(resource != NULL);

		    if (resourceMap.find(name) != resourceMap.end()){
		    	SCREEN_LOG_WARNING(name + " : Already loaded resource !")
		    }

		    resourceMap[name] = resource;
		    resource->name = name;
		}
		
		void ResourceManager::remove(const std::string& name){
			SCREEN_DECL_METHOD(remove)
		    ResourceMap::iterator i = resourceMap.find(name);

		    if (i == resourceMap.end()){
		    	SCREEN_LOG_WARNING(name + " : Delete unloaded resource !")
		    } else
		    	resourceMap.erase(i);
		}
	}
}
