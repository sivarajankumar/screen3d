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

#include <Screen/Xml/Dom/DomString.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        DOMStringList::DOMStringList() {}
	        DOMStringList::DOMStringList(const DOMStringList& other) {
	            strings = other.strings;
	        }
	        DOMStringList& DOMStringList::operator=(const DOMStringList& other) {
	            strings = other.strings;
	            return *this;
	        }
	        DOMStringList::~DOMStringList() {}
	        DOMString DOMStringList::item(unsigned long index) const {
	            if (index>=strings.size())
	                return "";
	            return strings[index];
	        }
	        unsigned long DOMStringList::getLength() const {
	            return (unsigned long) strings.size();
	        }
	        bool DOMStringList::contains(const DOMString& str) const {
	            for (unsigned int i=0; i<strings.size() ; i++) {
	                if (strings[i] == str)
	                    return true;
	            }
	            return false;
	        }
	        void DOMStringList::add(const DOMString& str) {
	            strings.push_back(str);
	        }
		}
	}
}
