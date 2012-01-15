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
/**
 * \file screen/utils/Exception.h
 * \brief Screen/Utils common exception header file
 * \author
 *
 */

#include <screen/utils/Exception.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        Exception::Exception(const std::string& iMessage) throw ()
                :std::exception(), _message("[screen exception] "+iMessage) {
        }

        Exception::Exception(const std::string& iFile, int iLine, const std::string& iMessage) throw ()
                :std::exception(),_message("") {
            std::ostringstream aStream;
            aStream << "screen exception = file : " << iFile;
            aStream << " , line : " << iLine;
            aStream << " / " << iMessage;
            _message = aStream.str();
        }

        Exception::~Exception() throw() {}

        const char* Exception::what() const throw() {
            return _message.c_str();
        }

        AssertException::AssertException(const std::string& iFile, int iLine, const std::string& iMessage) throw ()
                :Exception(iFile, iLine, "Assertion failed : "+iMessage){
        }

        AssertException::~AssertException() throw (){}

        LoadingException::LoadingException(const std::string& iFileName, const std::string& iMessage) throw ()
            :Exception("Unable to load file : "+iFileName+" / "+iMessage){
        }

        LoadingException::~LoadingException() throw (){}
    }
}
