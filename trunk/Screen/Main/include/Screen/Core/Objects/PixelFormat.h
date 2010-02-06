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

#ifndef SCREEN_PIXEL_FORMAT_H
#define SCREEN_PIXEL_FORMAT_H

#include <Screen/Core/Enums.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		namespace Objects {
			class SCREEN_EXPORT PixelConverter {
				SCREEN_DECL_CLASS(Screen::Core::Objects::PixelConverter)
			public:
				static void convertPixel(Screen::Core::PixelFormat srcFormat,
			    						const unsigned char* src,
			    						Screen::Core::PixelFormat destFormat,
			    						unsigned char* dest);
				
				PixelConverter(Screen::Core::PixelFormat srcFormat, Screen::Core::PixelFormat destFormat);
				~PixelConverter();
			    
			    void operator ()(const unsigned char* src,
								  unsigned char* dest) const;

			private:
				Screen::Core::PixelFormat srcFormat;
				Screen::Core::PixelFormat destFormat;
				typedef void (*ConvertionFunc) (const unsigned char*, unsigned char*);
				ConvertionFunc func;
			};
			
			class SCREEN_EXPORT PixelFormatDescriptor {
				SCREEN_DECL_CLASS(Screen::Core::Objects::PixelFormatDescriptor)
			public:
				static const char* getName(Screen::Core::PixelFormat pxf);
			    static unsigned int getBytesPerPixels(Screen::Core::PixelFormat pxf);
			    static bool isCompressed(Screen::Core::PixelFormat pxf);
				PixelFormatDescriptor(Screen::Core::PixelFormat pxf);
				~PixelFormatDescriptor();
				const char* getName() const;
				unsigned int getBytesPerPixels() const;
				bool isCompressed() const;
			private:
				Screen::Core::PixelFormat pxf;
			};
		}
	}
}

#endif
