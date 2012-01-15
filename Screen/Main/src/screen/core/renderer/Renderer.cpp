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

#include <screen/core/renderer/Renderer.h>
#include <screen/utils/Exception.h>

namespace screen {
    namespace core {
    	Renderer::Renderer(){
    		SCREEN_DECL_CONSTRUCTOR(Renderer)
    	}
    	Renderer::~Renderer(){
    		SCREEN_DECL_DESTRUCTOR(~Renderer)
    	}

		void Renderer::load(const std::string& fileName){
			SCREEN_DECL_STATIC_METHOD(load)
			delete renderer;
			renderer = sharedLibrary.load(fileName);
            SCREEN_ASSERT(renderer!=NULL);
		}

		Renderer* Renderer::get(){
			SCREEN_DECL_STATIC_METHOD(get)
            SCREEN_ASSERT(renderer!=NULL);
			return renderer;
		}

		void Renderer::destroy(){
			SCREEN_DECL_STATIC_METHOD(destroy)
			delete renderer;
			renderer = NULL;
		}
		
		void Renderer::setTexture(unsigned int textureNumber, const screen::core::objects::Texture& texture){
			SCREEN_DECL_METHOD(setTexture)
			setTextureBase(textureNumber, texture.getTexture());
		}
		
		void Renderer::init(){
			SCREEN_DECL_METHOD(init)
			renderWindow->init();
			initialize();
		}
		
		bool Renderer::isRunning(){
			SCREEN_DECL_METHOD(isRunning)
			return renderWindow->isRunning();
		}
		
		void Renderer::setRenderWindow(screen::core::RenderWindow* renderWindow){
			SCREEN_DECL_METHOD(setRenderWindow)
			this->renderWindow = renderWindow;
		}
		
		screen::utils::Plugin<Renderer> Renderer::sharedLibrary;
		Renderer* Renderer::renderer = NULL;
    }
}
