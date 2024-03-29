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

#ifndef SCREEN_ROOT_H
#define SCREEN_ROOT_H

#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen {
	namespace utils {
		class Timer;
	}
    namespace core {
	    class FPSCounter;
	    class Renderer;
	    class RenderWindow;
	    
        class SCREEN_MAIN_EXPORT Root {
        	SCREEN_DECL_CLASS(screen::core::Root)
        public:
            explicit Root();
            virtual ~Root();
            void setRenderWindow(screen::core::RenderWindow* renderWindow);
            void setFPSCounter(screen::core::FPSCounter* fpsCounter);
            
            virtual void init();
            void startRendering();
        protected:
            virtual bool renderFrame();
            screen::utils::Timer* timer;
            FPSCounter* fpsCounter;
            Renderer* renderer;
            RenderWindow* renderWindow;
        };
    }
}

#endif
