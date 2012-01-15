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

#ifndef SCREEN_TEXTURE_H
#define SCREEN_TEXTURE_H

#include <screen/core/objects/Image.h>
#include <screen/core/objects/TextureBase.h>
#include <screen/math/Rectangle.h>
#include <screen/math/Vector2i.h>
#include <screen/core/Enums.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen {
	namespace core {
		namespace objects {
			/*!  \class Texture
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 29 nov. 09
			 */

			class SCREEN_MAIN_EXPORT Texture {
			public:
				Texture();
				~Texture();

		        void create(const screen::math::Vector2i& size,
		        			screen::core::PixelFormat pxf,
		        			screen::core::TextureFlag flags = screen::core::TEXTURE_NO_FLAG,
		        			const std::string& name = "");
		        
		        void createFromFile(const std::string& filename,
		        					screen::core::PixelFormat pxf,
		        					screen::core::TextureFlag flags = screen::core::TEXTURE_NO_FLAG);
		        
		        void createFromImage(const Image& image,
		        					 screen::core::PixelFormat pxf,
		        					 screen::core::TextureFlag flags = screen::core::TEXTURE_NO_FLAG,
		        					 const std::string& name = "");
		        
		        void update(const screen::math::Rectangle& rect = screen::math::Rectangle(-1, -1, -1, -1));

		        screen::core::objects::Image& getImage();
		        const screen::math::Vector2i& getSize() const;
		        screen::core::PixelFormat getFormat() const;
		        const std::string& getName() const;
		        const TextureBase* getTexture() const;

		        bool operator ==(const Texture& texture) const;
		        bool operator !=(const Texture& texture) const;

		    private :
		        void load(const Image& image, screen::core::PixelFormat pxf, screen::core::TextureFlag flags, const std::string& name);

		        TextureBase::SmartPtr texture;
		    };	
		}
	}
}

#endif
