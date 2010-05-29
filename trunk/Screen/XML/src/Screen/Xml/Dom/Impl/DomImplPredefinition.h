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

#ifndef SCREEN_DOM_IMPL_PREDEFINITION_H
#define SCREEN_DOM_IMPL_PREDEFINITION_H

#include <Screen/Utils/SmartPtr.h>
#include <Screen/Xml/Dom/DomPredefinition.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
			class DOMImplementationSourceImpl;
			typedef Screen::Utils::SmartPtr<DOMImplementationSourceImpl> DOMImplementationSourceImplPtr;
			class DOMImplementationImpl;
			typedef Screen::Utils::SmartPtr<DOMImplementationImpl> DOMImplementationImplPtr;
			class NodeImpl;
			typedef Screen::Utils::SmartPtr<NodeImpl> NodeImplPtr;
			class CharacterDataImpl;
			typedef Screen::Utils::SmartPtr<CharacterDataImpl> CharacterDataImplPtr;
			class AttrImpl;
			typedef Screen::Utils::SmartPtr<AttrImpl> AttrImplPtr;
			class ElementImpl;
			typedef Screen::Utils::SmartPtr<ElementImpl> ElementImplPtr;
			class TextImpl;
			typedef Screen::Utils::SmartPtr<TextImpl> TextImplPtr;
			class CommentImpl;
			typedef Screen::Utils::SmartPtr<CommentImpl> CommentImplPtr;
			class TypeInfoImpl;
			typedef Screen::Utils::SmartPtr<TypeInfoImpl> TypeInfoImplPtr;
			class UserDataHandlerImpl;
			typedef Screen::Utils::SmartPtr<UserDataHandlerImpl> UserDataHandlerImplPtr;
			class DOMErrorImpl;
			typedef Screen::Utils::SmartPtr<DOMErrorImpl> DOMErrorImplPtr;
			class DOMErrorHandlerImpl;
			typedef Screen::Utils::SmartPtr<DOMErrorHandlerImpl> DOMErrorHandlerImplPtr;
			class DOMLocatorImpl;
			typedef Screen::Utils::SmartPtr<DOMLocatorImpl> DOMLocatorImplPtr;
			class DOMConfigurationImpl;
			typedef Screen::Utils::SmartPtr<DOMConfigurationImpl> DOMConfigurationImplPtr;
			class CDATASectionImpl;
			typedef Screen::Utils::SmartPtr<CDATASectionImpl> CDATASectionImplPtr;
			class DocumentTypeImpl;
			typedef Screen::Utils::SmartPtr<DocumentTypeImpl> DocumentTypeImplPtr;
			class NotationImpl;
			typedef Screen::Utils::SmartPtr<NotationImpl> NotationImplPtr;
			class EntityImpl;
			typedef Screen::Utils::SmartPtr<EntityImpl> EntityImplPtr;
			class EntityReferenceImpl;
			typedef Screen::Utils::SmartPtr<EntityReferenceImpl> EntityReferenceImplPtr;
			class ProcessingInstructionImpl;
			typedef Screen::Utils::SmartPtr<ProcessingInstructionImpl> ProcessingInstructionImplPtr;
			class DocumentFragmentImpl;
			typedef Screen::Utils::SmartPtr<DocumentFragmentImpl> DocumentFragmentImplPtr;
			class DocumentImpl;
			typedef Screen::Utils::SmartPtr<DocumentImpl> DocumentImplPtr;
		}
	}
}

#endif