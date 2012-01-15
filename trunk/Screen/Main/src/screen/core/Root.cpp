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

#include <screen/core/Root.h>
#include <screen/utils/Timer.h>
#include <screen/core/FPSCounter.h>
#include <screen/core/renderer/Renderer.h>
#include <screen/core/renderer/RenderWindow.h>
#include <screen/utils/MediaManager.h>

#include <iostream>

screen::core::Root::Root()
	:timer(new screen::utils::Timer()), renderer(NULL), renderWindow(NULL){
	SCREEN_DECL_CONSTRUCTOR(Root)
}

screen::core::Root::~Root() {
	SCREEN_DECL_DESTRUCTOR(~Root)
	if(renderer!=NULL)
		Renderer::destroy();
    delete timer;
}

void screen::core::Root::setRenderWindow(screen::core::RenderWindow* renderWindow){
	SCREEN_DECL_METHOD(setRenderWindow)
	this->renderWindow = renderWindow;
}

void screen::core::Root::setFPSCounter(screen::core::FPSCounter* fpsCounter){
	SCREEN_DECL_METHOD(setFPSCounter)
	this->fpsCounter = fpsCounter;
}

void screen::core::Root::startRendering(){	
    bool isRunning = true;
	while(isRunning) {
    	renderer->beginScene();
        isRunning =  renderFrame();
    	renderer->endScene();        
        fpsCounter->count();
    }

}

bool screen::core::Root::renderFrame(){
	SCREEN_DECL_METHOD(renderFrame)
	return renderer->isRunning();
}

void screen::core::Root::init(){
	SCREEN_DECL_METHOD(init)
	renderer = screen::core::Renderer::get();
	renderer->setRenderWindow(renderWindow);
	renderer->init();
	timer->reset();	
}
