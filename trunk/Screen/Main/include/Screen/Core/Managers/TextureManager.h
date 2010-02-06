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

#ifndef SCREEN_TEXTURE_MANAGER_H
#define SCREEN_TEXTURE_MANAGER_H

#include <Screen/Utils/Singleton.h>
#include <Screen/Utils/MediaManager.h>
#include <Screen/Core/Objects/Image.h>
#include <Screen/Core/Objects/TextureBase.h>
#include <Screen/Utils/File.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		typedef TYPE_LIST_2(Screen::Core::Objects::Image, Screen::Core::Objects::TextureBase) TextureMediaList;
	
		/*!  \class TextureManager
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 5 déc. 09
		 */

		class SCREEN_EXPORT TextureManager : public Screen::Utils::UniqueSingleton<TextureManager>,
			public Screen::Utils::MediaManager<TextureMediaList>{
			SCREEN_DECL_CLASS(Screen::Core::TextureManager)
			friend class Screen::Utils::CreationWithStatic<TextureManager>;
		public:
			TextureManager();
			~TextureManager();
			
			Screen::Core::Objects::Image::SmartPtr loadImageFromFile(const Screen::Utils::File& filename) const;
			Screen::Core::Objects::TextureBase::SmartPtr loadTextureFromFile(const Screen::Utils::File& filename) const;
		private:
		};
	}
}

#endif
