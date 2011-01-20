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

#include <screen/opengl/OpenGLTexture.h>
#include <screen/opengl/OpenGLRenderer.h>
#include <screen/opengl/OpenGLPixelFormat.h>
#include <screen/math/Vector2i.h>
#include <screen/core/Enums.h>
#include <screen/core/objects/PixelFormat.h>
#include <screen/opengl/GlHeaders.h>

namespace screen {
	namespace opengl {
		OpenGLTexture::OpenGLTexture(unsigned int texture, const Vector2i& size, PixelFormat pxf, screen::core::TextureMipMap hasMipMap)
			:TextureBase(size,pxf,hasMipMap), texture(texture)
		{}
		
		OpenGLTexture::~OpenGLTexture(){
		    if (texture)
		        glDeleteTextures(1, &texture);
		}
		
		void OpenGLTexture::update(const screen::math::Rectangle& rect){
			Assert(screen::math::Rectangle(0, 0, size.getX(), size.getY()).intersects(rect) == screen::math::RECT_INT_IN);
			SCREEN_LOG_DEBUG("Texture update :");

			OpenGLPixelFormat texturePxf = oglPxf[pxf];
			OpenGLPixelFormat imagePxf = oglPxf[image.getPixelFormat()];

		    // texture binding
		    glBindTexture(GL_TEXTURE_2D, texture);

		    // pixel updates
		    if (screen::core::objects::PixelFormatDescriptor::isCompressed(image.getPixelFormat())){
		    	SCREEN_LOG_DEBUG("\t- Compressed format : " << screen::core::objects::PixelFormatDescriptor::getName(image.getPixelFormat()));
		        unsigned long dataSize = rect.getWidth() * rect.getHeight() * screen::core::objects::PixelFormatDescriptor::getBytesPerPixels(image.getPixelFormat());
		        if (rect.getWidth() == size.getX() && rect.getHeight() == size.getY()){
		            OpenGLRenderer::glCompressedTexSubImage2DARB(GL_TEXTURE_2D, 0, rect.getLeft(), rect.getTop(), rect.getWidth(), rect.getHeight(), imagePxf.format, dataSize, image.getData());
		        }
		        else{
		            //TODO : compressed subimage
		        }
		    }
		    else{
		    	SCREEN_LOG_DEBUG("\t- Not compressed format : " << screen::core::objects::PixelFormatDescriptor::getName(image.getPixelFormat()));
		        if (hasMipMap == screen::core::TEXTURE_HAS_HARDWARE_MIPMAP){
		        	SCREEN_LOG_DEBUG("\t- has hardware mipmapping");
		            //TODO : hardware mipmap
		        }
		        else if(hasMipMap == screen::core::TEXTURE_HAS_MIPMAP){
		        	SCREEN_LOG_DEBUG("\t- has software mipmapping");
		            // mipmap level update
		            gluBuild2DMipmaps(GL_TEXTURE_2D, texturePxf.fullFormat, size.getX(), size.getY(), imagePxf.format, imagePxf.type, image.getData());
		        }
		        else{
		        	SCREEN_LOG_DEBUG("\t- has no mipmapping");
		            //if ((rect.getWidth() == size.getX()) && (rect.getHeight() == size.getY()))
		            //{	
		                glTexImage2D(GL_TEXTURE_2D, 0, texturePxf.fullFormat, size.getX(), size.getY(), 0, imagePxf.format, imagePxf.type, image.getData());
		            //}
		            //else
		            //{
		                //CImage SubData = m_Data.SubImage(Rect);
		                //glTexSubImage2D(GL_TEXTURE_2D, 0, Rect.Left(), Rect.Top(), Rect.Width(), Rect.Height(), ImgFmt.Format, ImgFmt.Type, SubData.GetData());
		            //}
		            //gluBuild2DMipmaps(GL_TEXTURE_2D, texturePxf.fullFormat, size.getX(), size.getY(), imagePxf.format, imagePxf.type, image.getData());
		        }
		    }

		    // texture unbinding
		    glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		unsigned int OpenGLTexture::getTextureNumber() const{
			return texture;
		}
	}
}
