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

#ifndef SCREEN_PATH_H
#define SCREEN_PATH_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>
#include <string>

namespace Screen {
	namespace Utils {
	    class SCREEN_EXPORT Path{
	    	SCREEN_DECL_CLASS(Screen::Utils::Path)
	    public:
	    	Path(const std::string& path = "");
	    	Path(const char* path);
	
	        std::string getPath() const;
	        operator const char* () const;
	    private:
	    	void format();
	        std::string path;
	    };
	}
}

#endif
