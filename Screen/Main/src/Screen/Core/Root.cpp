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

#include <Screen/Core/Root.h>
#include <Screen/Core/Timer.h>
#include <Screen/Core/FPSCounter.h>
#include <Screen/Core/Renderer/Renderer.h>
#include <Screen/Core/Renderer/RenderWindow.h>
#include <Screen/Utils/MediaManager.h>

#include <iostream>

#define PI 3.141592654f

Screen::Core::Root::Root()
	:timer(new Timer()), renderer(NULL), renderWindow(NULL){
	SCREEN_DECL_CONSTRUCTOR(Root)
}

Screen::Core::Root::~Root() {
	SCREEN_DECL_DESTRUCTOR(~Root)
	if(renderer!=NULL)
		renderer->destroy();
    delete timer;
}

void Screen::Core::Root::setRenderWindow(Screen::Core::RenderWindow* renderWindow){
	SCREEN_DECL_METHOD(setRenderWindow)
	this->renderWindow = renderWindow;
}

void Screen::Core::Root::setFPSCounter(Screen::Core::FPSCounter* fpsCounter){
	SCREEN_DECL_METHOD(setFPSCounter)
	this->fpsCounter = fpsCounter;
}

void Screen::Core::Root::startRendering() const {
	using Screen::Core::Objects::VertexFormat;
	SCREEN_DECL_METHOD(startRendering)
	// Création des vertices et des indices
	TVertex1 Vertices1[] =
	{
//		{-1.0f, -1.0f,  1.0f, renderer->convertColor(0xFF0000FF), 0.0f, 1.0f},
//		{-1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFF00FF), 0.0f, 0.0f},
//		{ 1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFFFF00), 1.0f, 0.0f},
//		{ 1.0f, -1.0f,  1.0f, renderer->convertColor(0xFFFF0000), 1.0f, 1.0f},
//		{-1.0f, -1.0f, -1.0f, renderer->convertColor(0xFF00FFFF), 0.0f, 1.0f},
//		{-1.0f,  1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 0.0f},
//		{ 1.0f,  1.0f, -1.0f, renderer->convertColor(0xFF00FF00), 1.0f, 0.0f},
//		{ 1.0f, -1.0f, -1.0f, renderer->convertColor(0xFFFFC0C0), 1.0f, 1.0f}
		{-1.0f, -1.0f,  1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 1.0f},
		{-1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 0.0f},
		{ 1.0f,  1.0f,  1.0f, renderer->convertColor(0xFFFFFFFF), 1.0f, 0.0f},
		{ 1.0f, -1.0f,  1.0f, renderer->convertColor(0xFFFFFFFF), 1.0f, 1.0f},
		{-1.0f, -1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 1.0f},
		{-1.0f,  1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 0.0f, 0.0f},
		{ 1.0f,  1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 1.0f, 0.0f},
		{ 1.0f, -1.0f, -1.0f, renderer->convertColor(0xFFFFFFFF), 1.0f, 1.0f}
	};

	unsigned short Indices[] =
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
	vf1->add(VERTEX_USAGE_POSITION,VERTEX_TYPE_FLOAT3);
	vf1->add(VERTEX_USAGE_DIFFUSE,VERTEX_TYPE_COLOR);
	vf1->add(VERTEX_USAGE_TEXCOORD0,VERTEX_TYPE_FLOAT2);
	vf1->lock();
	VertexBuffer<TVertex1> vb1 = renderer->createVertexBuffer<TVertex1>(8,STATIC_DRAW,Vertices1,vf1);
	//VertexBuffer<void> vb1 = renderer->createVertexBuffer<void>(8,STATIC_DRAW,Vertices1,vf1);
	IndexBuffer<unsigned short> ib = renderer->createIndexBuffer(12*3,STATIC_DRAW,Indices);
	Screen::Core::Objects::Texture texture;
	texture.createFromFile("SCREEN.png", Screen::Core::PXF_A8R8G8B8);
	
	
	Screen::Math::Vector3f cam;
	Screen::Math::Matrix4x4f view,proj,rotX,rotY,rotZ;
	cam.set(0.0f, 2.5f, 2.5f);
	view.lookAt(cam, cam + Screen::Math::Vector3f(0.0f, -1.0f, -1.0f));
	proj.perspectiveFOV(PI/2, 800.0f / 600.0f, 0.1f, 1000.0f);
	
//    while(true) {
//        if(!renderFrame())
//            break;
//        fpsCounter->count();
//    }
	while(renderer->isRunning()){
		rotX.setRotationX((float)timer->getMilliseconds() * 0.05f / 180 * PI);
		rotY.setRotationY((float)timer->getMilliseconds() * 0.03f / 180 * PI);
		rotZ.setRotationZ((float)timer->getMilliseconds() * 0.09f / 180 * PI);
		renderer->beginScene();
		renderer->setMatrix(Screen::Core::MATRIX_VIEW, (rotX*rotY*rotZ*view));
		renderer->setMatrix(Screen::Core::MATRIX_PROJECTION, proj);
		renderer->setTexture(texture);
		renderer->setVertexBuffer(vb1);
		renderer->setIndexBuffer(ib);
		renderer->drawIndexedPrimitives(PRIMITIVE_TRIANGLELIST, 0, 12);
		renderer->endScene();
		fpsCounter->count();
	}
}

bool Screen::Core::Root::renderFrame() const {
	SCREEN_DECL_METHOD(renderFrame)
	renderer->beginScene();
	renderer->endScene();
	return renderer->isRunning();
}

void Screen::Core::Root::init(){
	SCREEN_DECL_METHOD(init)
	renderer = &Screen::Core::Renderer::get();
	renderer->setRenderWindow(renderWindow);
	renderer->init();
	timer->reset();	
}
