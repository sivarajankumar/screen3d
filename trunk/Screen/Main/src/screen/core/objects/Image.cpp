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

#include <screen/core/objects/Image.h>
#include <screen/core/objects/PixelFormat.h>
#include <screen/core/managers/TextureManager.h>
#include <screen/math/Vector2f.h>

namespace screen {
	namespace core {
		namespace objects {
		
			using screen::core::objects::PixelConverter;
			using screen::core::objects::PixelFormatDescriptor;
			
			Image::Image(const screen::math::Vector2i& size, screen::core::PixelFormat pxf)
				:size(size), pxf(pxf), pixels(size.getX() * size.getY() * PixelFormatDescriptor::getBytesPerPixels(pxf), 0x00){
				SCREEN_DECL_CONSTRUCTOR(Image)
			}
	
			Image::Image(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, const unsigned char* pixels)
				:size(size), pxf(pxf), pixels(pixels, pixels + size.getX() * size.getY() * PixelFormatDescriptor::getBytesPerPixels(pxf)){
				SCREEN_DECL_CONSTRUCTOR(Image)
			}
	
			const screen::math::Vector2i& Image::getSize() const{
				SCREEN_DECL_METHOD(getSize)
			    return size;
			}
	
			screen::core::PixelFormat Image::getPixelFormat() const{
				SCREEN_DECL_METHOD(getPixelFormat)
				return pxf;
			}
	
			const unsigned char* Image::getData() const{
				SCREEN_DECL_METHOD(getData)
				return &pixels[0];
			}
	
			void Image::loadFromFile(const std::string& filename){
				SCREEN_DECL_METHOD(loadFromFile)
				Image::SmartPtr image = TextureManager::instance()->loadImageFromFile(filename);
			    copy(*image);
			}
	
			void Image::fill(const screen::core::Color& color){
				SCREEN_DECL_METHOD(fill)
			    setPixel(0, 0, color);

			    unsigned int bpp = PixelFormatDescriptor::getBytesPerPixels(pxf);
			    std::vector<unsigned char>::iterator begin = pixels.begin();
			    for (std::vector<unsigned char>::iterator i = begin + bpp; i != pixels.end(); i += bpp)
			        std::copy(begin, begin + bpp, i);
			}
	
			void Image::setPixel(int x, int y, const unsigned char* pixel){
				SCREEN_DECL_METHOD(setPixel)
				std::copy(
			    	pixel,
			    	pixel + PixelFormatDescriptor::getBytesPerPixels(pxf),
			    	&pixels[(x + y * size.getX()) * PixelFormatDescriptor::getBytesPerPixels(pxf)]);
			}
	
			void Image::setPixel(int x, int y, const screen::core::Color& color){
				SCREEN_DECL_METHOD(setPixel)
				unsigned char* pixel = &pixels[(x + y * size.getX()) * PixelFormatDescriptor::getBytesPerPixels(pxf)];
			    unsigned char components[4] = {color.getBlue(), color.getGreen(), color.getRed(), color.getAlpha()};
			    PixelConverter::convertPixel(screen::core::PXF_A8R8G8B8, components, pxf, pixel);
			}
	
			void Image::getPixel(int x, int y, unsigned char* pixel) const{
				SCREEN_DECL_METHOD(getPixel)
				const unsigned char* begin = &pixels[(x + y * size.getX()) * PixelFormatDescriptor::getBytesPerPixels(pxf)];
			    std::copy(begin, begin + PixelFormatDescriptor::getBytesPerPixels(pxf), pixel);
			}
	
			screen::core::Color Image::getPixel(int x, int y) const{
				SCREEN_DECL_METHOD(getPixel)
				unsigned char components[4];
			    const unsigned char* pixel = &pixels[(x + y * size.getX()) * PixelFormatDescriptor::getBytesPerPixels(pxf)];
			    PixelConverter::convertPixel(pxf, pixel, PXF_A8R8G8B8, components);
			    return screen::core::Color(components[0], components[1], components[2], components[3]);
			}
	
			void Image::copy(const Image& src){
				SCREEN_DECL_METHOD(copy)
				SCREEN_LOG_DEBUG("Image copy :");
				SCREEN_LOG_DEBUG("\t- Source Pixel Format : " << src.pxf);
				SCREEN_LOG_DEBUG("\t- Target Pixel Format : " << pxf);
				SCREEN_LOG_DEBUG("\t- Source Size : [ " << src.size.getX() << " , " << src.size.getY() << " ]");
				SCREEN_LOG_DEBUG("\t- Target Size : [ " << size.getX() << " , " << size.getY() << " ]");
				if (size == src.size){
			        if (pxf == src.pxf){
			        	//same size, same format
			            pixels = src.pixels;
			        }
			        else{
			        	//same size, different format
			            const unsigned char* srcPixels  = &src.pixels[0];
			            unsigned char*       destPixels = &pixels[0];
			            unsigned int         srcBpp  = PixelFormatDescriptor::getBytesPerPixels(src.pxf);
			            unsigned int         destBpp = PixelFormatDescriptor::getBytesPerPixels(pxf);
	
			            PixelConverter converter(src.pxf, pxf);
			            int sizeX = size.getX();
			            int sizeY = size.getY();
			            for (int i = 0; i < sizeX; ++i){
			                for (int j = 0; j < sizeY; ++j){
			                	converter(srcPixels, destPixels);
			                    srcPixels  += srcBpp;
			                    destPixels += destBpp;
			                }
			            }
			        }
			    }
			    else{
		            int sizeX = size.getX();
		            int sizeY = size.getY();
		            //use a floats in order to keep precision and quality of Image
			        float stepX = static_cast<float>(src.size.getX()) / sizeX;
			        float stepY = static_cast<float>(src.size.getY()) / sizeY;
			        

			        if (pxf == src.pxf){
			            // different size, same format
			            unsigned char pixel[16];
			            for (int i = 0; i < sizeX; ++i){
			                for (int j = 0; j < sizeY; ++j){
			                    src.getPixel(static_cast<int>(i * stepX), static_cast<int>(j * stepX), pixel);
			                    setPixel(i, j, pixel);
			                }
			            }
			        }
			        else{
			            // different size, different format
			            unsigned char srcPixel[16], destPixel[16];
			            PixelConverter converter(src.pxf, pxf);
			            for (int i = 0; i < sizeX; ++i){
			                for (int j = 0; j < sizeY; ++j){
			                    src.getPixel(static_cast<int>(i * stepX), static_cast<int>(j * stepY), srcPixel);
			                    converter(srcPixel, destPixel);
			                    setPixel(i, j, destPixel);
			                }
			            }
			        }
			    }
			}
		}
	}
}
