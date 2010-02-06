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

#include <SFML/Graphics.hpp>
#include "SFMLOpenGLRenderWindow.h"

using Screen::Utils::SFMLOpenGLRenderWindow;

SFMLOpenGLRenderWindow::SFMLOpenGLRenderWindow()
	:Screen::Core::RenderWindow(){
	app = NULL;
}
			
SFMLOpenGLRenderWindow::~SFMLOpenGLRenderWindow(){
	delete app;
}
			
void SFMLOpenGLRenderWindow::init(){
	// Create main window
	app = new sf::RenderWindow(sf::VideoMode(800, 600), "Screen : OpenGL");
    app->PreserveOpenGLStates(true);
//    app->SetFramerateLimit(60);
}

bool SFMLOpenGLRenderWindow::isRunning() const{
    sf::Event Event;
    while (app->GetEvent(Event))
    {
        if (Event.Type == sf::Event::Closed)
            app->Close();
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            app->Close();
    }
	return app->IsOpened();
}

void SFMLOpenGLRenderWindow::swapBuffers(){
	app->Display();
}
