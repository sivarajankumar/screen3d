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
 * \file screen/utils/Exception.h
 * \brief Screen/Utils common exception header file
 * \author
 *
 */

#ifndef SCREEN_EXCEPTION_H
#define SCREEN_EXCEPTION_H

#include <screen/utils/Export.h>
#include <screen/utils/Declaration.h>
#include <exception>
#include <string>
#include <sstream>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        /**
         * \brief Common Screen exception
         */
        class SCREEN_UTILS_EXPORT Exception : public std::exception {
        public:
            /**
             * \brief Constructor with exception message
             *
             * \param[in] iMessage exception message
             */
            Exception(const std::string& iMessage) throw ();

            /**
             * \brief Constructor with file name, line number and exception message
             *
             * Commonly used with __FILE__ and __LINE__ macros
             *
             * \param[in] iFile file name
             * \param[in] iLine line number
             * \param[in] iMessage exception message
             */
            Exception(const std::string& iFile, int iLine, const std::string& iMessage) throw ();

			/**
			 * \brief Constructor with file name, line number and exception message as stream
			 *
			 * Commonly used with __FILE__ and __LINE__ macros
			 *
			 * \param[in] iFile file name
			 * \param[in] iLine line number
			 * \param[in] iStreamMessage exception message as stream
			 */
			Exception(const std::string& iFile, int iLine, std::ostringstream& iMessage) throw ();

            /**
             * \brief Destructor
             */
            ~Exception() throw ();

            /**
             * \brief Retrieve exception message
             *
             * \return Returns the exception message
             */
            virtual const char* what() const throw();

			/**
			 * \brief Get file where the exception has been thrown
			 *
			 * \return name of the code file which has thrown the exception; or an empty string if unknown
			 */
			std::string getFile() const{
				return _file;
			}

			/**
			 * \brief Get line where the exception has been thrown
			 *
			 * \return line of the code file which has thrown the exception; or 0 if unknown
			 */
			int getLine() const{
				return _line;
			}


		protected:

			/**
			 * \brief fill exception message, adding file, line and a header in the exception message
			 *
			 * \param[in] iFile file name
			 * \param[in] iLine line number
			 * \param[in] iStreamMessage exception message as stream
			 */
			virtual void fillMessage(const std::string& iFile, int iLine, std::ostringstream& iStreamMessage);

        private:
            std::string _message; ///< exception message string
			std::string _file; ///< file where the exception has been thrown (empty if not set)
			int _line; ///< line where the exception has been thrown (0 if not set)
        };


        /**
         * \brief Screen assertion exception
         *
         * Must be used throw SCREEN_ASSERT macro
         */
        struct SCREEN_UTILS_EXPORT AssertException : public Exception {
            /**
             * \brief Constructor with file name, line number and exception message
             *
             * File and line are filed by SCREEN_ASSERT macro
             *
             * \param[in] iFile file name
             * \param[in] iLine line number
             * \param[in] iMessage exception message
             */
            AssertException(const std::string& iFile, int iLine, const std::string& iMessage) throw ();

            /**
             * \brief Destructor
             */
            ~AssertException() throw ();
        };

# ifdef USE_SCREEN_ASSERT
#  define SCREEN_ASSERT(p) if(!(p)) throw screen::utils::AssertException(__FILE__,__LINE__,#p)
# else
#  define SCREEN_ASSERT(p)
# endif

        /**
         * \brief Screen loading exception
         *
         * Must be used for file IO errors
         */
        struct SCREEN_UTILS_EXPORT LoadingException : public Exception {


			/**
			 * \brief Constructor with file name, line number and exception message
			 *
			 * File and line are filed by SCREEN_ASSERT macro
			 *
			 * \param[in] iFile file name
			 * \param[in] iLine line number
			 * \param[in] iMessage exception message
			 */
			LoadingException(const std::string& iFile, int iLine, const std::string& iMessage) throw ();


            /**
             * \brief Constructor with file name, line number and exception message
             *
             * File and line are filed by SCREEN_ASSERT macro
             *
             * \param[in] iFileName File name we were unable to load
             * \param[in] iMessage exception message
             */
            LoadingException(const std::string& iFileName, const std::string& iMessage) throw ();

            /**
             * \brief Destructor
             */
            ~LoadingException() throw ();
		};

    }
}

#endif
