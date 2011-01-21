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

#include <screen/core/objects/PixelFormat.h>
#include <screen/utils/Exception.h>

namespace screen {
	namespace core {
		namespace objects {
			using namespace screen::core;
			
			template <unsigned int Src, unsigned int Dest>
			inline void convertPixelT(const unsigned char* src, unsigned char* dest){
				throw screen::utils::Exception("Unsupported pixel convertion");
			}
			
#define CONVERT_FUNCTION(DEST) \
	template <> \
	inline void convertPixelT<SRC, DEST>(const unsigned char* src, unsigned char* dest)
			
#undef SRC
#define SRC PXF_L8
			
			CONVERT_FUNCTION(PXF_L8){
			    *dest = *src;
			}

			CONVERT_FUNCTION(PXF_A8L8){
				dest[0] = *src;
			    dest[1] = 0xFF;
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    *reinterpret_cast<unsigned short*>(dest) =
			    	0x8000 |
			        ((*src >> 3) << 10) |
			        ((*src >> 3) <<  5) |
			        ((*src >> 3) <<  0);
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
				dest[0] = (*src & 0xF0) | (*src >> 4);
			    dest[1] = 0xF0 | (*src >> 4);
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    dest[0] = *src;
			    dest[1] = *src;
			    dest[2] = *src;
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    dest[0] = *src;
			    dest[1] = *src;
			    dest[2] = *src;
			    dest[3] = 0xFF;
			}


#undef SRC
#define SRC PXF_A8L8
			
			CONVERT_FUNCTION(PXF_L8){
				*dest = src[0];
			}

			CONVERT_FUNCTION(PXF_A8L8){
			    dest[0] = src[0];
			    dest[1] = src[1];
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    *reinterpret_cast<unsigned short*>(dest) = 
			    	((src[1] >> 7) << 15) |
			        ((src[0] >> 3) << 10) |
			        ((src[0] >> 3) <<  5) |
			        ((src[0] >> 3) <<  0);
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
			    dest[0] = (src[0] & 0xF0) | (src[0] >> 4);
			    dest[1] = (src[1] & 0xF0) | (src[0] >> 4);
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[0];
			    dest[2] = src[0];
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[0];
			    dest[2] = src[0];
			    dest[3] = src[1];
			}

#undef SRC
#define SRC PXF_A1R5G5B5
			
			CONVERT_FUNCTION(PXF_L8){
			    unsigned short pix = *reinterpret_cast<const unsigned short*>(src);
			    *dest = static_cast<unsigned char>(
			    		((pix & 0x7C00) >> 7) * 0.30 +
			            ((pix & 0x03E0) >> 2) * 0.59 +
			            ((pix & 0x001F) << 3) * 0.11);
			}

			CONVERT_FUNCTION(PXF_A8L8){
			    unsigned short pix = *reinterpret_cast<const unsigned short*>(src);
			    dest[0] = static_cast<unsigned char>(
			    		((pix & 0x7C00) >> 7) * 0.30 +
			            ((pix & 0x03E0) >> 2) * 0.59 +
			            ((pix & 0x001F) << 3) * 0.11);
			    dest[1] = src[1] & 0x8000 ? 0xFF : 0x00;
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    dest[0] = src[0];
			    dest[1] = src[1];
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
			    unsigned short pix = *reinterpret_cast<const unsigned short*>(src);
			    dest[1] = (pix & 0x8000 ? 0xF0 : 0x00) | ((pix & 0x7C00) >> 11);
			    dest[0] = ((pix & 0x03C0) >> 2) | ((pix & 0x001F) >> 1);
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    unsigned short pix = *reinterpret_cast<const unsigned short*>(src);
			    dest[2] = (pix & 0x7C00) >> 7;
			    dest[1] = (pix & 0x03E0) >> 2;
			    dest[0] = (pix & 0x001F) << 3;
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    unsigned short pix = *reinterpret_cast<const unsigned short*>(src);
			    dest[3] = (pix & 0x8000) >> 8;
			    dest[2] = (pix & 0x7C00) >> 7;
			    dest[1] = (pix & 0x03E0) >> 2;
			    dest[0] = (pix & 0x001F) << 3;
			}

#undef SRC
#define SRC PXF_A4R4G4B4
			
			CONVERT_FUNCTION(PXF_L8){
			    *dest = static_cast<unsigned char>(
			    		((src[1] & 0x0F) << 4) * 0.30 +
			            ((src[0] & 0xF0) >> 0) * 0.59 +
			            ((src[0] & 0x0F) << 4) * 0.11);
			}

			CONVERT_FUNCTION(PXF_A8L8){
			    dest[0] = static_cast<unsigned char>(
			    		((src[1] & 0x0F) << 4) * 0.30 +
			            ((src[0] & 0xF0) >> 0) * 0.59 +
			            ((src[0] & 0x0F) << 4) * 0.11);
			    dest[1] = src[1] & 0xF0;
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    *reinterpret_cast<unsigned short*>(dest) =
			    	((src[1] & 0x80) <<  8) |
			        ((src[1] & 0x0F) << 11) |
			        ((src[0] & 0xF0) <<  2) |
			        ((src[0] & 0x0F) <<  1);
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
			    dest[0] = src[0];
			    dest[1] = src[1];
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    dest[0] = (src[0] & 0x0F) << 4;
			    dest[1] = (src[0] & 0xF0);
			    dest[2] = (src[1] & 0x0F) << 4;
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    dest[0] = (src[0] & 0x0F) << 4;
			    dest[1] = (src[0] & 0xF0);
			    dest[2] = (src[1] & 0x0F) << 4;
			    dest[3] = (src[1] & 0xF0);
			}

#undef SRC
#define SRC PXF_R8G8B8
			
			CONVERT_FUNCTION(PXF_L8){
			    *dest = static_cast<unsigned char>(src[2] * 0.30 + src[1] * 0.59 + src[0] * 0.11);
			}

			CONVERT_FUNCTION(PXF_A8L8){
			    dest[0] = static_cast<unsigned char>(src[2] * 0.30 + src[1] * 0.59 + src[0] * 0.11);
			    dest[1] = 0xFF;
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    *reinterpret_cast<unsigned short*>(dest) =
			    	0x8000 |
			        ((src[2] >> 3) << 10) |
			        ((src[1] >> 3) <<  5) |
			        ((src[0] >> 3) <<  0);
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
			    dest[0] = (src[1] & 0xF0) | (src[0] >> 4);
			    dest[1] = 0xF0 | (src[2] >> 4);
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[1];
			    dest[2] = src[2];
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[1];
			    dest[2] = src[2];
			    dest[3] = 0xFF;
			}

#undef SRC
#define SRC PXF_A8R8G8B8
			
			CONVERT_FUNCTION(PXF_L8){
			    *dest = static_cast<unsigned char>(src[2] * 0.30 + src[1] * 0.59 + src[0] * 0.11);
			}

			CONVERT_FUNCTION(PXF_A8L8){
			    dest[0] = static_cast<unsigned char>(src[2] * 0.30 + src[1] * 0.59 + src[0] * 0.11);
			    dest[1] = src[3];
			}

			CONVERT_FUNCTION(PXF_A1R5G5B5){
			    *reinterpret_cast<unsigned short*>(dest) =
			    	((src[3] >> 7) << 15) |
			        ((src[2] >> 3) << 10) |
			        ((src[1] >> 3) <<  5) |
			        ((src[0] >> 3) <<  0);
			}
			
			CONVERT_FUNCTION(PXF_A4R4G4B4){
			    dest[0] = (src[1] & 0xF0) | (src[0] >> 4);
			    dest[1] = (src[3] & 0xF0) | (src[2] >> 4);
			}

			CONVERT_FUNCTION(PXF_R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[1];
			    dest[2] = src[2];
			}

			CONVERT_FUNCTION(PXF_A8R8G8B8){
			    dest[0] = src[0];
			    dest[1] = src[1];
			    dest[2] = src[2];
			    dest[3] = src[3];
			}
			
#undef SRC
			typedef void (*ConvertionFunc) (const unsigned char*, unsigned char*);
							
			#define CONV_LINE(PXF) { \
				&convertPixelT<PXF, screen::core::PXF_L8>, \
				&convertPixelT<PXF, screen::core::PXF_A8L8>, \
				&convertPixelT<PXF, screen::core::PXF_A1R5G5B5>, \
				&convertPixelT<PXF, screen::core::PXF_A4R4G4B4>, \
				&convertPixelT<PXF, screen::core::PXF_R8G8B8>, \
				&convertPixelT<PXF, screen::core::PXF_A8R8G8B8> \
			}
							
			//line = src
			//column = dest
			const ConvertionFunc convertFuncTable[screen::core::NB_PXF][screen::core::NB_PXF] = {
				CONV_LINE(screen::core::PXF_L8),
				CONV_LINE(screen::core::PXF_A8L8),
				CONV_LINE(screen::core::PXF_A1R5G5B5),
				CONV_LINE(screen::core::PXF_A4R4G4B4),
				CONV_LINE(screen::core::PXF_R8G8B8),
				CONV_LINE(screen::core::PXF_A8R8G8B8)
			};
			
			#undef CONV_LINE
			
			void PixelConverter::convertPixel(PixelFormat srcFormat, const unsigned char* src, PixelFormat destFormat, unsigned char* dest){
				SCREEN_DECL_FUNCTION(convertPixel)
				(*(convertFuncTable[srcFormat][destFormat]))(src,dest);
			}
			
			PixelConverter::PixelConverter(screen::core::PixelFormat srcFormat, screen::core::PixelFormat destFormat)
				:srcFormat(srcFormat),destFormat(destFormat),func(*(convertFuncTable[srcFormat][destFormat])){
				SCREEN_DECL_CONSTRUCTOR(PixelConverter)
			}
			
			PixelConverter::~PixelConverter(){
				SCREEN_DECL_DESTRUCTOR(~PixelConverter)
			}
		    
		    void PixelConverter::operator() (const unsigned char* src,
							  				 unsigned char* dest) const{
		    	SCREEN_DECL_METHOD(operator())
		    	(*func)(src,dest);
		    }
			
			
			enum PixelFormatFlags{
				PXFF_HAS_RED		= 0x00000001,
				PXFF_HAS_GREEN		= 0x00000002,
				PXFF_HAS_BLUE		= 0x00000004,
				PXFF_HAS_COLOR		= 0x00000007, //red+green+blue
				PXFF_HAS_ALPHA		= 0x00000008,
				PXFF_HAS_LUMINANCE	= 0x00000010,
				PXFF_COMPRESSED		= 0x00000100,
				PXFF_DEPTH			= 0x00000200, //for depth textures
			};
			
		    struct PixelFormatDescription{
		        // FormatName
		        const char *name;
		        // Format byte number
		        unsigned char nbBytes;
		        // Pixel format flags
		        int flags;
		        // Number of bits for red, green, blue, alpha, luminance
		        unsigned char rbits,gbits,bbits,abits,lbist; 
		        // Position of bits
		        unsigned char rpos, gpos, bpos, apos, lpos;
		    };
		    
		    const PixelFormatDescription pfdTable[screen::core::NB_PXF] = {
		    	//PXF_L8
		    	{
		    		"PXF_L8",
		    		1,
		    		PXFF_HAS_LUMINANCE,
		    		0,0,0,0,8,
		    		0,0,0,0,0
		    	},
		    	//PXF_A8L8
		    	{
		    		"PXF_A8L8",
		    		2,
		    		PXFF_HAS_ALPHA | PXFF_HAS_LUMINANCE,
		    		0,0,0,8,8,
		    		0,0,0,8,0
		    	},
		    	//PXF_A1R5G5B5
		    	{
		    		"PXF_A1R5G5B5",
		    		2,
		    		PXFF_HAS_ALPHA | PXFF_HAS_COLOR,
		    		5,5,5,1,0,
		    		10,5,0,15,0
		    	},
		    	//PXF_A4R4G4B4
		    	{
		    		"PXF_A4R4G4B4",
		    		2,
		    		PXFF_HAS_ALPHA | PXFF_HAS_COLOR,
		    		4,4,4,4,0,
		    		8,4,0,12,0
		    	},
		    	//PXF_R8G8B8
		    	{
		    		"PXF_R8G8B8",
		    		3,
		    		PXFF_HAS_COLOR,
		    		8,8,8,0,0,
		    		16,8,0,0,0
		    	},
		    	//PXF_A8R8G8B8
		    	{
		    		"PXF_A8R8G8B8",
		    		4,
		    		PXFF_HAS_ALPHA | PXFF_HAS_COLOR,
		    		8,8,8,8,0,
		    		16,8,0,24,0
		    	}		    	
		    };
		    
		    const char* PixelFormatDescriptor::getName(screen::core::PixelFormat pxf){
		    	return pfdTable[pxf].name;
		    }
		    unsigned int PixelFormatDescriptor::getBytesPerPixels(screen::core::PixelFormat pxf){
		    	return pfdTable[pxf].nbBytes;
		    }
		    bool PixelFormatDescriptor::isCompressed(screen::core::PixelFormat pxf){
		    	return (pfdTable[pxf].flags & PXFF_COMPRESSED)!=0;
		    }
		    
		    PixelFormatDescriptor::PixelFormatDescriptor(screen::core::PixelFormat pxf)
		    	:pxf(pxf)
		    {}
		    PixelFormatDescriptor::~PixelFormatDescriptor(){}
		    
		    const char* PixelFormatDescriptor::getName() const{
		    	return getName(pxf);
		    }
		    unsigned int PixelFormatDescriptor::getBytesPerPixels() const{
		    	return getBytesPerPixels(pxf);
		    }
		    bool PixelFormatDescriptor::isCompressed() const{
		    	return isCompressed(pxf);
		    }
		}
	}
}
