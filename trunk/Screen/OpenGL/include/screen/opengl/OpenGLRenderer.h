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

#include <screen/core/renderer/Renderer.h>
#include <screen/utils/Singleton.h>
#include <screen/core/Enums.h>
#include <screen/utils/Declaration.h>
#include <screen/opengl/GlHeaders.h>

namespace screen{
	namespace opengl{		
		class OpenGLRenderer : public screen::core::Renderer{
		private:
			OpenGLRenderer();
			~OpenGLRenderer();
			
			void loadExtensions();
		public:
			static OpenGLRenderer* instance();
			
			void initialize();
			void beginScene();
			void endScene();
			
			bool hasCapability(screen::core::ApiCapability caps) const;
			
			void pushMatrix(screen::core::MatrixType type);
			void popMatrix(screen::core::MatrixType type);
			void setMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix);
			void multipleMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix);
			void getMatrix(screen::core::MatrixType type, glm::mat4x4& matrix);
			
			unsigned long convertColor(const screen::core::Color& color) const;
			const screen::core::Color& retrieveColor(unsigned long color) const;
			
			screen::core::BufferBase* createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const;
			screen::core::BufferBase* createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const; 
			void setVB(const screen::core::BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex, const screen::core::VertexFormat& vf);
			void setIB(const screen::core::BufferBase* buffer, unsigned long stride);

			void drawIndexedPrimitives(screen::core::PrimitiveType type, unsigned long firstIndex, unsigned long count) const;

			screen::core::objects::TextureBase* createTexture(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, screen::core::TextureFlag flags) const;
			void setTextureBase(unsigned int textureNumber, const screen::core::objects::TextureBase* texture);
		private:
			std::string openGLExtensions;
			bool capabilityTable[screen::core::NB_CAP];
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
