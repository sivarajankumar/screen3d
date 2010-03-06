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

#include <Screen/Core/Color.h>

namespace Screen {
	namespace Core {
		Color::Color(unsigned long color)
			:color(color){
			SCREEN_DECL_CONSTRUCTOR(Color)
		}
		
		Color::Color(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
			SCREEN_DECL_CONSTRUCTOR(Color)
			set(b,g,r,a);
		}
		
		Color::~Color(){
			SCREEN_DECL_DESTRUCTOR(~Color)
		}
		
		unsigned long Color::convertABGR() const{
			SCREEN_DECL_METHOD(convertABGR)
			return color;
		}
		
		unsigned char Color::getAlpha() const{
			SCREEN_DECL_METHOD(getAlpha)
			return static_cast<unsigned char>((color & 0xFF000000) >> 24);
		}
		
		void Color::setAlpha(unsigned char a){
			SCREEN_DECL_METHOD(setAlpha)
			color = (color & 0x00FFFFFF) | (a << 24);
		}
        
		unsigned char Color::getBlue() const{
			SCREEN_DECL_METHOD(getBlue)
			return static_cast<unsigned char>((color & 0x00FF0000) >> 16);
        }
        
		void Color::setBlue(unsigned char b){
			SCREEN_DECL_METHOD(setBlue)
			color = (color & 0xFF00FFFF) | (b << 16);
		}
        
		unsigned char Color::getGreen() const{
			SCREEN_DECL_METHOD(getGreen)
			return static_cast<unsigned char>((color & 0x0000FF00) >> 8);
		}
        
		void Color::setGreen(unsigned char g){
			SCREEN_DECL_METHOD(setGreen)
			color = (color & 0xFFFF00FF) | (g << 8);
		}
        
		unsigned char Color::getRed() const{
			SCREEN_DECL_METHOD(getRed)
			return static_cast<unsigned char>((color & 0x000000FF) >> 0);
		}
        
		void Color::setRed(unsigned char r){
			SCREEN_DECL_METHOD(setRed)
			color = (color & 0xFFFFFF00) | (r << 0);
		}

        void Color::set(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
        	SCREEN_DECL_METHOD(set)
        	color = (a << 24) | (b << 16) | (g << 8) | (r << 0);
        }
        
        void Color::set(unsigned char b, unsigned char g, unsigned char r){
        	SCREEN_DECL_METHOD(set)
        	color = (color & 0xFF000000) | (b << 16) | (g << 8) | (r << 0);
        }
        
        void Color::set(unsigned long color){
        	SCREEN_DECL_METHOD(set)
        	this->color = color;
		}
	}
}
