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

#ifndef SCREEN_FAKE_RENDERER_H
#define SCREEN_FAKE_RENDERER_H

#include <screen/core/renderer/Renderer.h>

namespace screen {
	namespace test {
		namespace utils {
			using screen::core::objects::VertexBuffer;
			using screen::core::objects::IndexBuffer;
			using screen::core::objects::BufferBase;
			using screen::core::objects::VertexFormat;
			using screen::core::objects::Texture;
			using screen::core::objects::TextureBase;
			using screen::core::Color;
			using screen::core::PrimitiveType;
			
			class FakeRenderer : public screen::core::Renderer {
			public:
				FakeRenderer();
				virtual ~FakeRenderer();
				
				virtual bool hasCapability(screen::core::ApiCapability caps) const;
				
				virtual void pushMatrix(screen::core::MatrixType type);
				virtual void popMatrix(screen::core::MatrixType type);
				virtual void setMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix);
				virtual void multipleMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix);
				virtual void getMatrix(screen::core::MatrixType type, glm::mat4x4& matrix);
				
				virtual unsigned long convertColor(const Color& color) const;
				virtual const screen::core::Color& retrieveColor(unsigned long color) const;
				
				virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long firstIndex, unsigned long count) const;
					        
				virtual TextureBase* createTexture(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, screen::core::TextureFlag flags) const;
				
				virtual void beginScene();
				virtual void endScene();
				
				virtual BufferBase* createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const;
				virtual BufferBase* createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const;

				virtual void setVB(const BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const VertexFormat& vf);
				virtual void setIB(const BufferBase* buffer, unsigned long stride);

				virtual void setTextureBase(unsigned int textureNumber, const TextureBase* texture);

				virtual void initialize();
			private:
			};
		}
	}
}

#endif
