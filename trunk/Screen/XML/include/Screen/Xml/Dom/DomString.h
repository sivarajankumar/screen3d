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

#ifndef SCREEN_DOM_STRING_H
#define SCREEN_DOM_STRING_H

#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>
#include <string>

namespace Screen{
	namespace Xml{
		namespace Dom{
			typedef std::string DOMString;
			
            class SCREEN_XML_EXPORT DOMStringList {
            public:
                DOMStringList();
                DOMStringList(const DOMStringList& other);
                DOMStringList& operator=(const DOMStringList& other);
                virtual ~DOMStringList();

                virtual DOMString item(unsigned long index) const;
                virtual unsigned long getLength() const;
                virtual bool contains(const DOMString& str) const;
            protected:
                virtual void add(const DOMString& str);

                std::vector<DOMString> strings;
            };
		}
	}
}

#endif
