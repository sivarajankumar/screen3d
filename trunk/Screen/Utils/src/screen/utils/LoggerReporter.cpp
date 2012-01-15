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
 * \file screen/utils/LoggerReporter.cpp
 * \brief Screen/Utils log message output handling source file
 * \author
 *
 */

#include <screen/utils/LoggerReporter.h>
#include <iostream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        const char* _DefaultCallPos[] = {
            "begin",
            "end"
        };

        const char* _DefaultCallType[] = {
            "constructor",
            "destructor",
            "method",
            "static method",
            "function"
        };

        LoggerReporter::LoggerReporter() {}

        LoggerReporter::~LoggerReporter() {}

        CoutLoggerReporter::CoutLoggerReporter()
            :screen::utils::LoggerReporter() {}

        CoutLoggerReporter::~CoutLoggerReporter() {}

        void CoutLoggerReporter::debug(const std::string& iLog) {
            std::cout << "[DEBUG] " << iLog << std::endl;
        }

        void CoutLoggerReporter::info(const std::string& iLog) {
            std::cout << "[INFO] " << iLog << std::endl;
        }

        void CoutLoggerReporter::warning(const std::string& iLog) {
            std::cout << "[WARNING] " << iLog << std::endl;
        }

        void CoutLoggerReporter::error(const std::string& iLog) {
            std::cout << "[ERROR] " << iLog << std::endl;
        }

        void CoutLoggerReporter::call(CallPosition iPos,
                                      CallType iType,
                                      const char* iClassName,
                                      const std::string& iFunctionName,
                                      const std::string& iAddress){
            switch(iType){
            case CALL_FUNCTION:
                std::cout 	<< "[CALL] ["
                            << _DefaultCallPos[iPos]
                            << "]["
                            << _DefaultCallType[iType]
                            << " = "
                            << iFunctionName
                            << "]"
                            << std::endl;
                break;
            case CALL_STATIC_METHOD:
                std::cout 	<< "[CALL] ["
                            << _DefaultCallPos[iPos]
                            << "]["
                            << _DefaultCallType[iType]
                            << " = "
                            << iClassName
                            << "::"
                            << iFunctionName
                            << "]"
                            << std::endl;
                break;
            default:
                std::cout 	<< "[CALL] ["
                            << _DefaultCallPos[iPos]
                            << "]["
                            << _DefaultCallType[iType]
                            << " = "
                            << iClassName
                            << "::"
                            << iFunctionName
                            << "][address = "
                            << iAddress
                            << "]"
                            << std::endl;
                break;
            }
        }

        FileLoggerReporter::FileLoggerReporter(const char* iFile)
                :LoggerReporter(), _fileStream(iFile) {}

        FileLoggerReporter::~FileLoggerReporter() {}

        void FileLoggerReporter::debug(const std::string& iLog) {
            _fileStream << "[DEBUG] " << iLog << std::endl;
        }

        void FileLoggerReporter::info(const std::string& iLog) {
            _fileStream << "[INFO] " << iLog << std::endl;
        }

        void FileLoggerReporter::warning(const std::string& iLog) {
            _fileStream << "[WARNING] " << iLog << std::endl;
        }

        void FileLoggerReporter::error(const std::string& iLog) {
            _fileStream << "[ERROR] " << iLog << std::endl;
        }

        void FileLoggerReporter::call(CallPosition iPos,
                                      CallType iType,
                                      const char* iClassName,
                                      const std::string& iFunctionName,
                                      const std::string& iAddress){
            switch(iType){
            case CALL_FUNCTION:
                _fileStream 	<< "[CALL] ["
                                << _DefaultCallPos[iPos]
                                << "]["
                                << _DefaultCallType[iType]
                                << " = "
                                << iFunctionName
                                << "]"
                                << std::endl;
                break;
            case CALL_STATIC_METHOD:
                _fileStream 	<< "[CALL] ["
                                << _DefaultCallPos[iPos]
                                << "]["
                                << _DefaultCallType[iType]
                                << " = "
                                << iClassName
                                << "::"
                                << iFunctionName
                                << "]"
                                << std::endl;
                break;
            default:
                _fileStream 	<< "[CALL] ["
                                << _DefaultCallPos[iPos]
                                << "]["
                                << _DefaultCallType[iType]
                                << " = "
                                << iClassName
                                << "::"
                                << iFunctionName
                                << "][address = "
                                << iAddress
                                << "]"
                                << std::endl;
                break;
            }
        }
    }
}
