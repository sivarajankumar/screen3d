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

#ifndef SCREEN_LOGGER_REPORTER_H
#define SCREEN_LOGGER_REPORTER_H

#include <screen/utils/Logger.h>
#include <screen/utils/Export.h>
#include <string>
#include <fstream>

namespace screen {
    namespace utils {
        class SCREEN_UTILS_EXPORT LoggerReporter {
        public:
            LoggerReporter();
            virtual ~LoggerReporter();
            virtual void debug(const std::string& log) = 0;
            virtual void info(const std::string& log) = 0;
            virtual void warning(const std::string& log) = 0;
            virtual void error(const std::string& log) = 0;
            virtual void call(CallPosition pos,
            				  CallType type,
            				  const char* className,
            				  const std::string& functionName,
            				  const std::string& address) = 0;
        };

        class SCREEN_UTILS_EXPORT CoutLoggerReporter : public LoggerReporter {
        public:
            CoutLoggerReporter();
            ~CoutLoggerReporter();
            void debug(const std::string& log);
            void info(const std::string& log);
            void warning(const std::string& log);
            void error(const std::string& log);
            void call(CallPosition pos,
            		  CallType type,
            		  const char* className,
            		  const std::string& functionName,
            		  const std::string& address);
        };
        
        class SCREEN_UTILS_EXPORT FileLoggerReporter : public LoggerReporter {
        public:
        	FileLoggerReporter(const char* file);
            ~FileLoggerReporter();
            void debug(const std::string& log);
            void info(const std::string& log);
            void warning(const std::string& log);
            void error(const std::string& log);
            void call(CallPosition pos,
            		  CallType type,
            		  const char* className,
            		  const std::string& functionName,
            		  const std::string& address);
        private:
        	std::ofstream fileStream;
        };
    }
}

#endif
