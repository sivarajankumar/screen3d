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

#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H

#include <screen/utils/Plugin.h>
#include <screen/main/Export.h>
#include <screen/utils/SmartPtr.h>
#include <screen/core/Color.h>
#include <screen/core/objects/BufferBase.h>
#include <screen/core/objects/VertexBuffer.h>
#include <screen/core/objects/VertexBufferFiller.h>
#include <screen/core/objects/IndexBuffer.h>
#include <screen/core/objects/IndexBufferFiller.h>
#include <screen/core/objects/TextureBase.h>
#include <screen/core/objects/Texture.h>
#include <screen/core/renderer/RenderWindow.h>
#include <screen/core/Enums.h>
#include <glm/glm.hpp>
#include <screen/math/Vector2i.h>
#include <screen/utils/Declaration.h>

namespace screen {
    namespace core {
		using screen::core::objects::VertexBuffer;
		using screen::core::objects::VertexBufferFiller;
		using screen::core::objects::IndexBuffer;
		using screen::core::objects::IndexBufferFiller;
		using screen::core::objects::BufferBase;
		using screen::core::objects::VertexFormat;
		using screen::core::objects::Texture;
		using screen::core::objects::TextureBase;
		
		class SCREEN_MAIN_EXPORT Renderer {
			SCREEN_DECL_CLASS(screen::core::Renderer)
		public:
			Renderer();
			virtual ~Renderer();
			static void load(const std::string& fileName);
			static Renderer* get();
			static void destroy();
			
			virtual bool hasCapability(screen::core::ApiCapability caps) const = 0;

			virtual void pushMatrix(screen::core::MatrixType type) = 0;
			virtual void popMatrix(screen::core::MatrixType type) = 0;
			virtual void setMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix) = 0;
			virtual void multipleMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix) = 0;
			virtual void getMatrix(screen::core::MatrixType type, glm::mat4x4& matrix) = 0;
			
			virtual unsigned long convertColor(const Color& color) const = 0;
			virtual const Color& retrieveColor(unsigned long color) const = 0;

			template <class T> inline VertexBuffer<T> createVertexBuffer(unsigned long size, screen::core::BufferFlag flags, const T* data, const VertexFormat::SmartPtr& vf) const;
			template <class T> inline VertexBuffer<T> createVertexBuffer(const VertexBufferFiller& vbf, screen::core::BufferFlag flags) const;
			template <class T> inline IndexBuffer<T> createIndexBuffer(unsigned long size, screen::core::BufferFlag flags, const T* data) const;
			template <class T> inline IndexBuffer<T> createIndexBuffer(const IndexBufferFiller& ibf, screen::core::BufferFlag flags) const;
			template <class T> inline void setVertexBuffer(const VertexBuffer<T>& buffer, unsigned long minVertex = 0, unsigned long maxVertex = 0);
			template <class T> inline void setIndexBuffer(const IndexBuffer<T>& buffer);
	        
	        virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long firstIndex, unsigned long count) const = 0;
	        
	        virtual TextureBase* createTexture(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, screen::core::TextureFlag flags) const = 0;
			void setTexture(unsigned int textureNumber, const Texture& texture);
	        
			void init();

			virtual void beginScene() = 0;
			virtual void endScene() = 0;
			
			bool isRunning();

			void setRenderWindow(screen::core::RenderWindow* renderWindow);
		protected:
			virtual BufferBase* createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const = 0;
	        virtual BufferBase* createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const = 0;
	        
	        virtual void setVB(const BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const VertexFormat& vf) = 0;
	        virtual void setIB(const BufferBase* buffer, unsigned long stride) = 0;
	        
			virtual void setTextureBase(unsigned int textureNumber, const TextureBase* texture) = 0;
			
			screen::core::RenderWindow* renderWindow;
			
			virtual void initialize() = 0;
		private:
			static Renderer* renderer;
			static screen::utils::Plugin<Renderer> sharedLibrary;
		};
		
		//inline method body
		
		template <class T>
		inline VertexBuffer<T> Renderer::createVertexBuffer(unsigned long size, screen::core::BufferFlag flags, const T* data, const VertexFormat::SmartPtr& vf) const{
			SCREEN_DECL_METHOD(createVertexBuffer)
			if(!vf->isLocked()){
				SCREEN_LOG_WARNING("Vertex format isn't locked while creating a VertexBuffer => forced lock")
				VertexFormat& fmt = const_cast<VertexFormat&>(*(vf.get()));
				fmt.lock();
			}
			VertexBuffer<T> buffer(createVB(size, vf->getSize(), flags),vf);
		    if (data!=NULL)
		        buffer.fill(data, size);
		    return buffer;
		}
		
		template <class T>
		inline VertexBuffer<T> Renderer::createVertexBuffer(const VertexBufferFiller& vbf, screen::core::BufferFlag flags) const{
			SCREEN_DECL_METHOD(createVertexBuffer)
			return createVertexBuffer(vbf.getSize(),flags,vbf.get<T>(),vbf.getVertexFormat());
		}

		template <class T>
		inline IndexBuffer<T> Renderer::createIndexBuffer(unsigned long size, screen::core::BufferFlag flags, const T* data) const{
			SCREEN_DECL_METHOD(createIndexBuffer)
			IndexBuffer<T> buffer(createIB(size, sizeof(T), flags));
		    if (data!=NULL)
		        buffer.fill(data, size);
		    return buffer;
		}
		
		template <class T>
		inline IndexBuffer<T> Renderer::createIndexBuffer(const IndexBufferFiller& ibf, screen::core::BufferFlag flags) const{
			SCREEN_DECL_METHOD(createIndexBuffer)
			return createIndexBuffer(ibf.getSize(),flags,ibf.get<T>());
		}
		
		template <class T>
		inline void Renderer::setVertexBuffer(const VertexBuffer<T>& buffer, unsigned long minVertex, unsigned long maxVertex){
			SCREEN_DECL_METHOD(setVertexBuffer)
		    setVB(buffer.getBuffer(), buffer.getElementSize(), minVertex, (maxVertex!=0) ? maxVertex : buffer.getCount() - 1, *(buffer.getVertexFormat()));
		}
		
		template <class T>
		inline void Renderer::setIndexBuffer(const IndexBuffer<T>& buffer){
		    SCREEN_DECL_METHOD(setIndexBuffer)
			setIB(buffer.getBuffer(), sizeof(T));
		}
    }
}

#endif
