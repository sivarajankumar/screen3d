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

#ifndef SCREEN_DOM_ERROR_H
#define SCREEN_DOM_ERROR_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen {
    namespace Xml {
        namespace Dom {
	        class SCREEN_XML_EXPORT DOMError {
	        public:
	            DOMError();
	            virtual ~DOMError();
	
	            typedef enum{
	                DOMERROR_SEVERITY_WARNING = 1,
	                DOMERROR_SEVERITY_ERROR = 2,
	                DOMERROR_SEVERITY_FATAL_ERROR = 3
	            } ErrorSeverity;
	
	            virtual unsigned short getSeverity() =0;
	            virtual DOMString getMessage() =0;
	            virtual DOMString getType() =0;
	            virtual DOMObjectPtr getRelatedException() =0;
	            virtual DOMObjectPtr getRelatedData() =0;
	            virtual DOMLocatorPtr getLocation() =0;
	        };
	
	        typedef Screen::Utils::SmartPtr<DOMError> DOMErrorPtr;

	        class SCREEN_XML_EXPORT DOMErrorHandler {
	        public:
	            DOMErrorHandler();
	            virtual ~DOMErrorHandler();
	
	            virtual bool handleError(const DOMErrorPtr error) =0;
	        };
        }
    }
}

#endif
