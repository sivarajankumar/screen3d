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

#ifndef SCREEN_FAKE_RENDERER_H
#define SCREEN_FAKE_RENDERER_H

#include <Screen/Core/Renderer/Renderer.h>

namespace Screen {
	namespace Test {
		namespace Utils {
			using Screen::Core::Objects::VertexBuffer;
			using Screen::Core::Objects::IndexBuffer;
			using Screen::Core::Objects::BufferBase;
			using Screen::Core::Objects::VertexFormat;
			using Screen::Core::Objects::Texture;
			using Screen::Core::Objects::TextureBase;
			using Screen::Core::Color;
			using Screen::Core::PrimitiveType;
			
			class FakeRenderer : public Screen::Core::Renderer {
			public:
				FakeRenderer();
				virtual ~FakeRenderer();
				
				virtual bool hasCapability(Screen::Core::ApiCapability caps) const;
				
				virtual void pushMatrix(Screen::Core::MatrixType type);
				virtual void popMatrix(Screen::Core::MatrixType type);
				virtual void setMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix);
				virtual void multipleMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix);
				virtual void getMatrix(Screen::Core::MatrixType type, Screen::Math::Matrix4x4f& matrix);
				
				virtual unsigned long convertColor(const Color& color) const;
				virtual const Screen::Core::Color& retrieveColor(unsigned long color) const;
				
				virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long firstIndex, unsigned long count) const;
					        
		        virtual TextureBase* createTexture(const Screen::Math::Vector2i& size, Screen::Core::PixelFormat pxf, Screen::Core::TextureFlag flags) const;
				
				virtual void beginScene();
				virtual void endScene();
				
				virtual BufferBase* createVB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const;
		        virtual BufferBase* createIB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const;
		        
		        virtual void setVB(const BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const VertexFormat& vf);
		        virtual void setIB(const BufferBase* buffer, unsigned long stride);
		        
		        virtual void setTextureBase(const TextureBase* texture);
		        
		        virtual void initialize();
			private:
			};
		}
	}
}

#endif
