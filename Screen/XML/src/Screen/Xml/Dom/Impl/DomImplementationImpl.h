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

#ifndef SCREEN_DOM_IMPLEMENTATION_IMPL_H
#define SCREEN_DOM_IMPLEMENTATION_IMPL_H

#include <Screen/Xml/Dom/Impl/DomImplPredefinition.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
			class DOMImplementationSourceImpl : public DOMImplementationSource{
			public:
			    virtual DOMImplementationPtr getDOMImplementation(const DOMString& features);
			    virtual DOMImplementationList getDOMImplementationList(const DOMString& features);
			    DOMImplementationSourceImpl();
			    virtual ~DOMImplementationSourceImpl();
			protected:
			    DOMImplementationImplPtr domImpl;
			    DOMImplementationList domImplList;
			};
	
			class DOMImplementationImpl : public DOMImplementation{
			public:
			    DOMImplementationImpl();
			    virtual ~DOMImplementationImpl();
			    virtual bool hasFeature(const DOMString& feature, const DOMString& version);
			    virtual DocumentTypePtr createDocumentType(const DOMString& qualifiedName,
			                                     const DOMString& publicId,
			                                     const DOMString& systemId)
			                                     throw(DOMException);
			    virtual DocumentPtr createDocument(const DOMString& namespaceURI,
			                             const DOMString& qualifiedName,
			                             DocumentTypePtr doctype)
			                             throw(DOMException);
			    virtual DOMObjectPtr getFeature(const DOMString& feature,
			                             const DOMString& version);
			};
		}
	}
}

#endif
