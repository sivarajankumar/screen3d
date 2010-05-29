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

#include <Screen/Xml/Dom/NamePair.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        NamePair::NamePair(const DOMString& namespaceURI, const DOMString& name)
	                :namespaceURI(namespaceURI),name(name) {}
	        NamePair::NamePair(const NamePair& other)
	                :namespaceURI(other.namespaceURI),name(other.name) {}
	        NamePair& NamePair::operator=(const NamePair& other) {
	            namespaceURI = other.namespaceURI;
	            name = other.name;
	            return *this;
	        }
	        NamePair::~NamePair() {}
	
	        NameList::NameList() {}
	        NameList::NameList(const NameList& other) {
	            namePairs = other.namePairs;
	        }
	        NameList& NameList::operator=(const NameList& other) {
	            namePairs = other.namePairs;
	            return *this;
	        }
	        NameList::~NameList() {}
	        DOMString NameList::getName(unsigned long index) const {
	            if (index>=namePairs.size())
	                return "";
	            return namePairs[index].name;
	        }
	        DOMString NameList::getNamespaceURI(unsigned long index) const {
	            if (index>=namePairs.size())
	                return "";
	            return namePairs[index].namespaceURI;
	        }
	        unsigned long NameList::getLength() const {
	            return (unsigned long)namePairs.size();
	        }
	        bool NameList::contains(const DOMString& name) const {
	            for (unsigned int i=0; i<namePairs.size() ; i++) {
	                if (namePairs[i].name == name )
	                    return true;
	            }
	            return false;
	        }
	        bool NameList::containsNS(const DOMString namespaceURI,const DOMString& name) const {
	            for (unsigned int i=0; i<namePairs.size() ; i++) {
	                if (namePairs[i].namespaceURI == namespaceURI ||
	                        namePairs[i].name         == name           )
	                    return true;
	            }
	            return false;
	        }
		}
	}
}
