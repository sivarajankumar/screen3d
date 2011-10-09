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

#include <screen/utils/LoggerReporter.h>
#include <iostream>

const char* defaultCallPos[] = {
	"begin",
	"end"
};

const char* defaultCallType[] = {
	"constructor",
	"destructor",
	"method",
	"static method",
	"function"
};

screen::utils::LoggerReporter::LoggerReporter() {}

screen::utils::LoggerReporter::~LoggerReporter() {}

screen::utils::CoutLoggerReporter::CoutLoggerReporter()
        :screen::utils::LoggerReporter() {}

screen::utils::CoutLoggerReporter::~CoutLoggerReporter() {}

void screen::utils::CoutLoggerReporter::debug(const std::string& log) {
    std::cout << "[DEBUG] " << log << std::endl;
}

void screen::utils::CoutLoggerReporter::info(const std::string& log) {
    std::cout << "[INFO] " << log << std::endl;
}

void screen::utils::CoutLoggerReporter::warning(const std::string& log) {
    std::cout << "[WARNING] " << log << std::endl;
}

void screen::utils::CoutLoggerReporter::error(const std::string& log) {
    std::cout << "[ERROR] " << log << std::endl;
}

void screen::utils::CoutLoggerReporter::call(
		CallPosition pos,
		CallType type,
		const char* className,
		const std::string& functionName,
		const std::string& address){
	switch(type){
	case CALL_FUNCTION:
		std::cout 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< functionName
					<< "]"
					<< std::endl;
		break;
	case CALL_STATIC_METHOD:
		std::cout 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< className
					<< "::"
					<< functionName
					<< "]"
					<< std::endl;
		break;
	default:
		std::cout 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< className
					<< "::"
					<< functionName
					<< "][address = "
					<< address
					<< "]"
					<< std::endl;
		break;
	}
}

screen::utils::FileLoggerReporter::FileLoggerReporter(const char* file)
        :screen::utils::LoggerReporter(), fileStream(file) {}

screen::utils::FileLoggerReporter::~FileLoggerReporter() {}

void screen::utils::FileLoggerReporter::debug(const std::string& log) {
    fileStream << "[DEBUG] " << log << std::endl;
}

void screen::utils::FileLoggerReporter::info(const std::string& log) {
	fileStream << "[INFO] " << log << std::endl;
}

void screen::utils::FileLoggerReporter::warning(const std::string& log) {
	fileStream << "[WARNING] " << log << std::endl;
}

void screen::utils::FileLoggerReporter::error(const std::string& log) {
	fileStream << "[ERROR] " << log << std::endl;
}

void screen::utils::FileLoggerReporter::call(
		CallPosition pos,
		CallType type,
		const char* className,
		const std::string& functionName,
		const std::string& address){
	switch(type){
	case CALL_FUNCTION:
		fileStream 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< functionName
					<< "]"
					<< std::endl;
		break;
	case CALL_STATIC_METHOD:
		fileStream 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< className
					<< "::"
					<< functionName
					<< "]"
					<< std::endl;
		break;
	default:
		fileStream 	<< "[CALL] ["
					<< defaultCallPos[pos]
					<< "]["
					<< defaultCallType[type]
					<< " = "
					<< className
					<< "::"
					<< functionName
					<< "][address = "
					<< address
					<< "]"
					<< std::endl;
		break;
	}
}
