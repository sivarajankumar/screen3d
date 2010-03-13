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

#ifndef SCREEN_RESOURCE_MANAGER_H
#define SCREEN_RESOURCE_MANAGER_H

#include <Screen/Utils/Singleton.h>
#include <Screen/Utils/Resource.h>
#include <Screen/Utils/Declaration.h>
#include <map>

namespace Screen {
	namespace Utils {
		/*!  \class ResourceManager
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 20 sept. 09
		 */

		class SCREEN_EXPORT ResourceManager : public UniqueSingleton<ResourceManager> {
			SCREEN_DECL_CLASS(Screen::Utils::ResourceManager)
			SINGLETON_DECL(UniqueSingleton,ResourceManager)
		public:
			template <class T> T* get(const std::string& name) const;
			void add(const std::string& name, ResourceBase* resource);
			void remove(const std::string& name);
		private:
			ResourceManager();
			~ResourceManager();
			typedef std::map<std::string, ResourceBase*> ResourceMap;
			ResourceMap resourceMap;
		};
		
		template <class T>
		inline T* ResourceManager::get(const std::string& name) const{
			SCREEN_DECL_METHOD(get)
		    ResourceMap::const_iterator i = resourceMap.find(name);
		    if (i != resourceMap.end()){
		        i->second->add();
		        return dynamic_cast<T*>(i->second);
		    }
		    else{
		        return NULL;
		    }
		}
	}
}

#endif
