/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2011 Ratouit Thomas                                    *
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

#include "screen/core/Root.h"
#include "screen/utils/Timer.h"
#include "screen/core/FPSCounter.h"
#include "screen/core/renderer/Renderer.h"
#include "screen/utils/Profiler.h"
#include "screen/utils/ProfilerReporter.h"
#include "screen/utils/Logger.h"
#include "screen/utils/LoggerReporter.h"
#include "screen/utils/File.h"
#include "screen/utils/Path.h"
#include "screen/image/il/ImageLoader.h"
#include "screen/core/managers/TextureManager.h"
//
#include "SFMLOpenGLRenderWindow.h"
#include "SFMLRoot.h"

#include <iostream>

int main() {
	try{
		SCREEN_ATTACH_LOGGER_REPORTER(new screen::utils::FileLoggerReporter("out.log"))
		SCREEN_ATTACH_PROFILE_REPORTER(new screen::utils::FileProfilerReporter("profiler.log"))
		
		SCREEN_LOG_DEBUG("Hello world !!");
		
		screen::core::Renderer::load("ScreenOpenGL");
		screen::core::TextureManager::instance()->registerLoader<screen::core::objects::Image>(new screen::image::il::ImageLoader, "jpg|png|bmp|tga");
		screen::core::TextureManager::instance()->addPath(".");
		
		screen::utils::SmartPtr<screen::core::Root> root(new SFMLRoot());
		screen::utils::SmartPtr<screen::core::RenderWindow> rw(new screen::utils::SFMLOpenGLRenderWindow());
		screen::utils::SmartPtr<screen::core::FPSCounter> fc(new screen::core::FPSCounter(2.0,std::cout));
		root->setRenderWindow(rw);
		root->setFPSCounter(fc);
		root->init();
		root->startRendering();
		
		screen::core::TextureManager::instance()->unregisterLoader<screen::core::objects::Image>("jpg|png|bmp|tga");

	}catch(const screen::utils::Exception& e){
		SCREEN_LOG_ERROR("Screen Exception : " << std::endl << e.what());
		throw;
	}catch(const std::exception& e){
		SCREEN_LOG_ERROR("Standard Exception : " << std::endl << e.what());
		throw;
	}catch(...){
		SCREEN_LOG_ERROR("Unknown Exception");
		throw;
	}

    return EXIT_SUCCESS;
}
