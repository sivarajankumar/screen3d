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

#ifndef SCREEN_VERTEX_BUFFER_FILLER_H
#define SCREEN_VERTEX_BUFFER_FILLER_H

#include <Screen/Core/Objects/VertexFormat.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Core/Enums.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>
#include <vector>

namespace Screen{
	namespace Math{
		class Vector2f;
		class Vector3f;
	}
	namespace Core{
		class Color;
		namespace Objects{
			class SCREEN_EXPORT VertexBufferFiller{
				SCREEN_DECL_CLASS(Screen::Core::Objects::VertexBufferFiller)
			public:
				VertexBufferFiller(const VertexFormat::SmartPtr& vf);
				~VertexBufferFiller();
				
				void setPositionAt(unsigned int i, const Screen::Math::Vector3f& vector);
				void setNormalAt(unsigned int i, const Screen::Math::Vector3f& vector);
				void setDiffuseAt(unsigned int i, const Screen::Core::Color& color);
				void setTextureAt(unsigned int i, unsigned int textureNumber, const Screen::Math::Vector2f& vector);
				
				void getPositionAt(unsigned int i, Screen::Math::Vector3f& vector) const;
				void getNormalAt(unsigned int i, Screen::Math::Vector3f& vector) const;
				void getDiffuseAt(unsigned int i, Screen::Core::Color& color) const;
				void getTextureAt(unsigned int i, unsigned int textureNumber, Screen::Math::Vector2f& vector) const;
				
				template <class T>
				const T* get() const;
				unsigned int getSize() const;
				
				const VertexFormat::SmartPtr& getVertexFormat() const;
				
				typedef Screen::Utils::SmartPtr<VertexBufferFiller> SmartPtr;
			private:
				VertexFormat::SmartPtr vf;
				typedef int VertexInfoPosition;
				typedef int VertexInfoSize;
				typedef std::pair<VertexInfoPosition,VertexInfoSize> VertexInfo;
				VertexInfo vertexInfo[Screen::Core::NB_VERTEX_USAGE];
				unsigned int stepSize;
				std::vector<unsigned long> buffer;
				unsigned int bufferSize;
			};
			
			template <class T>
			const T* VertexBufferFiller::get() const{
				SCREEN_DECL_METHOD(get)
#ifdef SCREEN_AUTHORIZE_LOG_DEBUG
				SCREEN_LOG_DEBUG("buffer");
				std::stringstream s;
				s << "|";
				for(int i=0; i<buffer.size(); i++){
					s << buffer[i] << "|";
				}
				SCREEN_LOG_DEBUG(s.str());
#endif
				return reinterpret_cast<const T*>(&buffer[0]);
			}
		}
	}
}

#endif

