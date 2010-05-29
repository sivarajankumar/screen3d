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

#ifndef SCREEN_NAME_PAIR_H
#define SCREEN_NAME_PAIR_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	        class SCREEN_XML_EXPORT NamePair {
	        public:
	            NamePair(const DOMString& namespaceURI, const DOMString& name);
	            NamePair(const NamePair& other);
	            NamePair& operator=(const NamePair& other);
	            virtual ~NamePair();
	
	            DOMString namespaceURI;
	            DOMString name;
	        };

	        class SCREEN_XML_EXPORT NameList {
	        public:
	            NameList();
	            NameList(const NameList& other);
	            NameList& operator=(const NameList& other);
	            virtual ~NameList();
	
	            virtual DOMString getName(unsigned long index) const;
	            virtual DOMString getNamespaceURI(unsigned long index) const;
	            virtual unsigned long getLength() const;
	            virtual bool contains(const DOMString& name) const;
	            virtual bool containsNS(const DOMString namespaceURI,const DOMString& name) const;
	        protected:
	            std::vector<NamePair> namePairs;
	        };
		}
	}
}

#endif
