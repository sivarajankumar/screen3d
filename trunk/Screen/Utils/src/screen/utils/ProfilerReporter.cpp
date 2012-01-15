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

#include <screen/utils/ProfilerReporter.h>
#include <screen/utils/Profiler.h>
#include <iostream>

namespace screen {
	namespace utils {
		ProfilerReporter::ProfilerReporter(){}
		ProfilerReporter::~ProfilerReporter(){}
		
		void CoutProfilerReporter::report(Profile* profile) {
            std::cout << profile->_info << " | "
            << profile->_beginning << " | "
            << profile->_ending << " | "
            << (profile->_ended ? "ended" : "crash" ) << std::endl;
        }
		
    	FileProfilerReporter::FileProfilerReporter(const char* file)
    		:ProfilerReporter(), file(file)
    	{}
    	
        void FileProfilerReporter::report(Profile* profile) {
        	static std::ofstream fileStream(file);
            fileStream << profile->_info << " | "
            << profile->_beginning << " | "
            << profile->_ending << " | "
            << (profile->_ended ? "ended" : "crash" ) << std::endl;
        }
	}
}
