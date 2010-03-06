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

#include <Screen/Core/Objects/VertexBufferFiller.h>
#include <Screen/Core/Renderer/Renderer.h>
#include <Screen/Core/Color.h>
#include <Screen/Math/Vector2f.h>
#include <Screen/Math/Vector3f.h>

const unsigned int vertexTypeSize[Screen::Core::NB_VERTEX_TYPE] = {1,2,3,4,1};

#define BUFFER_MIN_SIZE 10

namespace Screen{
	namespace Core{
		namespace Objects{
			VertexBufferFiller::VertexBufferFiller(const VertexFormat::SmartPtr& vf)
				:vf(vf),buffer(BUFFER_MIN_SIZE,0){
				SCREEN_DECL_CONSTRUCTOR(VertexBufferFiller)
				//fill table with position and size of the usage
				for(unsigned int i=0; i<Screen::Core::NB_VERTEX_USAGE; i++){
					vertexInfo[i].first = -1;
					vertexInfo[i].second = -1;
				}
				unsigned int currentPosition = 0;
				for (Screen::Core::Objects::VertexFormat::const_iterator it = vf->begin(); it != vf->end(); ++it){
					vertexInfo[(*it)->getUsage()].first = currentPosition;
					vertexInfo[(*it)->getUsage()].second = vertexTypeSize[(*it)->getType()];
					currentPosition += vertexTypeSize[(*it)->getType()];
				}
				stepSize = currentPosition;
#ifdef SCREEN_AUTHORIZE_LOG_DEBUG
				SCREEN_LOG_DEBUG("VertexBufferFiller / vertexInfo table :");
				SCREEN_LOG_DEBUG("step size = " << stepSize);
				for(unsigned int i=0; i<Screen::Core::NB_VERTEX_USAGE; i++){
					SCREEN_LOG_DEBUG("[ " << vertexInfo[i].first << " / " << vertexInfo[i].second << " ]");
				}
#endif
			}
			
			VertexBufferFiller::~VertexBufferFiller(){
				SCREEN_DECL_DESTRUCTOR(VertexBufferFiller)
			}
			
#define SET_VECTOR(vertexUsage,inputSize) \
	unsigned int cur = i*stepSize + vertexInfo[vertexUsage].first; \
	if(cur+vertexInfo[vertexUsage].second>buffer.size()){ \
		SCREEN_LOG_DEBUG("resize vextex buffer"); \
		buffer.resize(buffer.size()*2,0); \
	} \
	for(int j=0; j<vertexInfo[vertexUsage].second; j++){ \
		unsigned long val = 0; \
		SCREEN_LOG_DEBUG("current buffer assignment = " << cur+j); \
		::memcpy(&val,&vector(j),sizeof(unsigned long)); \
		SCREEN_LOG_DEBUG("|" << val << "|" << vector(j) << "|"); \
		buffer[cur+j] = val; \
	} \
	bufferSize = std::max(bufferSize,i+1);
			
#define GET_VECTOR(vertexUsage,inputSize) \
	unsigned int cur = i*stepSize + vertexInfo[vertexUsage].first; \
	for(unsigned int j=0; j<vertexInfo[vertexUsage].second; j++){ \
		float val; \
		::memcpy(&val,&buffer[cur+j],sizeof(float)); \
		vector(j) = val; \
	}
			
#define SET_COLOR(vertexUsage) \
	unsigned int cur = i*stepSize + vertexInfo[vertexUsage].first; \
	if(cur+vertexInfo[vertexUsage].second>buffer.size()){ \
		SCREEN_LOG_DEBUG("resize vextex buffer"); \
		buffer.resize(buffer.size()*2,0); \
	} \
	SCREEN_LOG_DEBUG("current buffer assignment = " << cur); \
	buffer[cur] = Renderer::get().convertColor(color); \
	SCREEN_LOG_DEBUG("|" << color.convertABGR() << "|"); \
	bufferSize = std::max(bufferSize,i+1);

#define GET_COLOR(vertexUsage) \
	unsigned int cur = i*stepSize + vertexInfo[vertexUsage].first; \
	color = Renderer::get().retrieveColor(buffer[cur]);
			
			void VertexBufferFiller::setPositionAt(unsigned int i, const Screen::Math::Vector3f& vector){
				SCREEN_DECL_METHOD(setPositionAt)
				SET_VECTOR(Screen::Core::VERTEX_USAGE_POSITION,3);
			}
			void VertexBufferFiller::setNormalAt(unsigned int i, const Screen::Math::Vector3f& vector){
				SCREEN_DECL_METHOD(setNormalAt)
				SET_VECTOR(Screen::Core::VERTEX_USAGE_NORMAL,3);
			}
			void VertexBufferFiller::setDiffuseAt(unsigned int i, const Screen::Core::Color& color){
				SCREEN_DECL_METHOD(setDiffuseAt)
				SET_COLOR(Screen::Core::VERTEX_USAGE_DIFFUSE);
			}
			void VertexBufferFiller::setTextureAt(unsigned int i, unsigned int textureNumber, const Screen::Math::Vector2f& vector){
				SCREEN_DECL_METHOD(setTextureAt)
				SET_VECTOR(Screen::Core::VERTEX_USAGE_TEXCOORD0 + textureNumber,2);
			}
			
			void VertexBufferFiller::getPositionAt(unsigned int i, Screen::Math::Vector3f& vector) const{
				SCREEN_DECL_METHOD(getPositionAt)
				GET_VECTOR(Screen::Core::VERTEX_USAGE_POSITION,3);
			}
			void VertexBufferFiller::getNormalAt(unsigned int i, Screen::Math::Vector3f& vector) const{
				SCREEN_DECL_METHOD(getNormalAt)
				GET_VECTOR(Screen::Core::VERTEX_USAGE_NORMAL,3);
			}
			void VertexBufferFiller::getDiffuseAt(unsigned int i, Screen::Core::Color& color) const{
				SCREEN_DECL_METHOD(getDiffuseAt)
				GET_COLOR(Screen::Core::VERTEX_USAGE_DIFFUSE);
			}
			void VertexBufferFiller::getTextureAt(unsigned int i, unsigned int textureNumber, Screen::Math::Vector2f& vector) const{
				SCREEN_DECL_METHOD(getTextureAt)
				GET_VECTOR(Screen::Core::VERTEX_USAGE_TEXCOORD0 + textureNumber,2);
			}
			
			unsigned int VertexBufferFiller::getSize() const{
				SCREEN_DECL_METHOD(getSize)
				SCREEN_LOG_DEBUG("Vertex buffer size = " << bufferSize);
				return bufferSize;
			}
			
			const VertexFormat::SmartPtr& VertexBufferFiller::getVertexFormat() const{
				SCREEN_DECL_METHOD(getVertexFormat)
				return vf;
			}
		}
	}
}
