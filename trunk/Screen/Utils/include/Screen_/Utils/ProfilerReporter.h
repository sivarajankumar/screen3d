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

#ifndef SCREEN_PROFILER_REPORTER_H
#define SCREEN_PROFILER_REPORTER_H

#include <Screen/Utils/Export.h>
#include <fstream>

namespace Screen {
    namespace Utils {
    	struct Profile;
        /*interface*/
        class SCREEN_UTILS_EXPORT ProfilerReporter {
        public:
            ProfilerReporter();
            virtual ~ProfilerReporter();
            virtual void report(Profile* profile) = 0;
        };

        class SCREEN_UTILS_EXPORT CoutProfilerReporter : public ProfilerReporter {
        public:
            void report(Profile* profile);
        };
        
        class SCREEN_UTILS_EXPORT FileProfilerReporter : public ProfilerReporter {
        public:
        	FileProfilerReporter(const char* file);
            void report(Profile* profile);
        private:
        	const char* file;
        };
    }
}
#endif
