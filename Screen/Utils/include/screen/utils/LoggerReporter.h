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
 * \file screen/utils/LoggerReporter.h
 * \brief Screen/Utils log message output handling header file
 * \author
 *
 */

#ifndef SCREEN_LOGGER_REPORTER_H
#define SCREEN_LOGGER_REPORTER_H

#include <screen/utils/Logger.h>
#include <screen/utils/Export.h>
#include <string>
#include <fstream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        /**
         * \brief Interface for all log reporters
         */
        class SCREEN_UTILS_EXPORT LoggerReporter {
        public:
            /**
             * \brief Default constructor
             */
            LoggerReporter();

            /**
             * \brief Destructor
             */
            virtual ~LoggerReporter() = 0;

            /**
             * \brief Log a debug message
             *
             * \param[in] iLog the debug message
             */
            virtual void debug(const std::string& iLog) = 0;

            /**
             * \brief Log an info message
             *
             * \param[in] iLog the info message
             */
            virtual void info(const std::string& iLog) = 0;

            /**
             * \brief Log a warning message
             *
             * \param[in] iLog the warning message
             */
            virtual void warning(const std::string& iLog) = 0;

            /**
             * \brief Log an error message
             *
             * \param[in] iLog the error message
             */
            virtual void error(const std::string& iLog) = 0;

            /**
             * \brief Log a call message
             *
             * \param[in] iPos The call position (begin or end)
             * \param[in] iType The call type
             * \param[in] iClassName The name of the class
             * \param[in] iFunctionName The function or method name
             * \param[in] iAddress The address of the traced instance
             */
            virtual void call(CallPosition iPos,
                      CallType iType,
                      const char* iClassName,
                      const std::string& iFunctionName,
                      const std::string& iAddress) = 0;
        };

        /**
         * \brief Standard output reporter
         *
         * Writes the log messages into the console
         */
        class SCREEN_UTILS_EXPORT CoutLoggerReporter : public LoggerReporter {
        public:
            /**
             * \brief Default constructor
             */
            CoutLoggerReporter();

            /**
             * \brief Destructor
             */
            ~CoutLoggerReporter();

            /**
             * \brief Log a debug message in standard output stream
             *
             * \param[in] iLog the debug message
             */
            void debug(const std::string& iLog);

            /**
             * \brief Log an info message in standard output stream
             *
             * \param[in] iLog the info message
             */
            void info(const std::string& iLog);

            /**
             * \brief Log a warning message in standard output stream
             *
             * \param[in] iLog the warning message
             */
            void warning(const std::string& iLog);

            /**
             * \brief Log an error message in standard output stream
             *
             * \param[in] iLog the error message
             */
            void error(const std::string& iLog);

            /**
             * \brief Log a call message in standard output stream
             *
             * \param[in] iPos The call position (begin or end)
             * \param[in] iType The call type
             * \param[in] iClassName The name of the class
             * \param[in] iFunctionName The function or method name
             * \param[in] iAddress The address of the traced instance
             */
            void call(CallPosition iPos,
                      CallType iType,
                      const char* iClassName,
                      const std::string& iFunctionName,
                      const std::string& iAddress);
        };
        
        /**
         * \brief File output reporter
         *
         * Writes the log messages into a given file
         */
        class SCREEN_UTILS_EXPORT FileLoggerReporter : public LoggerReporter {
        public:
            /**
             * \brief Constructor with output file path
             *
             * \param[in] iFile complete file path
             */
            FileLoggerReporter(const char* iFile);

            /**
             * \brief Destructor
             */
            ~FileLoggerReporter();

            /**
             * \brief Log a debug message in file output stream
             *
             * \param[in] iLog the debug message
             */
            void debug(const std::string& iLog);

            /**
             * \brief Log an info message in file output stream
             *
             * \param[in] iLog the info message
             */
            void info(const std::string& iLog);

            /**
             * \brief Log a warning message in file output stream
             *
             * \param[in] iLog the warning message
             */
            void warning(const std::string& iLog);

            /**
             * \brief Log an error message in file output stream
             *
             * \param[in] iLog the error message
             */
            void error(const std::string& iLog);

            /**
             * \brief Log a call message in file output stream
             *
             * \param[in] iPos The call position (begin or end)
             * \param[in] iType The call type
             * \param[in] iClassName The name of the class
             * \param[in] iFunctionName The function or method name
             * \param[in] iAddress The address of the traced instance
             */
            void call(CallPosition iPos,
                      CallType iType,
                      const char* iClassName,
                      const std::string& iFunctionName,
                      const std::string& iAddress);
        private:
            std::ofstream _fileStream; ///< output file stream
        };
    }
}

#endif
