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

#include <screen/Test/utils/FakeRenderer.h>

namespace screen {
	namespace Test {
		namespace utils {
			FakeRenderer::FakeRenderer(){}
			FakeRenderer::~FakeRenderer(){}
			bool FakeRenderer::hasCapability(screen::core::ApiCapability caps) const{return true;}
			void FakeRenderer::pushMatrix(screen::core::MatrixType type){}
			void FakeRenderer::popMatrix(screen::core::MatrixType type){}
			void FakeRenderer::setMatrix(screen::core::MatrixType type, const screen::math::Matrix4x4f& matrix){}
			void FakeRenderer::multipleMatrix(screen::core::MatrixType type, const screen::math::Matrix4x4f& matrix){}
			void FakeRenderer::getMatrix(screen::core::MatrixType type, screen::math::Matrix4x4f& matrix){}
			unsigned long FakeRenderer::convertColor(const Color& color) const{return 0;}
			const screen::core::Color& FakeRenderer::retrieveColor(unsigned long color) const{static screen::core::Color c; return c;}
			void FakeRenderer::drawIndexedPrimitives(PrimitiveType type, unsigned long firstIndex, unsigned long count) const{}
	        TextureBase* FakeRenderer::createTexture(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, screen::core::TextureFlag flags) const{return NULL;}
			void FakeRenderer::beginScene(){}
			void FakeRenderer::endScene(){}
			BufferBase* FakeRenderer::createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{return NULL;}
	        BufferBase* FakeRenderer::createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{return NULL;}
	        void FakeRenderer::setVB(const BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const VertexFormat& vf){}
	        void FakeRenderer::setIB(const BufferBase* buffer, unsigned long stride){}
	        void FakeRenderer::setTextureBase(const TextureBase* texture){}
	        void FakeRenderer::initialize(){}
		}
	}
}
