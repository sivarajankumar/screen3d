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

#ifndef SCREEN_DOM_EXCEPTION_H
#define SCREEN_DOM_EXCEPTION_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Export.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        class SCREEN_XML_EXPORT DOMException : public Screen::Utils::Exception {
	        public:
	            typedef enum{
	            	UNKNOW_ERROR = 0,
	                INDEX_SIZE_ERR = 1,
	                DOMSTRING_SIZE_ERR = 2,
	                HIERARCHY_REQUEST_ERR = 3,
	                WRONG_DOCUMENT_ERR = 4,
	                INVALID_CHARACTER_ERR = 5,
	                NO_DATA_ALLOWED_ERR = 6,
	                NO_MODIFICATION_ALLOWED_ERR = 7,
	                NOT_FOUND_ERR = 8,
	                NOT_SUPPORTED_ERR = 9,
	                INUSE_ATTRIBUTE_ERR = 10,
	                INVALID_STATE_ERR = 11,
	                SYNTAX_ERR = 12,
	                INVALID_MODIFICATION_ERR = 13,
	                NAMESPACE_ERR = 14,
	                INVALID_ACCESS_ERR = 15,
	                VALIDATION_ERR = 16,
	                TYPE_MISMATCH_ERR = 17
	            } ExceptionCode;
	
	            DOMException(const DOMString& reasonMsg);
	            DOMException(unsigned int code);
	            virtual ~DOMException() throw();
	
	            unsigned int code;
	        };
		}
	}
}

#endif
