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

#include <screen/core/objects/Texture.h>
#include <screen/core/Managers/TextureManager.h>
#include <screen/core/objects/PixelFormat.h>
#include <screen/core/Renderer/Renderer.h>
#include <screen/utils/ResourceManager.h>
#include <screen/math/Other.h>

namespace screen {
	namespace core {
		namespace objects {
			Texture::Texture(){}
			Texture::~Texture(){}
	
	        void Texture::create(const screen::math::Vector2i& size,
	        					 screen::core::PixelFormat pxf,
	        					 screen::core::TextureFlag flags,
	        					 const std::string& name){
	        	Image image(size,pxf);
	        	createFromImage(image, pxf, flags, name);
	        }
	        
	        void Texture::createFromFile(const std::string& filename,
	        							 screen::core::PixelFormat pxf,
	        							 screen::core::TextureFlag flags){
	            texture = screen::core::TextureManager::instance()->loadTextureFromFile(filename);
	            if(texture==NULL){
	            	Image::SmartPtr image = screen::core::TextureManager::instance()->loadImageFromFile(filename);
	            	load(*image, pxf, flags, filename);
	            }
	        }
	        
	        void Texture::createFromImage(const Image& image,
	        							  screen::core::PixelFormat pxf,
	        							  screen::core::TextureFlag flags,
	        							  const std::string& name){
	        	texture = screen::core::TextureManager::instance()->loadTextureFromFile(name);
	            if(texture==NULL){
	            	load(image, pxf, flags, name);
	            }
	        }
	        
	        void Texture::update(const screen::math::Rectangle& rect){
	            if (rect.getWidth() == -1 || rect.getHeight() == -1)
	                texture->update(screen::math::Rectangle(0, 0, getSize().getX(), getSize().getY()));
	            else
	                texture->update(rect);
	        }
	
	        screen::core::objects::Image& Texture::getImage(){
	        	return texture->image;
	        }
	        const screen::math::Vector2i& Texture::getSize() const{
	        	return texture->size;
	        }
	        screen::core::PixelFormat Texture::getFormat() const{
	        	return texture->pxf;
	        }
	        const std::string& Texture::getName() const{
	        	return texture->getName();
	        }
	        const TextureBase* Texture::getTexture() const{
	        	return texture;
	        }
	
	        bool Texture::operator ==(const Texture& _texture) const{
	        	return texture == _texture.texture;
	        }
	        bool Texture::operator !=(const Texture& texture) const{
	        	return !(*this == texture);
	        }
	
	        void Texture::load(const Image& image, screen::core::PixelFormat pxf, screen::core::TextureFlag flags, const std::string& name){
		        using screen::core::objects::PixelFormatDescriptor;
	        	if (PixelFormatDescriptor::isCompressed(pxf) && !screen::core::Renderer::get()->hasCapability(screen::core::CAPABILITY_COMPRESSED_TEXTURE)){
		        	// compressed texture but not supported by the API
		        	pxf = screen::core::PXF_A8R8G8B8;
		            SCREEN_LOG_WARNING("Compressed texture but not supported by the API");
	           		SCREEN_LOG_WARNING("New format : PXF_A8R8G8B8");
	           		if(name!=""){
	           			SCREEN_LOG_WARNING("Texture : " << name);
	           		}
		        }
		
	        	screen::math::Vector2i size = image.getSize();
	        	if(!screen::core::Renderer::get()->hasCapability(screen::core::CAPABILITY_NON_POWER_OF_TWO_TEXTURE)){
	        		screen::math::Vector2i size2(screen::math::nearestPowerOfTwo(image.getSize().getX()),
	        									 screen::math::nearestPowerOfTwo(image.getSize().getY()));
			        if ((size2 != image.getSize())){
			        	SCREEN_LOG_WARNING("Non power of 2 sized texture but not supported by the API");
			        	SCREEN_LOG_WARNING("Change size :");
			        	SCREEN_LOG_WARNING("[" << image.getSize().getX() << "," << image.getSize().getY() << "] => [" << size2.getX() << "," << size2.getY() << "]");
			        	if(name!=""){
		           			SCREEN_LOG_WARNING("Texture : " << name);
		           		}
			        	size = size2;
			        }
	        	}
	        	
	        	SCREEN_LOG_DEBUG("Texture size : ""[" << size.getX() << "," << size.getY() << "]");
		
		        texture = Renderer::get()->createTexture(size, pxf, flags);
		
		        if (name != ""){
		            screen::utils::ResourceManager::instance()->add(name, texture);
		        }
		
		        // Copie des pixels
		        getImage().copy(image);
		        update();
			}
		}
	}
}

