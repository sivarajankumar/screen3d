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

#ifndef SCREEN_NODE_H
#define SCREEN_NODE_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        class SCREEN_XML_EXPORT Node {
	        public:
	            typedef enum {
	                ELEMENT_NODE = 1,
	                ATTRIBUTE_NODE = 2,
	                TEXT_NODE = 3,
	                CDATA_SECTION_NODE = 4,
	                ENTITY_REFERENCE_NODE = 5,
	                ENTITY_NODE = 6,
	                PROCESSING_INSTRUCTION_NODE = 7,
	                COMMENT_NODE = 8,
	                DOCUMENT_NODE = 9,
	                DOCUMENT_TYPE_NODE = 10,
	                DOCUMENT_FRAGMENT_NODE = 11,
	                NOTATION_NODE = 12
	            } NodeType;                
	            
	            typedef enum {
	                DOCUMENT_POSITION_DISCONNECTED = 0x01,
	                DOCUMENT_POSITION_PRECEDING = 0x02,
	                DOCUMENT_POSITION_FOLLOWING = 0x04,
	                DOCUMENT_POSITION_CONTAINS = 0x08,
	                DOCUMENT_POSITION_CONTAINED_BY = 0x10,
	                DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20
	            } DocumentPosition;
	
	            Node();
	            virtual ~Node();
	
	            virtual DOMString getNodeName() = 0;
	            virtual DOMString getNodeValue() throw (DOMException) = 0;
	            virtual void setNodeValue(const DOMString& val) throw (DOMException) = 0;
	            virtual unsigned short getNodeType() = 0;
	            virtual NodePtr getParentNode() = 0;
	            virtual NodeList getChildNodes() = 0;
	            virtual NodePtr getFirstChild() = 0;
	            virtual NodePtr getLastChild() = 0;
	            virtual NodePtr getPreviousSibling() = 0;
	            virtual NodePtr getNextSibling() = 0;
	            virtual NamedNodeMap& getAttributes() = 0;
	            virtual DocumentPtr getOwnerDocument() = 0;
	            virtual NodePtr insertBefore(const NodePtr newChild, const NodePtr refChild)
	            throw(DOMException) = 0;
	            virtual NodePtr replaceChild(const NodePtr newChild, const NodePtr oldChild)
	            throw(DOMException) = 0;
	            virtual NodePtr removeChild(const NodePtr oldChild)
	            throw(DOMException) = 0;
	            virtual NodePtr appendChild(const NodePtr newChild)
	            throw(DOMException) = 0;
	            virtual bool hasChildNodes() = 0;
	            virtual NodePtr cloneNode(bool deep) = 0;
	            virtual void normalize() = 0;
	            virtual bool isSupported(const DOMString& feature, const DOMString& version) = 0;
	            virtual DOMString getNamespaceURI() = 0;
	            virtual DOMString getPrefix() = 0;
	            virtual void setPrefix(const DOMString& val) throw(DOMException) = 0;
	            virtual DOMString getLocalName() = 0;
	            virtual bool hasAttributes() = 0;
	            virtual DOMString getBaseURI() = 0;
	
	            virtual unsigned short compareDocumentPosition(const NodePtr other) = 0;
	            virtual DOMString getTextContext() throw(DOMException) = 0;
	            virtual void setTextContext(const DOMString& val) throw(DOMException) = 0;
	            virtual DOMString lookupPrefix(const DOMString& namespaceURI) =0;
	            virtual bool isDefaultNamespace(const DOMString& namespaceURI) =0;
	            virtual DOMString lookupNamespaceURI(const DOMString& prefix) =0;
	            virtual bool isEqualNode(const NodePtr node) =0;
	            virtual DOMObjectPtr getFeature(const DOMString& feature, const DOMString& version) =0;
	            virtual DOMUserDataPtr setUserData(const DOMString& key,
	                                             		  const DOMUserDataPtr& data,
	                                             		  const UserDataHandlerPtr& handler) =0;
	            virtual DOMUserDataPtr getUserData(const DOMString& namespaceURI) =0;
	        };
	
	        class SCREEN_XML_EXPORT NodeList {
	            friend class NodeImpl;
	            friend class ElementImpl;
	        public:
	            NodeList();
	            NodeList(const NodeList& other);
	            NodeList& operator=(const NodeList& other);
	            virtual ~NodeList();
	
	            virtual NodePtr item(unsigned long index);
	            virtual unsigned long getLength();
	            virtual void clear();
	        protected:
	            virtual void add(const NodePtr node);
	
	            std::vector<NodePtr> nodes;
	        };
		}
	}
}

#endif
