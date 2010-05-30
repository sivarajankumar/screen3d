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

#ifndef SCREEN_OPENGL_GL_HEADERS_H
#define SCREEN_OPENGL_GL_HEADERS_H

#ifdef WIN32
#	include <gl/gl.h>
#	include <gl/glu.h>
#	include <gl/glext.h>
#	include <gl/wglext.h>
#else
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <GL/glext.h>
namespace Screen {
	namespace X11NS {
#	include <X11/Xlib.h>
#	include <X11/Xutil.h>
typedef XID GLXContextID;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
typedef XID GLXPbuffer;
typedef XID GLXWindow;
typedef XID GLXFBConfigID;
typedef struct __GLXcontextRec *GLXContext;
                                 typedef struct __GLXFBConfigRec *GLXFBConfig;
#define GLX_GLXEXT_PROTOTYPES
#	include <GL/glxext.h>
	}
}

#define glXGetProcAddress Screen::X11NS::glXGetProcAddress

#endif

#endif