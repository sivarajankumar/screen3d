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

#include <screen/core/Enums.h>
#include <screen/core/objects/Image.h>
#include <screen/math/Vector2i.h>
#include <screen/math/Rectangle.h>
#include <screen/main/Export.h>
#include <screen/utils/SmartPtr.h>
#include <screen/utils/Resource.h>
#include <screen/utils/Declaration.h>

namespace screen {
	namespace core {
		namespace objects {
			/*!  \class TextureBase
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 11 nov. 09
			 */

			class SCREEN_MAIN_EXPORT TextureBase : public screen::utils::Resource<> {
				friend class Texture;
				SCREEN_DECL_CLASS(screen::core::TextureBase)
			public:
				TextureBase(screen::math::Vector2i size, screen::core::PixelFormat pxf, screen::core::TextureMipMap hasMipMap);
				virtual ~TextureBase();
				
				virtual void update(const screen::math::Rectangle& rect) = 0;
				
				typedef screen::utils::SmartPtr<TextureBase,screen::utils::ResourceSmartPolicy> SmartPtr;
			protected:
				screen::core::objects::Image image;
				screen::math::Vector2i size;
				screen::core::PixelFormat pxf;
				screen::core::TextureMipMap hasMipMap;
			};
		}
	}
}

#endif
