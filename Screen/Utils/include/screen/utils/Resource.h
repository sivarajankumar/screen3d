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
 * \file screen/utils/Resource.h
 * \brief Screen/Utils resource base header file
 * \author
 *
 */

#ifndef SCREEN_RESOURCE_H
#define SCREEN_RESOURCE_H

#include <screen/utils/Policies.h>
#include <screen/utils/Declaration.h>
#include <screen/utils/Export.h>
#include <string>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {
    
		/**
		 * \brief Interface for all resource instances
		 */
		class SCREEN_UTILS_EXPORT ResourceBase {
			SCREEN_DECL_CLASS(screen::utils::ResourceBase)
            friend class ResourceManager;
		protected:

			/**
			 * \brief Default constructor
			 */
			ResourceBase();

			/**
			 * \brief Destructor
			 */
			virtual ~ResourceBase();
			
			/**
			 * \brief Resource name accessor
			 *
			 * \return The name string
			 */
			const std::string& getName() const;

			/**
			 * \brief Indicate the resource is used in a new context
			 */
			virtual void add() = 0;

			/**
			 * \brief Indicate the resource is unused in a context
			 *
			 * \return Indicates is the resource instance has been deleted
			 */
			virtual bool remove() = 0;
		private:
			std::string _name; ///< Resource name string
		};

		/**
		 * \brief Lifetime policy based Resource class
		 *
		 * \tparam LifeTimePolicy Policy to determine when the resource instance is deleted
		 */
		template<class LifeTimePolicy = ReferenceCountLifeTime>
        class Resource : public ResourceBase {
        	SCREEN_DECL_CLASS(screen::utils::Resource)
        public:
			/**
			 * \brief Default constructor
			 */
			Resource()
            	:ResourceBase(){
            	SCREEN_DECL_CONSTRUCTOR(Resource)
				_lifeTime.instanciated();
            }
            
			/**
			 * \brief Destructor
			 */
			virtual ~Resource(){
            	SCREEN_DECL_DESTRUCTOR(~Resource)
            }
            
			/**
			 * \brief Indicate the resource is used in a new context
			 */
			void add(){
            	SCREEN_DECL_METHOD(add)
				_lifeTime.instanceUsed();
            }
            
			/**
			 * \brief Indicate the resource is unused in a context
			 *
			 * \return Indicates is the resource instance has been deleted
			 */
			bool remove(){
            	SCREEN_DECL_METHOD(remove)
				_lifeTime.deleted();
				bool aToDelete = _lifeTime.isAuthorisedDeletion();
				if(aToDelete)
            		delete this;
				return aToDelete;
            }
        private:
			/**
			 * \brief Copy constructor
			 *
			 * Private constructor to forbid copy of the resource
			 */
			Resource(Resource&) {}

			/**
			 * \brief Copy operator
			 *
			 * Private operator to forbid copy of the resource
			 *
			 * \param[in] iR A dummy resource
			 * \return The same dummy resource
			 */
			Resource& operator =(Resource& iR) {
				return iR;
            }

			LifeTimePolicy _lifeTime; ///< Lifetime policy instance
        };
    }
}

#endif
