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

#ifndef SCREEN_OPENGL_TEXTURE_H
#define SCREEN_OPENGL_TEXTURE_H

#include <screen/core/objects/TextureBase.h>
#include <screen/math/Vector2i.h>
#include <screen/core/Enums.h>

namespace screen {
	namespace opengl {
		using screen::core::objects::TextureBase;
		using screen::math::Vector2i;
		using screen::core::PixelFormat;
		/*!  \class OpenGLTexture
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 11 nov. 09
		 */

		class OpenGLTexture : public TextureBase {
		public:
			OpenGLTexture(unsigned int texture, const Vector2i& size, PixelFormat pxf, screen::core::TextureMipMap hasMipMap);
			~OpenGLTexture();

			void update(const screen::math::Rectangle& rect);
			
			unsigned int getTextureNumber() const;
		private:
			unsigned int texture;
		};
	}
}

#endif
