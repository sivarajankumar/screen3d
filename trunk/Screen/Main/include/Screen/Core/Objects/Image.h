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

#ifndef SCREEN_IMAGE_H
#define SCREEN_IMAGE_H

#include <Screen/Math/Vector2i.h>
#include <Screen/Math/Rectangle.h>
#include <Screen/Core/Color.h>
#include <Screen/Core/Enums.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/Resource.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		namespace Objects {
		
			/** This class represents a loaded image file
			 @remarks
			 	The Image class contains method to load,
			 	get and modify image data.
			 */
			class SCREEN_EXPORT Image : public Screen::Utils::Resource<> {
			public:
				SCREEN_DECL_CLASS(Screen::Core::Objects::Image)
				Image(const Screen::Math::Vector2i& size = Screen::Math::Vector2i(1, 1), Screen::Core::PixelFormat pxf = PXF_A8R8G8B8);
		        Image(const Screen::Math::Vector2i& size, Screen::Core::PixelFormat pxf, const unsigned char* pixels);

		        const Screen::Math::Vector2i& getSize() const;
		        Screen::Core::PixelFormat getPixelFormat() const;
		        const unsigned char* getData() const;

		        void loadFromFile(const std::string& filename);
		        void fill(const Screen::Core::Color& color);
		        void setPixel(int x, int y, const unsigned char* pixel);
		        void setPixel(int x, int y, const Screen::Core::Color& color);

		        void getPixel(int x, int y, unsigned char* pixel) const;
		        Screen::Core::Color getPixel(int x, int y) const;
		        void copy(const Image& src);
		        
		        typedef Screen::Utils::SmartPtr<Image, Screen::Utils::ResourceSmartPolicy> SmartPtr;
		    private :
		        Screen::Math::Vector2i size;
		        Screen::Core::PixelFormat pxf;
		        std::vector<unsigned char> pixels; ///< Tableau des pixels
			};
		}
	}
}

#endif
