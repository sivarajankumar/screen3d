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

#include <Screen/Xml/Dom/NamedNodeMap.h>
#include <Screen/Xml/Dom/Node.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        NamedNodeMapEntry::NamedNodeMapEntry(const DOMString& namespaceURI, const DOMString& name, const NodePtr node)
	                :namespaceURI(namespaceURI),name(name),node((NodePtr) node) {}
	        NamedNodeMapEntry::NamedNodeMapEntry(const NamedNodeMapEntry& other) {
	            assign(other);
	        }
	        NamedNodeMapEntry& NamedNodeMapEntry::operator=(const NamedNodeMapEntry& other) {
	            assign(other);
	            return *this;
	        }
	        NamedNodeMapEntry::~NamedNodeMapEntry() {}
	        void NamedNodeMapEntry::assign(const NamedNodeMapEntry& other) {
	            namespaceURI = other.namespaceURI;
	            name = other.name;
	            node = other.node;
	        }
	        NamedNodeMap::NamedNodeMap() {}
	        NamedNodeMap::NamedNodeMap(const NamedNodeMap& other) {
	            entries = other.entries;
	        }
	        NamedNodeMap& NamedNodeMap::operator=(const NamedNodeMap& other) {
	            entries = other.entries;
	            return *this;
	        }
	        NamedNodeMap::~NamedNodeMap() {}
	
	        NodePtr NamedNodeMap::getNamedItem(const DOMString& name) {
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->name == name) {
	                    NodePtr node = iter->node;
	                    return node;
	                }
	            }
	            return NULL;
	        }
	
	        NodePtr NamedNodeMap::setNamedItem(NodePtr arg) throw(DOMException) {
	            if (!arg)
	                return NULL;
	            DOMString namespaceURI = arg->getNamespaceURI();
	            DOMString name         = arg->getNodeName();
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->name == name) {
	                    NodePtr node = iter->node;
	                    iter->node = arg;
	                    return node;
	                }
	            }
	            NamedNodeMapEntry entry(namespaceURI, name, arg);
	            entries.push_back(entry);
	            return arg;
	        }
	
	        NodePtr NamedNodeMap::removeNamedItem(const DOMString& name) throw(DOMException) {
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->name == name) {
	                    NodePtr node = iter->node;
	                    entries.erase(iter);
	                    return node;
	                }
	            }
	            return NULL;
	        }
	
	        NodePtr NamedNodeMap::item(unsigned long index) {
	            if (index>=entries.size())
	                return NULL;
	            return entries[index].node;
	        }
	
	        unsigned long NamedNodeMap::getLength() {
	            return (unsigned long)entries.size();
	        }
	
	        NodePtr NamedNodeMap::getNamedItemNS(const DOMString& namespaceURI,
	                                     const DOMString& localName) {
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->namespaceURI == namespaceURI && iter->name == localName) {
	                    NodePtr node = iter->node;
	                    return node;
	                }
	            }
	            return NULL;
	        }
	
	        NodePtr NamedNodeMap::setNamedItemNS(NodePtr arg) throw(DOMException) {
	            if (!arg)
	                return NULL;
	            DOMString namespaceURI = arg->getNamespaceURI();
	            DOMString name = arg->getNodeName();
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->namespaceURI == namespaceURI && iter->name == name) {
	                    NodePtr node = iter->node;
	                    iter->node = arg;
	                    return node;
	                }
	            }
	            NamedNodeMapEntry entry(namespaceURI, name, arg);
	            entries.push_back(entry);
	            return arg;
	        }
	
	        NodePtr NamedNodeMap::removeNamedItemNS(const DOMString& namespaceURI,
	                                        const DOMString& localName)
	        throw(DOMException) {
	            std::vector<NamedNodeMapEntry>::iterator iter;
	            for (iter = entries.begin() ; iter!=entries.end() ; iter++) {
	                if (iter->namespaceURI == namespaceURI && iter->name == localName) {
	                    NodePtr node = iter->node;
	                    entries.erase(iter);
	                    return node;
	                }
	            }
	            return NULL;
	        }
		}
	}
}
