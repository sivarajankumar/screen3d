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

#ifndef SCREEN_TYPE_INFO_H
#define SCREEN_TYPE_INFO_H

#include <Screen/Xml/Dom/DomString.h>
#include <Screen/Xml/Dom/DomException.h>
#include <Screen/Xml/Dom/DomPredefinition.h>
#include <Screen/Xml/Export.h>

namespace Screen {
    namespace Xml {
        namespace Dom {
	        class SCREEN_XML_EXPORT TypeInfo {
	        public:
	            TypeInfo();
	            virtual ~TypeInfo();
	
	            virtual DOMString getTypeName() =0;
	            virtual DOMString getTypeNamespace() =0;
	
	            typedef enum{
	                DERIVATION_RESTRICTION = 0x00000001,
	                DERIVATION_EXTENSION = 0x00000002,
	                DERIVATION_UNION = 0x00000004,
	                DERIVATION_LIST = 0x00000008
	            } DerivationMethod;
	
	            virtual bool isDerivedFrom(const DOMString& typeNamespaceArg,
	                                       const DOMString& typeNameArg,
	                                       DerivationMethod derivationMethod) =0;
	        };
        }
    }
}

#endif
