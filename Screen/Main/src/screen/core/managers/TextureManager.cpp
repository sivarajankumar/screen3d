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

#include <screen/core/managers/TextureManager.h>
#include <screen/utils/ResourceManager.h>

namespace screen {
	namespace core {
		SINGLETON_IMPL(UniqueSingleton,TextureManager)
	
		using screen::core::objects::Image;
		using screen::core::objects::TextureBase;
	
		TextureManager::TextureManager(){
			SCREEN_DECL_CONSTRUCTOR(TextureManager)
		}
		TextureManager::~TextureManager(){
			SCREEN_DECL_DESTRUCTOR(~TextureManager)
		}
		
		Image::SmartPtr TextureManager::loadImageFromFile(const screen::utils::File& filename) const{
			SCREEN_DECL_METHOD(loadImageFromFile)
			Image* ptr = screen::utils::ResourceManager::Instance()->get<Image>(filename.getFullname());
			if(ptr==NULL){
	    		ptr = loadMediaFromFile<Image>(filename);
				screen::utils::ResourceManager::Instance()->add(filename.getFullname(),ptr);
	    	}
	    	return ptr;
		}
		
		TextureBase::SmartPtr TextureManager::loadTextureFromFile(const screen::utils::File& filename) const{
			SCREEN_DECL_METHOD(loadTextureFromFile)
			TextureBase* ptr = screen::utils::ResourceManager::Instance()->get<TextureBase>(filename.getFullname());
			// not automaticly loaded, use Texture::load
	    	return ptr;
		}
	}
}
