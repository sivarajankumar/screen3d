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

#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include <Screen/Xml/Dom/Node.h>
#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen {
    namespace Xml {
        namespace Dom {
	        class SCREEN_XML_EXPORT Element : virtual public Node {
	        public:
	            Element();
	            ~Element();
	
	            virtual DOMString getTagName() = 0;
	            virtual DOMString getAttribute(const DOMString& name) = 0;
	            virtual void setAttribute(const DOMString& name,
	                                      const DOMString& value)
	            throw(DOMException) = 0;
	            virtual void removeAttribute(const DOMString& name)
	            throw(DOMException) = 0;
	            virtual AttrPtr getAttributeNode(const DOMString& name) = 0;
	            virtual AttrPtr setAttributeNode(const AttrPtr& newAttr)
	            throw(DOMException) = 0;
	            virtual AttrPtr removeAttributeNode(const AttrPtr& oldAttr)
	            throw(DOMException) = 0;
	            virtual NodeList getElementsByTagName(const DOMString& name) = 0;
	            virtual DOMString getAttributeNS(const DOMString& namespaceURI,
	                                             const DOMString& localName) = 0;
	            virtual void setAttributeNS(const DOMString& namespaceURI,
	                                        const DOMString& qualifiedName,
	                                        const DOMString& value)
	            throw(DOMException) = 0;
	            virtual void removeAttributeNS(const DOMString& namespaceURI,
	                                           const DOMString& localName)
	            throw(DOMException) = 0;
	            virtual AttrPtr getAttributeNodeNS(const DOMString& namespaceURI,
	                                             const DOMString& localName) = 0;
	            virtual AttrPtr setAttributeNodeNS(const AttrPtr& newAttr)
	            throw(DOMException) = 0;
	            virtual NodeList getElementsByTagNameNS(const DOMString& namespaceURI,
	                                                    const DOMString& localName) = 0;
	            virtual bool hasAttribute(const DOMString& name) = 0;
	            virtual bool hasAttributeNS(const DOMString& namespaceURI,
	                                        const DOMString& localName) = 0;
	            virtual TypeInfoPtr getSchemaTypeInto() = 0;
	            virtual void setIdAttribute(const DOMString& name,
	                                        bool isId) throw (DOMException) = 0;
	            virtual void setIdAttributeNS(const DOMString& namespaceURI,
	                                          const DOMString& localName,
	                                          bool isId) throw (DOMException) = 0;
	            virtual void setIdAttributeNode(const AttrPtr& idAttr,
	                                            bool isId) throw (DOMException) = 0;
	        };
        }
    }
}

#endif
