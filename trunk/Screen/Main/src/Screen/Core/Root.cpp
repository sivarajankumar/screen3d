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
#include <Screen/Utils/Timer.h>
#include <Screen/Core/FPSCounter.h>
#include <Screen/Core/Renderer/Renderer.h>
#include <Screen/Core/Renderer/RenderWindow.h>
#include <Screen/Utils/MediaManager.h>

#include <iostream>

Screen::Core::Root::Root()
	:timer(new Screen::Utils::Timer()), renderer(NULL), renderWindow(NULL){
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

void Screen::Core::Root::startRendering(){	
    bool isRunning = true;
	while(isRunning) {
    	renderer->beginScene();
        isRunning =  renderFrame();
    	renderer->endScene();        
        fpsCounter->count();
    }

}

bool Screen::Core::Root::renderFrame(){
	SCREEN_DECL_METHOD(renderFrame)
	return renderer->isRunning();
}

void Screen::Core::Root::init(){
	SCREEN_DECL_METHOD(init)
	renderer = &Screen::Core::Renderer::get();
	renderer->setRenderWindow(renderWindow);
	renderer->init();
	timer->reset();	
}
