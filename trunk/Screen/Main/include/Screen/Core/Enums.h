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

#ifndef SCREEN_MATRIX_TYPE_H
#define SCREEN_MATRIX_TYPE_H

namespace Screen{
	namespace Core{
		enum MatrixType{
			MATRIX_VIEW,
			MATRIX_PROJECTION,
			MATRIX_TEXTURE0,
			MATRIX_TEXTURE1,
			MATRIX_TEXTURE2,
			MATRIX_TEXTURE3
		};
		
		enum LockFlag{
			LOCK_READ_WRITE,
			LOCK_READ_ONLY,
			LOCK_WRITE_ONLY
		};
		
		enum BufferFlag{
			STATIC_DRAW,
			DYNAMIC_DRAW
		};
		
		enum PrimitiveType{
	        PRIMITIVE_TRIANGLELIST,
	        PRIMITIVE_TRIANGLESTRIP,
	        PRIMITIVE_TRIANGLEFAN,
	        PRIMITIVE_LINELIST,
	        PRIMITIVE_LINESTRIP,
	        PRIMITIVE_POINTLIST
		};
		
	    enum VertexUsage{
	        VERTEX_USAGE_POSITION,  ///< Vecteur position
	        VERTEX_USAGE_NORMAL,    ///< Vecteur normal
	        VERTEX_USAGE_DIFFUSE,   ///< Couleur diffuse
	        VERTEX_USAGE_TEXCOORD0, ///< Coordonnées de texture 0
	        VERTEX_USAGE_TEXCOORD1, ///< Coordonnées de texture 1
	        VERTEX_USAGE_TEXCOORD2, ///< Coordonnées de texture 2
	        VERTEX_USAGE_TEXCOORD3  ///< Coordonnées de texture 3
	    };
	
	    enum VertexType{
	    	VERTEX_TYPE_FLOAT1, ///< 1 flottant
	    	VERTEX_TYPE_FLOAT2, ///< 2 floattants
	    	VERTEX_TYPE_FLOAT3, ///< 3 floattants
	    	VERTEX_TYPE_FLOAT4, ///< 4 floattants
	    	VERTEX_TYPE_COLOR   ///< Couleur (entier long non signé)
	    };
		
	    enum PixelFormat{
	        PXF_L8,
	        PXF_A8L8,
	        PXF_A1R5G5B5,
	        PXF_A4R4G4B4,
	        PXF_R8G8B8,
	        PXF_A8R8G8B8,
	        NB_PXF
	    };
	    
	    enum TextureFlag{
	    	TEXTURE_NO_FLAG = 0
	    };
	    
	    enum TextureMipMap{
	    	TEXTURE_NO_MIPMAP,
	    	TEXTURE_HAS_MIPMAP,
	    	TEXTURE_HAS_HARDWARE_MIPMAP
	    };
	    
	    enum RectangleIntersection{
	    	RECT_INT_IN,
	    	RECT_INT_INTERSECT,
	    	RECT_INT_OUT
	    };
	}
}

#endif
