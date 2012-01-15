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

#include <screen/utils/Resource.h>
#include <screen/utils/ResourceManager.h>

namespace screen {
	namespace utils {
		ResourceBase::ResourceBase()
			:name(""){
			SCREEN_DECL_CONSTRUCTOR(ResourceBase)
		}
		
		ResourceBase::~ResourceBase(){
			SCREEN_DECL_DESTRUCTOR(~ResourceBase)
			if(name!="")
				ResourceManager::Instance()->remove(name);
		}
		
        const std::string& ResourceBase::getName() const{
        	SCREEN_DECL_METHOD(getName)
        	return name;
        }
	}
}
