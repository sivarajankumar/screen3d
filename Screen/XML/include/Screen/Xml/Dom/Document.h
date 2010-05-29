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

#ifndef SCREEN_DOCUMENT_H
#define SCREEN_DOCUMENT_H

#include <Screen/Xml/Dom/Node.h>
#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen {
    namespace Xml {
        namespace Dom {
	        class SCREEN_XML_EXPORT Document : virtual public Node {
	        public:
	            Document();
	            virtual ~Document();
	
	            virtual DocumentTypePtr getDoctype() = 0;
	            virtual DOMImplementationPtr getImplementation() = 0;
	            virtual ElementPtr getDocumentElement() = 0;
	            virtual ElementPtr createElement(const DOMString& tagName)
	            throw(DOMException) = 0;
	            virtual DocumentFragmentPtr createDocumentFragment() = 0;
	            virtual TextPtr createTextNode(const DOMString& data) = 0;
	            virtual CommentPtr createComment(const DOMString& data) = 0;
	            virtual CDATASectionPtr createCDATASection(const DOMString& data)
	            throw(DOMException) = 0;
	            virtual ProcessingInstructionPtr createProcessingInstruction(const DOMString& target,
	                    const DOMString& data)
	            throw(DOMException) = 0;
	            virtual AttrPtr createAttribute(const DOMString& name)
	            throw(DOMException) = 0;
	            virtual EntityReferencePtr createEntityReference(const DOMString& name)
	            throw(DOMException) = 0;
	            virtual NodeList getElementsByTagName(const DOMString& tagname) = 0;
	            virtual NodePtr importNode(const NodePtr importedNode,
	                                     bool deep)
	            throw(DOMException) = 0;
	            virtual ElementPtr createElementNS(const DOMString& namespaceURI,
	                                             const DOMString& qualifiedName)
	            throw(DOMException) = 0;
	            virtual AttrPtr createAttributeNS(const DOMString& namespaceURI,
	                                            const DOMString& qualifiedName)
	            throw(DOMException) = 0;
	            virtual NodeList getElementsByTagNameNS(const DOMString& namespaceURI,
	                                                    const DOMString& localName) = 0;
	            virtual ElementPtr getElementById(const DOMString& elementId) = 0;
	            virtual DOMString getInputEncoding() = 0;
	            virtual DOMString getXmlEncoding() = 0;
	            virtual bool getXmlStandalone() = 0;
	            virtual void setXmlStandalone(bool val) throw (DOMException) = 0;
	            virtual DOMString getXmlVersion() = 0;
	            virtual void setXmlVersion(const DOMString& version) throw (DOMException) = 0;
	            virtual bool getStrictErrorChecking() = 0;
	            virtual void setStrictErrorChecking(bool val) = 0;
	            virtual DOMString getDocumentURI() = 0;
	            virtual void setDocumentURI(const DOMString& uri) = 0;
	            virtual NodePtr adoptNode(const NodePtr source) throw (DOMException) = 0;
	            virtual DOMConfigurationPtr getDomConfig() = 0;
	            virtual void normalizeDocument() = 0;
	            virtual NodePtr renameNode(const NodePtr n,
	                                     const DOMString& namespaceURI,
	                                     const DOMString& qualifiedName)
	            throw (DOMException) = 0;
	        };
        }
    }
}

#endif

