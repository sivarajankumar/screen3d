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

#ifndef SCREEN_IMAGE_H
#define SCREEN_IMAGE_H

#include <screen/math/Vector2i.h>
#include <screen/math/Rectangle.h>
#include <screen/core/Color.h>
#include <screen/core/Enums.h>
#include <screen/utils/SmartPtr.h>
#include <screen/utils/Resource.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen {
	namespace core {
		namespace objects {
		
			/** This class represents a loaded image file
			 @remarks
			 	The Image class contains method to load,
			 	get and modify image data.
			 */
			class SCREEN_MAIN_EXPORT Image : public screen::utils::Resource<> {
			public:
				SCREEN_DECL_CLASS(screen::core::objects::Image)
				Image(const screen::math::Vector2i& size = screen::math::Vector2i(1, 1), screen::core::PixelFormat pxf = PXF_A8R8G8B8);
		        Image(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, const unsigned char* pixels);

		        const screen::math::Vector2i& getSize() const;
		        screen::core::PixelFormat getPixelFormat() const;
		        const unsigned char* getData() const;

		        void loadFromFile(const std::string& filename);
		        void fill(const screen::core::Color& color);
		        void setPixel(int x, int y, const unsigned char* pixel);
		        void setPixel(int x, int y, const screen::core::Color& color);

		        void getPixel(int x, int y, unsigned char* pixel) const;
		        screen::core::Color getPixel(int x, int y) const;
		        void copy(const Image& src);
		        
		        typedef screen::utils::SmartPtr<Image, screen::utils::ResourceSmartPolicy> SmartPtr;
		    private :
		        screen::math::Vector2i size;
		        screen::core::PixelFormat pxf;
		        std::vector<unsigned char> pixels; ///< Tableau des pixels
			};
		}
	}
}

#endif
