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

#ifndef SCREEN_OPENGL_PIXEL_FORMAT_H
#define SCREEN_OPENGL_PIXEL_FORMAT_H

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>

namespace Screen {
	namespace OGL {
		struct OpenGLPixelFormat{
			GLenum format, fullFormat, type;
		};
	
		static OpenGLPixelFormat oglPxf[] = {
		    {GL_LUMINANCE,       GL_LUMINANCE8,                    GL_UNSIGNED_BYTE},
		    {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8,             GL_UNSIGNED_BYTE},
		    {GL_BGRA,            GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV},
		    {GL_BGRA,            GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV},
		    {GL_BGR,             GL_RGB8,                          GL_UNSIGNED_BYTE},
		    {GL_BGRA,            GL_RGBA8,                         GL_UNSIGNED_BYTE}
		};
	}
}

#endif
