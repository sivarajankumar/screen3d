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
 * \file screen/utils/File.cpp
 * \brief Screen/Utils basic file handling source file
 * \author
 *
 */

#include <screen/utils/File.h>
#include <algorithm>
#include <fstream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        File::File(const std::string& iFile)
            :_file(iFile){
			SCREEN_DECL_CONSTRUCTOR(File)
#ifdef WIN32
            std::replace(_file.begin(), _file.end(), '/', '\\');
#else
            std::replace(_file.begin(), _file.end(), '\\', '/');
#endif
		}
	
        File::File(const char* iFile)
            :_file(iFile){
			SCREEN_DECL_CONSTRUCTOR(File)
#ifdef WIN32
            std::replace(_file.begin(), _file.end(), '/', '\\');
#else
            std::replace(_file.begin(), _file.end(), '\\', '/');
#endif
		}
	
		bool File::exists() const{
			SCREEN_DECL_METHOD(exists)
            std::ifstream aStr(_file.c_str());
            return aStr.is_open();
		}
	
		std::string File::getFullname() const{
			SCREEN_DECL_METHOD(getFullName)
            return _file;
		}
	
		std::string File::getFilename() const{
			SCREEN_DECL_METHOD(getFileName)
            std::string::size_type aPos = _file.find_last_of("\\/");
	
            if (aPos != std::string::npos)
                return _file.substr(aPos + 1, std::string::npos);
		    else
                return _file;
		}	
	
		std::string File::getExtension() const{
			SCREEN_DECL_METHOD(getExtension)
            std::string::size_type aPos = _file.find_last_of(".");
            if (aPos != std::string::npos)
                return _file.substr(aPos + 1, std::string::npos);
		    else
		        return "";
		}
	}
}
