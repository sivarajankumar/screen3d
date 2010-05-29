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

#ifndef SCREEN_DOM_PREDEFINETION_H
#define SCREEN_DOM_PREDEFINETION_H

#include <Screen/Utils/SmartPtr.h>

namespace Screen{
	namespace Xml{
		namespace Dom{
	    	class DocumentType;
	    	typedef Screen::Utils::SmartPtr<DocumentType> DocumentTypePtr;
	    	class DOMImplementation;
	    	typedef Screen::Utils::SmartPtr<DOMImplementation> DOMImplementationPtr;
	    	class Element;
	    	typedef Screen::Utils::SmartPtr<Element> ElementPtr;
	    	class Text;
	    	typedef Screen::Utils::SmartPtr<Text> TextPtr;
	    	class Comment;
	    	typedef Screen::Utils::SmartPtr<Comment> CommentPtr;
	    	class CDATASection;
	    	typedef Screen::Utils::SmartPtr<CDATASection> CDATASectionPtr;
	    	class ProcessingInstruction;
	    	typedef Screen::Utils::SmartPtr<ProcessingInstruction> ProcessingInstructionPtr;
	    	class Attr;
	    	typedef Screen::Utils::SmartPtr<Attr> AttrPtr;
	    	class EntityReference;
	    	typedef Screen::Utils::SmartPtr<EntityReference> EntityReferencePtr;
	    	class DOMConfiguration;
	    	typedef Screen::Utils::SmartPtr<DOMConfiguration> DOMConfigurationPtr;
	    	class TypeInfo;
	    	typedef Screen::Utils::SmartPtr<TypeInfo> TypeInfoPtr;
	    	typedef void DOMUserData;
        	typedef Screen::Utils::SmartPtr<DOMUserData> DOMUserDataPtr;
        	typedef void DOMObject;
        	typedef Screen::Utils::SmartPtr<DOMObject> DOMObjectPtr;
        	class DOMLocator;
        	typedef Screen::Utils::SmartPtr<DOMLocator> DOMLocatorPtr;
        	class NodeList;
        	typedef Screen::Utils::SmartPtr<NodeList> NodeListPtr;
			class Node;
			typedef Screen::Utils::SmartPtr<Node> NodePtr;
			class NamedNodeMap;
			typedef Screen::Utils::SmartPtr<NamedNodeMap> NamedNodeMapPtr;
			class Document;
			typedef Screen::Utils::SmartPtr<Document> DocumentPtr;
			class DocumentFragment;
			typedef Screen::Utils::SmartPtr<DocumentFragment> DocumentFragmentPtr;
			class UserDataHandler;
			typedef Screen::Utils::SmartPtr<UserDataHandler> UserDataHandlerPtr;
			class DOMStringList;
			typedef Screen::Utils::SmartPtr<DOMStringList> DOMStringListPtr;
		}
	}
}

#endif
