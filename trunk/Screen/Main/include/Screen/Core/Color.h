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

#ifndef SCREEN_COLOR_H
#define SCREEN_COLOR_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		/*!  \class Color
		 *   \brief color definition
		 *   \author Ratouit Thomas
		 */

		class SCREEN_EXPORT Color {
			SCREEN_DECL_CLASS(Screen::Core::Color)
		public:
				Color(unsigned long color = 0xFF000000);
				Color(unsigned char b, unsigned char g, unsigned char r, unsigned char a = 0xFF);
				~Color();
				
				unsigned long convertABGR() const;
				
				unsigned char getAlpha() const;
				void setAlpha(unsigned char a);
				unsigned char getBlue() const;
				void setBlue(unsigned char b);
		        unsigned char getGreen() const;
		        void setGreen(unsigned char g);
				unsigned char getRed() const;
		        void setRed(unsigned char r);
		        void set(unsigned char b, unsigned char g, unsigned char r, unsigned char a);
		        void set(unsigned char b, unsigned char g, unsigned char r);
		        
		private:
			unsigned long color; //ABGR
		};
	}
}

#endif
