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
 * \file screen/utils/ProfilerReporter.cpp
 * \brief Screen/Utils profile data output handling source file
 * \author
 *
 */

#include <screen/utils/ProfilerReporter.h>
#include <screen/utils/Profiler.h>
#include <iostream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {
		ProfilerReporter::ProfilerReporter(){}
		ProfilerReporter::~ProfilerReporter(){}
		
        void CoutProfilerReporter::report(Profile* iProfile) {
            std::cout << iProfile->_info << " | "
            << iProfile->_beginning << " | "
            << iProfile->_ending << " | "
            << (iProfile->_ended ? "ended" : "crash" ) << std::endl;
        }
		
        FileProfilerReporter::FileProfilerReporter(const char* iFile)
            :ProfilerReporter(), _file(iFile)
    	{}
    	
        void FileProfilerReporter::report(Profile* iProfile) {
            static std::ofstream aFileStream(_file);
            aFileStream << iProfile->_info << " | "
            << iProfile->_beginning << " | "
            << iProfile->_ending << " | "
            << (iProfile->_ended ? "ended" : "crash" ) << std::endl;
        }
	}
}
