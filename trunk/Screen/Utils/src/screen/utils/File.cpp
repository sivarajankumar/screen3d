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

#include <screen/utils/File.h>
#include <algorithm>
#include <fstream>

namespace screen {
	namespace utils {
		File::File(const std::string& _file)
			:file(_file){
			SCREEN_DECL_CONSTRUCTOR(File)
#ifdef WIN32
		    std::replace(file.begin(), file.end(), '/', '\\');
#else
		    std::replace(file.begin(), file.end(), '\\', '/');
#endif
		}
	
		File::File(const char* _file)
			:file(_file){
			SCREEN_DECL_CONSTRUCTOR(File)
#ifdef WIN32
		    std::replace(file.begin(), file.end(), '/', '\\');
#else
		    std::replace(file.begin(), file.end(), '\\', '/');
#endif
		}
	
		bool File::exists() const{
			SCREEN_DECL_METHOD(exists)
			std::ifstream str(file.c_str());
		    return str.is_open();
		}
	
		std::string File::getFullname() const{
			SCREEN_DECL_METHOD(getFullName)
		    return file;
		}
	
		std::string File::getFilename() const{
			SCREEN_DECL_METHOD(getFileName)
		    std::string::size_type pos = file.find_last_of("\\/");
	
		    if (pos != std::string::npos)
		        return file.substr(pos + 1, std::string::npos);
		    else
		        return file;
		}	
	
		std::string File::getExtension() const{
			SCREEN_DECL_METHOD(getExtension)
		    std::string::size_type pos = file.find_last_of(".");
		    if (pos != std::string::npos)
		        return file.substr(pos + 1, std::string::npos);
		    else
		        return "";
		}
	}
}
