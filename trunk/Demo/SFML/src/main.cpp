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

#include "Screen/Core/Root.h"
#include "Screen/Utils/Timer.h"
#include "Screen/Core/FPSCounter.h"
#include "Screen/Core/Renderer/Renderer.h"
#include "Screen/Utils/Profiler.h"
#include "Screen/Utils/ProfilerReporter.h"
#include "Screen/Utils/Logger.h"
#include "Screen/Utils/LoggerReporter.h"
#include "Screen/Utils/File.h"
#include "Screen/Utils/Path.h"
#include "Screen/Core/Loaders/ImageLoader.h"
#include "Screen/Core/Managers/TextureManager.h"

#include "SFMLOpenGLRenderWindow.h"
#include "SFMLRoot.h"

#include <iostream>

int main() {
	try{
		SCREEN_ATTACH_LOGGER_REPORTER(new Screen::Utils::FileLoggerReporter("out.log"))
		SCREEN_ATTACH_TIMER(new Screen::Core::Timer())
		SCREEN_ATTACH_PROFILE_REPORTER(new Screen::Utils::FileProfilerReporter("profiler.log"))
//		SCREEN_ATTACH_PROFILE_REPORTER(new Screen::Utils::CoutProfilerReporter())
		
		SCREEN_LOG_DEBUG("coucou")
		
		Screen::Core::Renderer::load("ScreenOpenGL");
		Screen::Core::TextureManager::instance()->registerLoader<Screen::Core::Objects::Image>(new Screen::Core::ImageLoader, "jpg|png|bmp|tga");
		Screen::Core::TextureManager::instance()->addPath(".");
		//Screen::Core::Objects::Image::SmartPtr image = Screen::Core::TextureManager::instance()->loadImageFromFile("SCREEN.bmp");
		
		Screen::Utils::SmartPtr<Screen::Core::Root> root(new SFMLRoot());
		Screen::Utils::SmartPtr<Screen::Core::RenderWindow> rw(new Screen::Utils::SFMLOpenGLRenderWindow());
		Screen::Utils::SmartPtr<Screen::Core::FPSCounter> fc(new Screen::Core::FPSCounter(2.0,std::cout));
		root->setRenderWindow(rw);
		root->setFPSCounter(fc);
		root->init();
		root->startRendering();
		
		Screen::Core::TextureManager::instance()->unregisterLoader<Screen::Core::Objects::Image>("jpg|png|bmp|tga");

	}catch(const Screen::Utils::Exception& e){
		SCREEN_LOG_ERROR("Exception controlée : " << std::endl << e.what())
		throw;
	}catch(const std::exception& e){
		SCREEN_LOG_ERROR("Exception non controlée : " << std::endl << e.what())
		throw;
	}catch(...){
		SCREEN_LOG_ERROR("Exception non controlée")
		throw;
	}

    return EXIT_SUCCESS;
}
