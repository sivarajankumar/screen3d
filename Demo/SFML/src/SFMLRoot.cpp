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

#include "SFMLRoot.h"

#include <screen/math/Vector2f.h>
#include <screen/utils/Timer.h>
#include <screen/core/renderer/Renderer.h>
#include <screen/core/renderer/RenderWindow.h>
#include <screen/utils/MediaManager.h>

#include <screen/core/objects/VertexBufferFiller.h>
#include <screen/core/objects/IndexBufferFiller.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.141592654f

SFMLRoot::SFMLRoot()
	:screen::core::Root()
{}

SFMLRoot::~SFMLRoot(){}

void SFMLRoot::init(){
	Root::init();
	
	using screen::core::objects::VertexFormat;

	screen::core::objects::IndexBufferFiller ibf1;
	ibf1.setAt(0,0);	ibf1.setAt(1,1);	ibf1.setAt(2,3);
	ibf1.setAt(3,1);	ibf1.setAt(4,2);	ibf1.setAt(5,3);
	ibf1.setAt(6,0);	ibf1.setAt(7,4);	ibf1.setAt(8,3);
	ibf1.setAt(9,4);	ibf1.setAt(10,7);	ibf1.setAt(11,3);
	ibf1.setAt(12,1);	ibf1.setAt(13,5);	ibf1.setAt(14,2);
	ibf1.setAt(15,5);	ibf1.setAt(16,6);	ibf1.setAt(17,2);
	ibf1.setAt(18,3);	ibf1.setAt(19,7);	ibf1.setAt(20,6);
	ibf1.setAt(21,3);	ibf1.setAt(22,6);	ibf1.setAt(23,2);
	ibf1.setAt(24,0);	ibf1.setAt(25,4);	ibf1.setAt(26,5);
	ibf1.setAt(27,0);	ibf1.setAt(28,5);	ibf1.setAt(29,1);
	ibf1.setAt(30,4);	ibf1.setAt(31,5);	ibf1.setAt(32,7);
	ibf1.setAt(33,5);	ibf1.setAt(34,6);	ibf1.setAt(35,7);

	
	VertexFormat::SmartPtr vf1(new VertexFormat());
	vf1->add(screen::core::VERTEX_USAGE_POSITION,screen::core::VERTEX_TYPE_FLOAT3);
	vf1->add(screen::core::VERTEX_USAGE_DIFFUSE,screen::core::VERTEX_TYPE_COLOR);
	vf1->add(screen::core::VERTEX_USAGE_TEXCOORD0,screen::core::VERTEX_TYPE_FLOAT2);
	vf1->lock();
	
	screen::core::objects::VertexBufferFiller vbf1(vf1);
	
	//set vextex points
	vbf1.setPositionAt(0,glm::vec3(-1.0f, -1.0f,  1.0f));
	vbf1.setPositionAt(1,glm::vec3(-1.0f,  1.0f,  1.0f));
	vbf1.setPositionAt(2,glm::vec3( 1.0f,  1.0f,  1.0f));
	vbf1.setPositionAt(3,glm::vec3( 1.0f, -1.0f,  1.0f));
	vbf1.setPositionAt(4,glm::vec3(-1.0f, -1.0f, -1.0f));
	vbf1.setPositionAt(5,glm::vec3(-1.0f,  1.0f, -1.0f));
	vbf1.setPositionAt(6,glm::vec3( 1.0f,  1.0f, -1.0f));
	vbf1.setPositionAt(7,glm::vec3( 1.0f, -1.0f, -1.0f));
	
	//set vextex colors
	vbf1.setDiffuseAt(0,0xFF0000FF);
	vbf1.setDiffuseAt(1,0xFFFF00FF);
	vbf1.setDiffuseAt(2,0xFFFFFF00);
	vbf1.setDiffuseAt(3,0xFFFF0000);
	vbf1.setDiffuseAt(4,0xFF00FFFF);
	vbf1.setDiffuseAt(5,0xFFFFFFFF);
	vbf1.setDiffuseAt(6,0xFF00FF00);
	vbf1.setDiffuseAt(7,0xFFFFC0C0);
	
	//set texture vextices
	vbf1.setTextureAt(0,0,glm::vec2(0.0f, 1.0f));
	vbf1.setTextureAt(1,0,glm::vec2(0.0f, 0.0f));
	vbf1.setTextureAt(2,0,glm::vec2(1.0f, 0.0f));
	vbf1.setTextureAt(3,0,glm::vec2(1.0f, 1.0f));
	vbf1.setTextureAt(4,0,glm::vec2(0.0f, 1.0f));
	vbf1.setTextureAt(5,0,glm::vec2(0.0f, 0.0f));
	vbf1.setTextureAt(6,0,glm::vec2(1.0f, 0.0f));
	vbf1.setTextureAt(7,0,glm::vec2(1.0f, 1.0f));
		
	vb1 = new screen::core::objects::VertexBuffer<Vertex>(
			renderer->createVertexBuffer<Vertex>(vbf1,screen::core::STATIC_DRAW));
	ib1 = new screen::core::objects::IndexBuffer<unsigned short>(
			renderer->createIndexBuffer<unsigned short>(ibf1,screen::core::STATIC_DRAW));

	texture.createFromFile("SCREEN.png", screen::core::PXF_A8R8G8B8);
	
        cam = glm::vec3(0.0f, 5.0f, 5.0f);
        view = glm::lookAt(cam, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        proj = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

}

bool SFMLRoot::renderFrame(){        
        glm::mat4 rotX = glm::rotate(
                    view,
                    (float)timer->getMilliseconds() * 0.05f,
                    glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotXY = glm::rotate(
                    rotX,
                    (float)timer->getMilliseconds() * 0.03f,
                    glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotXYZ = glm::rotate(
                    rotXY,
                    (float)timer->getMilliseconds() * 0.08f,
                    glm::vec3(0.0f, 0.0f, 1.0f));
        renderer->setMatrix(screen::core::MATRIX_VIEW, rotXYZ);
	renderer->setMatrix(screen::core::MATRIX_PROJECTION, proj);
	renderer->setTexture(texture);
	renderer->setVertexBuffer(*(vb1.get<Vertex>()));
	renderer->setIndexBuffer(*(ib1.get<unsigned short>()));
	renderer->drawIndexedPrimitives(screen::core::PRIMITIVE_TRIANGLELIST, 0, 12);
	
	return Root::renderFrame();
}
