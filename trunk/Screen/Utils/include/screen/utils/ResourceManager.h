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
 * \file screen/utils/ResourceManager.h
 * \brief Screen/Utils resource manager header file
 * \author
 *
 */

#ifndef SCREEN_RESOURCE_MANAGER_H
#define SCREEN_RESOURCE_MANAGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Resource.h>
#include <screen/utils/Declaration.h>
#include <map>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {

		/**
		 * \brief Manager for all resource instances
		 */
		class SCREEN_UTILS_EXPORT ResourceManager : public UniqueSingleton<ResourceManager> {
			SCREEN_DECL_CLASS(screen::utils::ResourceManager)
			SINGLETON_DECL(UniqueSingleton,ResourceManager)
		public:
			/**
			 * \brief Retrieve a resource from its name
			 *
			 * \tparam T The resource real type
			 * \param[in] iName The name of the resource
			 * \return The resource instance
			 */
			template <class T> T* get(const std::string& iName) const;

			/**
			 * \brief Register a resource and its name
			 *
			 * \param[in] iName The name of the resource
			 * \param[in,out] ioResource The resource instance
			 */
			void add(const std::string& iName, ResourceBase* ioResource);

			/**
			 * \brief Remove a resource from its name
			 *
			 * \param[in] iName The name of the resource
			 */
			void remove(const std::string& iName);
		private:
			/**
			 * \brief Default constructor
			 */
			ResourceManager();

			/**
			 * \brief Destructor
			 */
			~ResourceManager();

			typedef std::map<std::string, ResourceBase*> ResourceMap;

			ResourceMap _resourceMap; ///< Mapping between the resource name and the resource instances
		};
		
		template <class T>
		inline T* ResourceManager::get(const std::string& iName) const{
			SCREEN_DECL_METHOD(get)
			ResourceMap::const_iterator aIt = _resourceMap.find(iName);
			if (aIt != _resourceMap.end()){
				aIt->second->add();
				return dynamic_cast<T*>(aIt->second);
		    }
		    else{
		        return NULL;
		    }
		}
	}
}

#endif
