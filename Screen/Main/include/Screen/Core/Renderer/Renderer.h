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

#include <Screen/Utils/Plugin.h>
#include <Screen/Utils/Export.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Core/Color.h>
#include <Screen/Core/Objects/BufferBase.h>
#include <Screen/Core/Objects/VertexBuffer.h>
#include <Screen/Core/Objects/VertexBufferFiller.h>
#include <Screen/Core/Objects/IndexBuffer.h>
//#include <Screen/Core/Objects/IndexBufferFiller.h>
#include <Screen/Core/Objects/TextureBase.h>
#include <Screen/Core/Objects/Texture.h>
#include <Screen/Core/Renderer/RenderWindow.h>
#include <Screen/Core/Enums.h>
#include <Screen/Math/Matrix4x4f.h>
#include <Screen/Math/Vector2i.h>
#include <Screen/Utils/Declaration.h>

namespace Screen {
    namespace Core {
		using Screen::Core::Objects::VertexBuffer;
		using Screen::Core::Objects::VertexBufferFiller;
		using Screen::Core::Objects::IndexBuffer;
//		using Screen::Core::Objects::IndexBufferFiller;
		using Screen::Core::Objects::BufferBase;
		using Screen::Core::Objects::VertexFormat;
		using Screen::Core::Objects::Texture;
		using Screen::Core::Objects::TextureBase;
		
		class SCREEN_EXPORT Renderer {
			SCREEN_DECL_CLASS(Screen::Core::Renderer)
		public:
			Renderer();
			virtual ~Renderer();
			static void load(const std::string& fileName);
			static Renderer& get();
			static void destroy();
			
			virtual bool hasCapability(Screen::Core::ApiCapability caps) const = 0;

			virtual void pushMatrix(Screen::Core::MatrixType type) = 0;
			virtual void popMatrix(Screen::Core::MatrixType type) = 0;
			virtual void setMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix) = 0;
			virtual void multipleMatrix(Screen::Core::MatrixType type, const Screen::Math::Matrix4x4f& matrix) = 0;
			virtual void getMatrix(Screen::Core::MatrixType type, Screen::Math::Matrix4x4f& matrix) = 0;
			
			virtual unsigned long convertColor(const Color& color) const = 0;
			virtual const Color& retrieveColor(unsigned long color) const = 0;

			template <class T> inline VertexBuffer<T> createVertexBuffer(unsigned long size, Screen::Core::BufferFlag flags, const T* data, const VertexFormat::SmartPtr& vf) const;
			template <class T> inline VertexBuffer<T> createVertexBuffer(const VertexBufferFiller& vbf, Screen::Core::BufferFlag flags) const;
			template <class T> inline IndexBuffer<T> createIndexBuffer(unsigned long size, Screen::Core::BufferFlag flags, const T* data) const;
//			template <class T> inline IndexBuffer<T> createIndexBuffer(const IndexBufferFiller& ibf, Screen::Core::BufferFlag flags) const;
			template <class T> inline void setVertexBuffer(const VertexBuffer<T>& buffer, unsigned long minVertex = 0, unsigned long maxVertex = 0);
			template <class T> inline void setIndexBuffer(const IndexBuffer<T>& buffer);
	        
	        virtual void drawIndexedPrimitives(PrimitiveType type, unsigned long firstIndex, unsigned long count) const = 0;
	        
	        virtual TextureBase* createTexture(const Screen::Math::Vector2i& size, Screen::Core::PixelFormat pxf, Screen::Core::TextureFlag flags) const = 0;
			void setTexture(const Texture& texture);
	        
			void init();

			virtual void beginScene() = 0;
			virtual void endScene() = 0;
			
			bool isRunning();

			void setRenderWindow(Screen::Core::RenderWindow* renderWindow);
		protected:
			virtual BufferBase* createVB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const = 0;
	        virtual BufferBase* createIB(unsigned long size, unsigned long stride, Screen::Core::BufferFlag flags) const = 0;
	        
	        virtual void setVB(const BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const VertexFormat& vf) = 0;
	        virtual void setIB(const BufferBase* buffer, unsigned long stride) = 0;
	        
	        virtual void setTextureBase(const TextureBase* texture) = 0;
			
			Screen::Core::RenderWindow* renderWindow;
			
			virtual void initialize() = 0;
		private:
			static Renderer* renderer;
			static Screen::Utils::Plugin<Renderer> sharedLibrary;
		};
		
		//inline method body
		
		template <class T>
		inline VertexBuffer<T> Renderer::createVertexBuffer(unsigned long size, Screen::Core::BufferFlag flags, const T* data, const VertexFormat::SmartPtr& vf) const{
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
		inline VertexBuffer<T> Renderer::createVertexBuffer(const VertexBufferFiller& vbf, Screen::Core::BufferFlag flags) const{
			SCREEN_DECL_METHOD(createVertexBuffer)
			return createVertexBuffer(vbf.getSize(),flags,vbf.get<T>(),vbf.getVertexFormat());
		}

		template <class T>
		inline IndexBuffer<T> Renderer::createIndexBuffer(unsigned long size, Screen::Core::BufferFlag flags, const T* data) const{
			SCREEN_DECL_METHOD(createIndexBuffer)
			IndexBuffer<T> buffer(createIB(size, sizeof(T), flags));
		    if (data!=NULL)
		        buffer.fill(data, size);
		    return buffer;
		}
		
//		template <class T>
//		inline IndexBuffer<T> Renderer::createIndexBuffer(const IndexBufferFiller& ibf, Screen::Core::BufferFlag flags) const{
//			SCREEN_DECL_METHOD(createIndexBuffer)
//			return createIndexBuffer(ibf.getSize(),flags,ibf.get<T>());
//		}
		
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
