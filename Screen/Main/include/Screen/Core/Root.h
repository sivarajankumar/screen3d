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

#ifndef SCREEN_ROOT_H
#define SCREEN_ROOT_H

#include <Screen/Core/Objects/VertexBuffer.h>
#include <Screen/Core/Objects/IndexBuffer.h>
#include <Screen/Math/Matrix4x4f.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
    namespace Core {
	    class Timer;
	    class FPSCounter;
	    class Renderer;
	    class RenderWindow;
	    
        class SCREEN_EXPORT Root {
        	SCREEN_DECL_CLASS(Screen::Core::Root)
        public:
            explicit Root();
            ~Root();
            void setRenderWindow(Screen::Core::RenderWindow* renderWindow);
            void setFPSCounter(Screen::Core::FPSCounter* fpsCounter);
            
            void init();
            void startRendering() const;
        private:
            bool renderFrame() const;
            Timer* timer;
            FPSCounter* fpsCounter;
            Renderer* renderer;
            RenderWindow* renderWindow;
            
            //tmp
            struct TVertex1
            {
            	float x, y, z;
            	unsigned long Color;
            	float tu, tv;
            };
        };
    }
}

#endif
