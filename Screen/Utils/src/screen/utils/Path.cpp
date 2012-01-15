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
/**
 * \file screen/utils/Path.cpp
 * \brief Screen/Utils basic path handling source file
 * \author
 *
 */

#include <screen/utils/Path.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {
        Path::Path(const std::string& iPath)
            :_path(iPath){
			SCREEN_DECL_CONSTRUCTOR(Path)
			format();
		}
        Path::Path(const char* iPath)
            :_path(iPath){
			SCREEN_DECL_CONSTRUCTOR(Path)
			format();
		}
		
		void Path::format(){
			SCREEN_DECL_METHOD(format)
#ifdef WIN32
            std::replace(_path.begin(), _path.end(), '/', '\\');
            if(_path.rbegin()[0]!='\\')
                _path += '\\';
#else
            std::replace(_path.begin(), _path.end(), '\\', '/');
            if(_path.rbegin()[0]!='/')
                _path += '/';
#endif
		}
	
	    std::string Path::getPath() const{
	    	SCREEN_DECL_METHOD(getPath)
            return _path;
	    }
	    Path::operator const char* () const{
	    	SCREEN_DECL_METHOD(operator const char*)
            return _path.c_str();
	    }
	}
}
