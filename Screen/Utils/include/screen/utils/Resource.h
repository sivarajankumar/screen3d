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

#ifndef SCREEN_RESOURCE_H
#define SCREEN_RESOURCE_H

#include <screen/utils/Policies.h>
#include <screen/utils/Declaration.h>
#include <screen/utils/Export.h>
#include <string>

namespace screen {
    namespace utils {
    
    	/*!  \class ResourceBase
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 20 sept. 09
		 */

		class SCREEN_UTILS_EXPORT ResourceBase {
			SCREEN_DECL_CLASS(screen::utils::ResourceBase)
            friend class ResourceManager;
		protected:
			ResourceBase();
			virtual ~ResourceBase();
			
			const std::string& getName() const;
			virtual void add() = 0;
			virtual bool remove() = 0;
		private:
            std::string name;
		};

        /*!  \class Resource
          *  \brief herited class for a ressource
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  The resource is managed by ResourceManager \n
          *  The behaviour of allocation and unallocation is specified by the life-time policy
          */

        template<class LifeTimePolicy = ReferenceCountLifeTime>
        class Resource : public ResourceBase {
        	SCREEN_DECL_CLASS(screen::utils::Resource)
        public:
            Resource()
            	:ResourceBase(){
            	SCREEN_DECL_CONSTRUCTOR(Resource)
                lifeTime.instanciated();
            }
            
            virtual ~Resource(){
            	SCREEN_DECL_DESTRUCTOR(~Resource)
            }
            
            void add(){
            	SCREEN_DECL_METHOD(add)
                lifeTime.instanceUsed();
            }
            
            bool remove(){
            	SCREEN_DECL_METHOD(remove)
                lifeTime.deleted();
                bool ret = lifeTime.isAuthorisedDeletion();
            	if(ret)
            		delete this;
            	return ret;
            }
        private:
            Resource(Resource&) {}
            Resource& operator =(Resource& r) {
                return r;
            }
            LifeTimePolicy lifeTime;
        };
    }
}

#endif
