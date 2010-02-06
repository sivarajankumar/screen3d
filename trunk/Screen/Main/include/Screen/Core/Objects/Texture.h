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

#ifndef SCREEN_TEXTURE_H
#define SCREEN_TEXTURE_H

#include <Screen/Core/Objects/Image.h>
#include <Screen/Core/Objects/TextureBase.h>
#include <Screen/Math/Rectangle.h>
#include <Screen/Math/Vector2i.h>
#include <Screen/Core/Enums.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		namespace Objects {
			/*!  \class Texture
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 29 nov. 09
			 */

			class SCREEN_EXPORT Texture {
			public:
				Texture();
				~Texture();

		        void create(const Screen::Math::Vector2i& size,
		        			Screen::Core::PixelFormat pxf,
		        			Screen::Core::TextureFlag flags = Screen::Core::TEXTURE_NO_FLAG,
		        			const std::string& name = "");
		        
		        void createFromFile(const std::string& filename,
		        					Screen::Core::PixelFormat pxf,
		        					Screen::Core::TextureFlag flags = Screen::Core::TEXTURE_NO_FLAG);
		        
		        void createFromImage(const Image& image,
		        					 Screen::Core::PixelFormat pxf,
		        					 Screen::Core::TextureFlag flags = Screen::Core::TEXTURE_NO_FLAG,
		        					 const std::string& name = "");
		        
		        void update(const Screen::Math::Rectangle& rect = Screen::Math::Rectangle(-1, -1, -1, -1));

		        Screen::Core::Objects::Image& getImage();
		        const Screen::Math::Vector2i& getSize() const;
		        Screen::Core::PixelFormat getFormat() const;
		        const std::string& getName() const;
		        const TextureBase* getTexture() const;

		        bool operator ==(const Texture& texture) const;
		        bool operator !=(const Texture& texture) const;

		    private :
		        void load(const Image& image, Screen::Core::PixelFormat pxf, Screen::Core::TextureFlag flags, const std::string& name);

		        TextureBase::SmartPtr texture;
		    };	
		}
	}
}

#endif
