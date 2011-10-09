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


#include <screen/utils/Logger.h>
#include <screen/utils/LoggerReporter.h>
#include <screen/utils/Exception.h>
#include <iostream>

SINGLETON_IMPL(UniqueSingleton,screen::utils::Logger)

void screen::utils::Logger::attachReporter(LoggerReporter* reporter) {
    if(this->reporter!=NULL)
        delete this->reporter;
    this->reporter = reporter;
}

void screen::utils::Logger::debug(const std::string& log) {
	//std::cout << this << " / " << reporter << std::endl;
		
    if(reporter==NULL){
        std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
        std::cerr << "To log : [DEBUG] " << log << std::endl;
        return;
    }
    reporter->debug(log);
}

void screen::utils::Logger::info(const std::string& log) {
    if(reporter==NULL){
        std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
        std::cerr << "To log : [INFO] " << log << std::endl;
        return;
    }
    reporter->info(log);
}

void screen::utils::Logger::warning(const std::string& log) {
    if(reporter==NULL){
        std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
        std::cerr << "To log : [WARNING] " << log << std::endl;
        return;
    }
    reporter->warning(log);
}

void screen::utils::Logger::error(const std::string& log) {
    if(reporter==NULL){
        std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
        std::cerr << "To log : [ERROR] " << log << std::endl;
        return;
    }
    reporter->error(log);
}

void screen::utils::Logger::call(CallPosition pos,
            		  			 CallType type,
            		  			 const char* className,
            		  			 const std::string& functionName,
            		  			 const std::string& address){
	if(reporter==NULL){
        std::cerr << "Can't log : undefined LoggerReporter" << std::endl;
        std::cerr << "To log : [CALL] ..." << std::endl;
        return;
    }
    reporter->call(pos,type,className,functionName,address);
}

screen::utils::Logger::Logger()
        :reporter(NULL) {}

screen::utils::Logger::~Logger() {
    delete reporter;
}
