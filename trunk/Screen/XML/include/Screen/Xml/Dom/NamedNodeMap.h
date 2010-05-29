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

#ifndef SCREEN_NAMED_NODE_MAP_H
#define SCREEN_NAMED_NODE_MAP_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        class SCREEN_XML_EXPORT NamedNodeMapEntry {
	        public:
	            NamedNodeMapEntry(const DOMString& namespaceURI, const DOMString& name, const NodePtr node);
	            NamedNodeMapEntry(const NamedNodeMapEntry& other);
	            NamedNodeMapEntry& operator=(const NamedNodeMapEntry& other);
	            virtual ~NamedNodeMapEntry();
	            void assign(const NamedNodeMapEntry& other);
	
	            DOMString namespaceURI;
	            DOMString name;
	            NodePtr node;
	        };
	
	        class SCREEN_XML_EXPORT NamedNodeMap {
	        public:
	            NamedNodeMap();
	            NamedNodeMap(const NamedNodeMap& other);
	            NamedNodeMap& operator=(const NamedNodeMap& other);
	            virtual ~NamedNodeMap();
	
	            virtual NodePtr getNamedItem(const DOMString& name);
	            virtual NodePtr setNamedItem(NodePtr arg) throw(DOMException);
	            virtual NodePtr removeNamedItem(const DOMString& name) throw(DOMException);
	            virtual NodePtr item(unsigned long index);
	            virtual unsigned long getLength();
	            virtual NodePtr getNamedItemNS(const DOMString& namespaceURI, const DOMString& localName);
	            virtual NodePtr setNamedItemNS(NodePtr arg) throw(DOMException);
	            virtual NodePtr removeNamedItemNS(const DOMString& namespaceURI, const DOMString& localName)
	            	throw(DOMException);
	        protected:
	            std::vector<NamedNodeMapEntry> entries;
	        };
		}
	}
}

#endif
