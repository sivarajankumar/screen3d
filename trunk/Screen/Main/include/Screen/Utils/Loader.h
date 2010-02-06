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

#ifndef SCREEN_LOADER_H
#define SCREEN_LOADER_H

#include <string>

namespace Screen {
	namespace Utils {
	    template <class T>
	    class Loader{
	    public :
	        virtual ~Loader() {}
	        virtual T* loadFromFile(const std::string& filename) const = 0;
	        virtual const char* _selfType() const = 0;
	        virtual const char* _loadedType() const = 0;
	    protected :
	        Loader() {}
	    };
	    
#define SCREEN_DECL_LOADER(self,loaded) \
public: \
virtual const char* _selfType() const{ \
    return #self; \
} \
virtual const char* _loadedType() const{ \
	return #loaded; \
}
	}
}

#endif
