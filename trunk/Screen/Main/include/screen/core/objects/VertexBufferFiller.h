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

#ifndef SCREEN_VERTEX_BUFFER_FILLER_H
#define SCREEN_VERTEX_BUFFER_FILLER_H

#include <screen/core/objects/VertexFormat.h>
#include <screen/utils/SmartPtr.h>
#include <screen/core/Enums.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>
#include <glm/glm.hpp>
#include <vector>

namespace screen{
	namespace math{
		class Vector2f;
		class Vector3f;
	}
	namespace core{
		class Color;
		namespace objects{
			class SCREEN_MAIN_EXPORT VertexBufferFiller{
				SCREEN_DECL_CLASS(screen::core::objects::VertexBufferFiller)
			public:
				VertexBufferFiller(const VertexFormat::SmartPtr& vf);
				~VertexBufferFiller();
				
                                void setPositionAt(unsigned int i, const glm::vec3& vector);
                                void setNormalAt(unsigned int i, const glm::vec3& vector);
				void setDiffuseAt(unsigned int i, const screen::core::Color& color);
                                void setTextureAt(unsigned int i, unsigned int textureNumber, const glm::vec2& vector);
				
                                void getPositionAt(unsigned int i, glm::vec3& vector) const;
                                void getNormalAt(unsigned int i, glm::vec3& vector) const;
				void getDiffuseAt(unsigned int i, screen::core::Color& color) const;
                                void getTextureAt(unsigned int i, unsigned int textureNumber, glm::vec2& vector) const;
				
				template <class T>
				const T* get() const;
				unsigned int getSize() const;
				
				const VertexFormat::SmartPtr& getVertexFormat() const;
				
				typedef screen::utils::SmartPtr<VertexBufferFiller> SmartPtr;
			private:
				VertexFormat::SmartPtr vf;
				typedef int VertexInfoPosition;
				typedef int VertexInfoSize;
				typedef std::pair<VertexInfoPosition,VertexInfoSize> VertexInfo;
				VertexInfo vertexInfo[screen::core::NB_VERTEX_USAGE];
				unsigned int stepSize;
				screen::memory::TypedBuffer<unsigned long> buffer;
			};
			
			template <class T>
			const T* VertexBufferFiller::get() const{
				SCREEN_DECL_METHOD(get)
#ifdef SCREEN_AUTHORIZE_LOG_DEBUG
				SCREEN_LOG_DEBUG("buffer");
				std::stringstream s;
				s << "|";
				const unsigned long* bufferContent = buffer.getAt(0);
				size_t size = buffer.size();
				for(int i=0; i<size; i++){
					s << bufferContent[i] << "|";
				}
				SCREEN_LOG_DEBUG(s.str());
#endif
				return reinterpret_cast<const T*>(buffer.getAt(0));
			}
		}
	}
}

#endif

