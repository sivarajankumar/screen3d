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

#include <screen/utils/Exception.h>

screen::utils::Exception::Exception(const std::string& message) throw ()
        :std::exception(),message("[screen exception] "+message) {
}

screen::utils::Exception::Exception(const std::string& file, int line, const std::string& message) throw ()
        :std::exception(),message("") {
    std::ostringstream stream;
    stream << "screen exception = file : " << file;
    stream << " , line : " << line;
    stream << " / " << message;
    this->message = stream.str();
}

screen::utils::Exception::~Exception() throw() {
}

const char* screen::utils::Exception::what() const throw() {
    return message.c_str();
}

screen::utils::AssertException::AssertException(const std::string& file, int line, const std::string& what) throw ()
        :screen::utils::Exception(file,line,"Assertion failed : "+what) {
}

screen::utils::AssertException::~AssertException() throw (){
}
