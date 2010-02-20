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

#include <Screen/OGL/OpenGLTexture.h>
#include <Screen/OGL/OpenGLRenderer.h>
#include <Screen/Math/Vector2i.h>
#include <Screen/Core/Enums.h>
#include <Screen/Core/Objects/PixelFormat.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>

namespace Screen {
	namespace OGL {
		struct OpenGLPixelFormat{
			GLenum format, fullFormat, type;
		};
	
		OpenGLPixelFormat oglPxf[] = {
		    {GL_LUMINANCE,       GL_LUMINANCE8,                    GL_UNSIGNED_BYTE},
		    {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8,             GL_UNSIGNED_BYTE},
		    {GL_BGRA,            GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV},
		    {GL_BGRA,            GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV},
		    {GL_BGR,             GL_RGB8,                          GL_UNSIGNED_BYTE},
		    {GL_BGRA,            GL_RGBA8,                         GL_UNSIGNED_BYTE}
		};
	
		OpenGLTexture::OpenGLTexture(unsigned int texture, const Vector2i& size, PixelFormat pxf, Screen::Core::TextureMipMap hasMipMap)
			:TextureBase(size,pxf,hasMipMap), texture(texture)
		{}
		
		OpenGLTexture::~OpenGLTexture(){
		    if (texture)
		        glDeleteTextures(1, &texture);
		}
		
		void OpenGLTexture::update(const Screen::Math::Rectangle& rect){
			Assert(Screen::Math::Rectangle(0, 0, size.getX(), size.getY()).intersects(rect) == Screen::Core::RECT_INT_IN);
			SCREEN_LOG_DEBUG("Texture update :");

			OpenGLPixelFormat texturePxf = oglPxf[pxf];
			OpenGLPixelFormat imagePxf = oglPxf[image.getPixelFormat()];

		    // texture binding
		    glBindTexture(GL_TEXTURE_2D, texture);

		    // pixel updates
		    if (Screen::Core::Objects::PixelFormatDescriptor::isCompressed(image.getPixelFormat())){
		    	SCREEN_LOG_DEBUG("\t- Compressed format : " << Screen::Core::Objects::PixelFormatDescriptor::getName(image.getPixelFormat()));
		        unsigned long dataSize = rect.getWidth() * rect.getHeight() * Screen::Core::Objects::PixelFormatDescriptor::getBytesPerPixels(image.getPixelFormat());
		        if (rect.getWidth() == size.getX() && rect.getHeight() == size.getY()){
		            OpenGLRenderer::glCompressedTexSubImage2DARB(GL_TEXTURE_2D, 0, rect.getLeft(), rect.getTop(), rect.getWidth(), rect.getHeight(), imagePxf.format, dataSize, image.getData());
		        }
		        else{
		            //TODO : compressed subimage
		        }
		    }
		    else{
		    	SCREEN_LOG_DEBUG("\t- Not compressed format : " << Screen::Core::Objects::PixelFormatDescriptor::getName(image.getPixelFormat()));
		        if (hasMipMap == Screen::Core::TEXTURE_HAS_HARDWARE_MIPMAP){
		        	SCREEN_LOG_DEBUG("\t- has hardware mipmapping");
		            //TODO : hardware mipmap
		        }
		        else if(hasMipMap == Screen::Core::TEXTURE_HAS_MIPMAP){
		        	SCREEN_LOG_DEBUG("\t- has software mipmapping");
		            // mipmap level update
		            gluBuild2DMipmaps(GL_TEXTURE_2D, texturePxf.fullFormat, size.getX(), size.getY(), imagePxf.format, imagePxf.type, image.getData());
		        }
		        else{
		        	SCREEN_LOG_DEBUG("\t- has no mipmapping");
		            gluBuild2DMipmaps(GL_TEXTURE_2D, texturePxf.fullFormat, size.getX(), size.getY(), imagePxf.format, imagePxf.type, image.getData());
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
