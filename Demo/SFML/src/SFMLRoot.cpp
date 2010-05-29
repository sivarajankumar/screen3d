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

#include <Screen/Math/Vector2f.h>
#include <Screen/Utils/Timer.h>
#include <Screen/Core/Renderer/Renderer.h>
#include <Screen/Core/Renderer/RenderWindow.h>
#include <Screen/Utils/MediaManager.h>

#define PI 3.141592654f

SFMLRoot::SFMLRoot()
	:Screen::Core::Root()
{}

void SFMLRoot::init(){
	Root::init();
	
	using Screen::Core::Objects::VertexFormat;
	// Création des vertices et des indices
//	static Vertex vertices[] =
//	{
//		{-1.0f, -1.0f,  1.0f, renderer->convertColor(0xFF0000FF), 0.0f, 1.0f},
//		{-1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFF00FF), 0.0f, 0.0f},
//		{ 1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFFFF00), 1.0f, 0.0f},
//		{ 1.0f, -1.0f,  1.0f, renderer->convertColor(0xFFFF0000), 1.0f, 1.0f},
//		{-1.0f, -1.0f, -1.0f, renderer->convertColor(0xFF00FFFF), 0.0f, 1.0f},
//		{-1.0f,  1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 0.0f},
//		{ 1.0f,  1.0f, -1.0f, renderer->convertColor(0xFF00FF00), 1.0f, 0.0f},
//		{ 1.0f, -1.0f, -1.0f, renderer->convertColor(0xFFFFC0C0), 1.0f, 1.0f}
//	};

	static unsigned short indices[] =
	{
		0, 1, 3,
		1, 2, 3,
		0, 4, 3,
		4, 7, 3,
		1, 5, 2,
		5, 6, 2,
		3, 7, 6,
		3, 6, 2,
		0, 4, 5,
		0, 5, 1,
		4, 5, 7,
		5, 6, 7
	};
	
	VertexFormat::SmartPtr vf1(new VertexFormat());
	vf1->add(Screen::Core::VERTEX_USAGE_POSITION,Screen::Core::VERTEX_TYPE_FLOAT3);
	vf1->add(Screen::Core::VERTEX_USAGE_DIFFUSE,Screen::Core::VERTEX_TYPE_COLOR);
	vf1->add(Screen::Core::VERTEX_USAGE_TEXCOORD0,Screen::Core::VERTEX_TYPE_FLOAT2);
	vf1->lock();
	
	Screen::Core::Objects::VertexBufferFiller vbf1(vf1);
	
	//set vextex points
	vbf1.setPositionAt(0,Screen::Math::Vector3f(-1.0f, -1.0f,  1.0f));
	vbf1.setPositionAt(1,Screen::Math::Vector3f(-1.0f,  1.0f,  1.0f));
	vbf1.setPositionAt(2,Screen::Math::Vector3f( 1.0f,  1.0f,  1.0f));
	vbf1.setPositionAt(3,Screen::Math::Vector3f( 1.0f, -1.0f,  1.0f));
	vbf1.setPositionAt(4,Screen::Math::Vector3f(-1.0f, -1.0f, -1.0f));
	vbf1.setPositionAt(5,Screen::Math::Vector3f(-1.0f,  1.0f, -1.0f));
	vbf1.setPositionAt(6,Screen::Math::Vector3f( 1.0f,  1.0f, -1.0f));
	vbf1.setPositionAt(7,Screen::Math::Vector3f( 1.0f, -1.0f, -1.0f));
	
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
	vbf1.setTextureAt(0,0,Screen::Math::Vector2f(0.0f, 1.0f));
	vbf1.setTextureAt(1,0,Screen::Math::Vector2f(0.0f, 0.0f));
	vbf1.setTextureAt(2,0,Screen::Math::Vector2f(1.0f, 0.0f));
	vbf1.setTextureAt(3,0,Screen::Math::Vector2f(1.0f, 1.0f));
	vbf1.setTextureAt(4,0,Screen::Math::Vector2f(0.0f, 1.0f));
	vbf1.setTextureAt(5,0,Screen::Math::Vector2f(0.0f, 0.0f));
	vbf1.setTextureAt(6,0,Screen::Math::Vector2f(1.0f, 0.0f));
	vbf1.setTextureAt(7,0,Screen::Math::Vector2f(1.0f, 1.0f));
	
//	vb1 = new Screen::Core::Objects::VertexBuffer<Vertex>(
//			renderer->createVertexBuffer<Vertex>(vbf1->getSize(),Screen::Core::STATIC_DRAW,vbf1->get<Vertex>(),vf1));
//	ib = new Screen::Core::Objects::IndexBuffer<unsigned short>(
//			renderer->createIndexBuffer(12*3,Screen::Core::STATIC_DRAW,indices));
	
	vb1 = new Screen::Core::Objects::VertexBuffer<Vertex>(
			renderer->createVertexBuffer<Vertex>(vbf1,Screen::Core::STATIC_DRAW));
	ib = new Screen::Core::Objects::IndexBuffer<unsigned short>(
			renderer->createIndexBuffer(12*3,Screen::Core::STATIC_DRAW,indices));

	texture.createFromFile("SCREEN.png", Screen::Core::PXF_A8R8G8B8);
	
	cam.set(0.0f, 2.5f, 2.5f);
	view.lookAt(cam, cam + Screen::Math::Vector3f(0.0f, -1.0f, -1.0f));
	proj.perspectiveFOV(PI/2, 800.0f / 600.0f, 0.1f, 1000.0f);

}

bool SFMLRoot::renderFrame(){
	rotX.setRotationX((float)timer->getMilliseconds() * 0.05f / 180 * PI);
	rotY.setRotationY((float)timer->getMilliseconds() * 0.03f / 180 * PI);
	rotZ.setRotationZ((float)timer->getMilliseconds() * 0.09f / 180 * PI);
	renderer->setMatrix(Screen::Core::MATRIX_VIEW, (rotX*rotY*rotZ*view));
	renderer->setMatrix(Screen::Core::MATRIX_PROJECTION, proj);
	renderer->setTexture(texture);
	renderer->setVertexBuffer(*(vb1.get<Vertex>()));
	renderer->setIndexBuffer(*ib);
	renderer->drawIndexedPrimitives(Screen::Core::PRIMITIVE_TRIANGLELIST, 0, 12);
	
	return Root::renderFrame();
}
