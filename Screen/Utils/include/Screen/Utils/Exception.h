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

#ifndef SCREEN_EXCEPTION_H
#define SCREEN_EXCEPTION_H

#include <Screen/Utils/Export.h>
#include <Screen/Utils/Declaration.h>
#include <exception>
#include <string>
#include <sstream>

namespace Screen {
    namespace Utils {
        class SCREEN_EXPORT Exception : public std::exception {
        public:
            Exception(const std::string& message) throw ();
            Exception(const std::string& file, int line, const std::string& message) throw ();
            ~Exception() throw ();
            virtual const char* what() const throw();
        private:
            std::string message;
        };

        struct SCREEN_EXPORT AssertException : public Exception {
            AssertException(const std::string& file, int line, const std::string& what) throw ();
        	~AssertException() throw ();
        };

# ifdef SCREEN_ASSERT
#  define Assert(p) if(!(p)) throw Screen::Utils::AssertException(__FILE__,__LINE__,#p)
# else
#  define Assert(p)
# endif

		struct SCREEN_EXPORT LoadingException : public Exception {
			LoadingException(const std::string& fileName, const std::string& message) throw ()
				:Exception("Unable to load file : "+fileName+" / "+message){
			}
			~LoadingException() throw (){
			}
		};

    }
}

#endif
