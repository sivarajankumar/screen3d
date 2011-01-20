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

#ifndef SCREEN_TEXTURE_BASE_H
#define SCREEN_TEXTURE_BASE_H

#include <Screen/Core/Enums.h>
#include <Screen/Core/Objects/Image.h>
#include <Screen/Math/Vector2i.h>
#include <Screen/Math/Rectangle.h>
#include <Screen/Main/Export.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/Resource.h>
#include <Screen/Utils/Declaration.h>

namespace Screen {
	namespace Core {
		namespace Objects {
			/*!  \class TextureBase
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 11 nov. 09
			 */

			class SCREEN_MAIN_EXPORT TextureBase : public Screen::Utils::Resource<> {
				friend class Texture;
				SCREEN_DECL_CLASS(Screen::Core::TextureBase)
			public:
				TextureBase(Screen::Math::Vector2i size, Screen::Core::PixelFormat pxf, Screen::Core::TextureMipMap hasMipMap);
				virtual ~TextureBase();
				
				virtual void update(const Screen::Math::Rectangle& rect) = 0;
				
				typedef Screen::Utils::SmartPtr<TextureBase,Screen::Utils::ResourceSmartPolicy> SmartPtr;
			protected:
				Screen::Core::Objects::Image image;
				Screen::Math::Vector2i size;
				Screen::Core::PixelFormat pxf;
				Screen::Core::TextureMipMap hasMipMap;
			};
		}
	}
}

#endif
