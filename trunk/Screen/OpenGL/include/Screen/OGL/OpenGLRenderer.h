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

#ifndef SCREEN_OPENGL_RENDERER_H
#define SCREEN_OPENGL_RENDERER_H

#include <Screen/Core/Renderer/Renderer.h>
#include <Screen/Utils/Singleton.h>
#include <Screen/Core/Enums.h>
#include <Screen/Utils/Declaration.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#ifdef WIN32
#	include <gl/wglext.h>
#else
#	include <gl/glxext.h>
#endif

namespace Screen{
	namespace OGL{
		class OpenGLRenderer : public Screen::Core::Renderer{
		private:
			OpenGLRenderer();
			~OpenGLRenderer();
			
			void loadExtensions();
		public:
			static OpenGLRenderer* instance();
			
			void initialize();
			void beginScene();
			void endScene();
			
			bool hasCapability(Screen::Core::ApiCapability caps) const;
			
			void pushMatrix(Screen::Core::MatrixType type);
			void popMatrix(Screen::Core::MatrixType type);
			void setMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix);
			void multipleMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix);
			void getMatrix(Screen::Core::MatrixType type, Screen::Math::Matrix4x4f& matrix);
			
			unsigned long convertColor(const Screen::Core::Color& color) const;
			
			Screen::Core::BufferBase* createVB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const;
			Screen::Core::BufferBase* createIB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const; 
	        void setVB(const Screen::Core::BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex, const Screen::Core::VertexFormat& vf);
	        void setIB(const Screen::Core::BufferBase* buffer, unsigned long stride);
	        
	        void drawIndexedPrimitives(Screen::Core::PrimitiveType type, unsigned long firstIndex, unsigned long count) const;
	        
	        Screen::Core::Objects::TextureBase* createTexture(const Screen::Math::Vector2i& size, Screen::Core::PixelFormat pxf, Screen::Core::TextureFlag flags) const;
	        void setTextureBase(const Screen::Core::Objects::TextureBase* texture);
		private:
			std::string openGLExtensions;
			bool capabilityTable[Screen::Core::NB_CAP];
			bool checkExtension(const std::string& extension) const;
			
			unsigned long indexStride;
			
			static unsigned long glMatrixType[];
			static unsigned long glBufferFlags[];
		public:
	        static PFNGLBINDBUFFERARBPROC          glBindBufferARB;
	        static PFNGLDELETEBUFFERSARBPROC       glDeleteBuffersARB;
	        static PFNGLGENBUFFERSARBPROC          glGenBuffersARB;
	        static PFNGLBUFFERDATAARBPROC          glBufferDataARB;
	        static PFNGLBUFFERSUBDATAARBPROC       glBufferSubDataARB;
	        static PFNGLGETBUFFERSUBDATAARBPROC    glGetBufferSubDataARB;
	        static PFNGLMAPBUFFERARBPROC           glMapBufferARB;
	        static PFNGLUNMAPBUFFERARBPROC         glUnmapBufferARB;
	        static PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB;
	        static PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
	        static PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC  glCompressedTexSubImage2DARB;
#ifdef WIN32
	        static PFNWGLCHOOSEPIXELFORMATARBPROC  wglChoosePixelFormatARB;
	        static PFNWGLCREATEPBUFFERARBPROC      wglCreatePbufferARB;
	        static PFNWGLGETPBUFFERDCARBPROC       wglGetPbufferDCARB;
	        static PFNWGLRELEASEPBUFFERDCARBPROC   wglReleasePbufferDCARB;
	        static PFNWGLDESTROYPBUFFERARBPROC     wglDestroyPbufferARB;
	        static PFNWGLQUERYPBUFFERARBPROC       wglQueryPbufferARB;
#else
	        
#endif
		};
	}
}
#endif
