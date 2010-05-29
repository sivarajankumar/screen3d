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

#ifndef SCREEN_DOM_IMPLEMENTATION_H
#define SCREEN_DOM_IMPLEMENTATION_H

#include <Screen/Xml/Dom/DomObject.h>
#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        class SCREEN_XML_EXPORT DOMImplementation {
	        public:
	            DOMImplementation();
	            virtual ~DOMImplementation();
	            virtual bool hasFeature(const DOMString& feature, const DOMString& version) const = 0;
	            virtual DocumentTypePtr createDocumentType(const DOMString& qualifiedName,
	                    										  const DOMString& publicId,
	                    										  const DOMString& systemId)
	            	throw(DOMException) = 0;
	            virtual DocumentPtr createDocument(const DOMString& namespaceURI,
	            										  const DOMString& qualifiedName,
	            										  const DocumentTypePtr& doctype)
	            throw(DOMException) = 0;
	            virtual const DOMObjectPtr& getFeature(const DOMString& feature, const DOMString& version) const = 0;
	            virtual DOMObjectPtr& getFeature(const DOMString& feature, const DOMString& version) = 0;
	        };
	
	        class SCREEN_XML_EXPORT DOMImplementationList {
	        public:
	            DOMImplementationList();
	            DOMImplementationList(const DOMImplementationList& other);
	            DOMImplementationList& operator=(const DOMImplementationList& other);
	            virtual ~DOMImplementationList();
	            
	            virtual DOMImplementationPtr getDOMImplementation(unsigned long index) const;
	            virtual DOMImplementationPtr getDOMImplementation(unsigned long index);
	            virtual unsigned long getLength() const;
	        protected:
	            std::vector<DOMImplementationPtr>implementations;
	        };

	        class SCREEN_XML_EXPORT DOMImplementationSource {
	        public:
	            DOMImplementationSource();
	            virtual ~DOMImplementationSource();
	            virtual const DOMImplementationPtr& getDOMImplementation(const DOMString& features) const = 0;
	            virtual DOMImplementationPtr& getDOMImplementation(const DOMString& features) = 0;
	            virtual DOMImplementationList getDOMImplementationList(const DOMString& features) = 0;
	        };
		}
	}
}

#endif
