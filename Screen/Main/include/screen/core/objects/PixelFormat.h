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

#ifndef SCREEN_PIXEL_FORMAT_H
#define SCREEN_PIXEL_FORMAT_H

#include <screen/core/Enums.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen {
	namespace core {
		namespace objects {
			class SCREEN_MAIN_EXPORT PixelConverter {
				SCREEN_DECL_CLASS(screen::core::objects::PixelConverter)
			public:
				static void convertPixel(screen::core::PixelFormat srcFormat,
			    						const unsigned char* src,
			    						screen::core::PixelFormat destFormat,
			    						unsigned char* dest);
				
				PixelConverter(screen::core::PixelFormat srcFormat, screen::core::PixelFormat destFormat);
				~PixelConverter();
			    
			    void operator ()(const unsigned char* src,
								  unsigned char* dest) const;

			private:
				screen::core::PixelFormat srcFormat;
				screen::core::PixelFormat destFormat;
				typedef void (*ConvertionFunc) (const unsigned char*, unsigned char*);
				ConvertionFunc func;
			};
			
			class SCREEN_MAIN_EXPORT PixelFormatDescriptor {
				SCREEN_DECL_CLASS(screen::core::objects::PixelFormatDescriptor)
			public:
				static const char* getName(screen::core::PixelFormat pxf);
			    static unsigned int getBytesPerPixels(screen::core::PixelFormat pxf);
			    static bool isCompressed(screen::core::PixelFormat pxf);
				PixelFormatDescriptor(screen::core::PixelFormat pxf);
				~PixelFormatDescriptor();
				const char* getName() const;
				unsigned int getBytesPerPixels() const;
				bool isCompressed() const;
			private:
				screen::core::PixelFormat pxf;
			};
		}
	}
}

#endif
