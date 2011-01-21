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

#ifndef SCREEN_VERTEX_BUFFER_H
#define SCREEN_VERTEX_BUFFER_H

#include <screen/core/objects/Buffer.h>
#include <screen/core/objects/VertexFormat.h>
#include <screen/utils/SmartPtr.h>
#include <screen/utils/Exception.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>
#include <screen/utils/Exception.h>
#include <string>

#define CHECK_VERTEX_FORMAT(vf,T) \
	if(sizeof(T) != vf->getSize()){ \
		std::stringstream ss; \
		ss << "different size between vertex element type and vertex format size\n" \
		   << "\t- Element type size = " << sizeof(T) << "\n" \
		   << "\t- Vertex format size = " << vf->getSize() << "\n"; \
		throw screen::utils::Exception(ss.str()); \
	}

namespace screen {
	namespace core {
		namespace objects {
			/*!  \class VertexBuffer
			 *   \brief 
			 *   \author Ratouit Thomas
			 *   \date 19 sept. 09
			 */
			
			template <class T>
			class VertexBuffer : public Buffer<T> {
				SCREEN_DECL_CLASS(screen::core::Object::VertexBuffer)
			public:
				VertexBuffer(BufferBase* buffer, const VertexFormat::SmartPtr& vf)
					:Buffer<T>(buffer),vf(vf){
					SCREEN_DECL_CONSTRUCTOR(VertexBuffer)
					CHECK_VERTEX_FORMAT(vf,T);
				}
				
				~VertexBuffer(){
					SCREEN_DECL_DESTRUCTOR(~VertexBuffer)
				}
								
				const VertexFormat::SmartPtr& getVertexFormat() const{
					SCREEN_DECL_METHOD(getVertexFormat)
					return vf;
				}
				
				typedef screen::utils::SmartPtr<VertexBuffer<T> > SmartPtr;
			private:
				VertexFormat::SmartPtr vf;
			};
			
			template <>
			class VertexBuffer<void> : public Buffer<void> {
				SCREEN_DECL_CLASS(screen::core::Object::VertexBuffer)
			public:
				VertexBuffer(BufferBase* buffer, const VertexFormat::SmartPtr& vf)
					:Buffer<void>(buffer,vf->getSize()),vf(vf){
					SCREEN_DECL_CONSTRUCTOR(VertexBuffer)
				}
				
				~VertexBuffer(){
					SCREEN_DECL_DESTRUCTOR(~VertexBuffer)
				}
				
				const VertexFormat::SmartPtr& getVertexFormat() const{
					SCREEN_DECL_METHOD(getVertexFormat)
					return vf;
				}
				
				typedef screen::utils::SmartPtr<VertexBuffer<void> > SmartPtr;
			private:
				VertexFormat::SmartPtr vf;
			};
		}
	}
}

#undef CHECK_VERTEX_FORMAT

#endif
