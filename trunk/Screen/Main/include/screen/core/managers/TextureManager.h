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

#ifndef SCREEN_TEXTURE_MANAGER_H
#define SCREEN_TEXTURE_MANAGER_H

#include <screen/utils/Singleton.h>
#include <screen/utils/Policies.h>
#include <screen/utils/MediaManager.h>
#include <screen/core/objects/Image.h>
#include <screen/core/objects/TextureBase.h>
#include <screen/utils/File.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen {
	namespace core {
		typedef TYPE_LIST_2(screen::core::objects::Image, screen::core::objects::TextureBase) TextureMediaList;
	
		/*!  \class TextureManager
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 5 déc. 09
		 */

		class SCREEN_MAIN_EXPORT TextureManager : public screen::utils::UniqueSingleton<TextureManager>,
			public screen::utils::MediaManager<TextureMediaList>{
			SCREEN_DECL_CLASS(screen::core::TextureManager)
			SINGLETON_DECL(UniqueSingleton,TextureManager)
		public:
			TextureManager();
			~TextureManager();
			
			screen::core::objects::Image::SmartPtr loadImageFromFile(const screen::utils::File& filename) const;
			screen::core::objects::TextureBase::SmartPtr loadTextureFromFile(const screen::utils::File& filename) const;
		private:
		};
	}
}

#endif
