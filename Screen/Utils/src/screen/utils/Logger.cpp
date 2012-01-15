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
 * \file screen/utils/Logger.cpp
 * \brief Screen/Utils log handling source file
 * \author
 *
 */


#include <screen/utils/Logger.h>
#include <screen/utils/LoggerReporter.h>
#include <screen/utils/Exception.h>
#include <iostream>

SINGLETON_IMPL(UniqueSingleton,screen::utils::Logger)

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        void Logger::attachReporter(LoggerReporter* iReporter) {
            if(_reporter!=NULL)
                delete _reporter;
            _reporter = iReporter;
        }

        void Logger::debug(const std::string& iLog) {
            if(_reporter==NULL){
                std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
                std::cerr << "To log : [DEBUG] " << iLog << std::endl;
            }
            else{
                _reporter->debug(iLog);
            }
        }

        void Logger::info(const std::string& iLog) {
            if(_reporter==NULL){
                std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
                std::cerr << "To log : [INFO] " << iLog << std::endl;
            }
            else{
                _reporter->info(iLog);
            }
        }

        void Logger::warning(const std::string& iLog) {
            if(_reporter==NULL){
                std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
                std::cerr << "To log : [WARNING] " << iLog << std::endl;
            }
            else{
                _reporter->warning(iLog);
            }
        }

        void Logger::error(const std::string& iLog) {
            if(_reporter==NULL){
                std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
                std::cerr << "To log : [ERROR] " << iLog << std::endl;
            }
            else{
                _reporter->error(iLog);
            }
        }

        void Logger::call(CallPosition iPos,
                          CallType iType,
                          const char* iClassName,
                          const std::string& iFunctionName,
                          const std::string& iAddress){
            if(_reporter==NULL){
                std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
                std::cerr << "To log : [CALL] ..." << std::endl;
            }
            else{
                _reporter->call(iPos,iType,iClassName,iFunctionName,iAddress);
            }
        }

        Logger::Logger()
            :_reporter(NULL) {}

        Logger::~Logger() {
            delete _reporter;
            _reporter = NULL;
        }

        ScopeLog::ScopeLog(screen::utils::CallType iType,
                           const char* iClassName,
                           const std::string& iFunctionName,
                           const std::string& iAddress)
            :_type(iType),_className(iClassName), _functionName(iFunctionName), _address(iAddress){
            SCREEN_LOG_CALL(screen::utils::CALL_BEGIN,_type,_className,_functionName,_address);
        }

        ScopeLog::~ScopeLog(){
            SCREEN_LOG_CALL(screen::utils::CALL_END,_type,_className,_functionName,_address);
        }
    }
}
