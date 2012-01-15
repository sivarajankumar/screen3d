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
 * \file screen/utils/File.h
 * \brief Screen/Utils basic file handling header file
 * \author
 *
 */

#ifndef SCREEN_FILE_H
#define SCREEN_FILE_H

#include <screen/utils/Declaration.h>
#include <screen/utils/Export.h>
#include <string>

/**
 * Namespace for all screen classes
 */
namespace screen {
    /**
     * Namespace for all utility classes
     */
    namespace utils {

        /**
         * \brief File path and name handling class
         */
	    class SCREEN_UTILS_EXPORT File{
	    	SCREEN_DECL_CLASS(screen::utils::File)
	    public :
            /**
             * \brief Constructor with full file path and name
             *
             * \param[in] iFile file path and name
             */
            File(const std::string& iFile = "");

            /**
             * \brief Constructor with full file path and name
             *
             * \param[in] iFile file path and name
             */
            File(const char* iFile);
	
            /**
             * \brief Verify the file exists on the system
             *
             * \return File exists
             */
            bool exists() const;
	
            /**
             * \brief Retrieve full path and name
             *
             * \return File name and path
             */
            std::string getFullname() const;
	
            /**
             * \brief Retrieve file name only (i.e without the path)
             *
             * \return File name
             */
            std::string getFilename() const;
	
            /**
             * \brief Retrieve file extension
             *
             * \return File extension
             */
            std::string getExtension() const;
	
	    private :
            std::string _file; ///< Full path and name string
	    };
	}
}

#endif
