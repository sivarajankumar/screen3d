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
			class NodeImpl : virtual public Node{
			    friend class DocumentImpl;
			public:
			    virtual DOMString getNodeName();
			    virtual DOMString getNodeValue() throw (DOMException);
			    virtual void setNodeValue(const DOMString& val) throw (DOMException);
			    virtual unsigned short getNodeType();
			    virtual NodePtr getParentNode();
			    virtual NodeList getChildNodes();
			    virtual NodePtr getFirstChild();
			    virtual NodePtr getLastChild();
			    virtual NodePtr getPreviousSibling();
			    virtual NodePtr getNextSibling();
			    virtual NamedNodeMap& getAttributes();
			    virtual DocumentPtr getOwnerDocument();
			    virtual NodePtr insertBefore(const NodePtr newChild,
			                       const NodePtr refChild)
			                       throw(DOMException);
			    virtual NodePtr replaceChild(const NodePtr newChild,
			                       const NodePtr oldChild)
			                       throw(DOMException);
			    virtual NodePtr removeChild(const NodePtr oldChild)
			                      throw(DOMException);
			    virtual NodePtr appendChild(const NodePtr newChild)
			                      throw(DOMException);
			    virtual bool hasChildNodes();
			    virtual NodePtr cloneNode(bool deep);
			    virtual void normalize();
			    virtual bool isSupported(const DOMString& feature,
			                     const DOMString& version);
			    virtual DOMString getNamespaceURI();
			    virtual DOMString getPrefix();
			    virtual void setPrefix(const DOMString& val) throw(DOMException);
			    virtual DOMString getLocalName();
			    virtual bool hasAttributes();
			    virtual DOMString getBaseURI();
			    virtual unsigned short compareDocumentPosition(const NodePtr other);
			    virtual DOMString getTextContent() throw(DOMException);
			    virtual void setTextContent(const DOMString &val) throw(DOMException);
			    virtual DOMString lookupPrefix(const DOMString &namespaceURI);
			    virtual bool isDefaultNamespace(const DOMString &namespaceURI);
			    virtual DOMString lookupNamespaceURI(const DOMString &prefix);
			    virtual bool isEqualNode(const NodePtr node);
			    virtual DOMObject *getFeature(const DOMString &feature,
			                                  const DOMString &version);
			    virtual DOMUserData *setUserData(const DOMString &key,
			                                     const DOMUserData *data,
			                                     const UserDataHandler *handler);
			    virtual DOMUserData *getUserData(const DOMString &key);
	
			    virtual void bindingsAdd(const DOMString &prefix, const DOMString &namespaceURI){
			        bindings[prefix] = namespaceURI;
			    }
			    virtual void bindingsClear(){
			        bindings.clear();
			    }
			    DOMString bindingsFind(const DOMString &prefix){
			        std::map<DOMString, DOMString>::iterator iter = bindings.find(prefix);
			        if (iter != bindings.end()){
			            DOMString ret = iter->second;
			            return ret;
			        }
			        if (parent.get()){
			            DOMString ret = parent->bindingsFind(prefix);
			            if (ret.size() > 0)
			                return ret;
			        }
			        return "";
			    }
	
			    virtual void setNodeName(const DOMString &qualifiedName);
			    virtual void setNamespaceURI(const DOMString &theNamespaceURI);
			    DOMString lookupNamespacePrefix(const DOMString &namespaceURI,
			                                    NodePtr originalElement);
			    NodeImpl();
			    NodeImpl(const NodeImpl &other);
			    NodeImpl &operator=(const NodeImpl &other);
			    NodeImpl(DocumentImplPtr owner);
			    NodeImpl(DocumentImplPtr owner, const DOMString &nodeName);
			    NodeImpl(DocumentImplPtr owner, const DOMString &namespaceURI,
				               const DOMString &nodeName);
			    virtual ~NodeImpl();
			    void assign(const NodeImpl &other);
			protected:
			    void init();
			    unsigned short nodeType;
			    NodeImplPtr parent;
			    NodeImplPtr prev;
			    NodeImplPtr next;
			    DOMUserData *userData;
			    DOMString prefix;
			    DOMString localName;
			    DOMString nodeName;
			    DOMString namespaceURI;
			    DOMString baseURI;
			    DOMString nodeValue;
			    NodeImplPtr firstChild;
			    NodeImplPtr lastChild;
			    DocumentImplPtr ownerDocument;
			    NamedNodeMap attributes;
			    class UserDataEntry{
			    public:
			        UserDataEntry(const DOMString       &theKey,
			                      const DOMUserData     *theData,
			                      const UserDataHandler *theHandler){
			            next    = NULL;
			            key     = theKey;
			            data    = (DOMUserData *)theData;
			            handler = (UserDataHandler *)theHandler;
			        }
	
			        virtual ~UserDataEntry(){
			            //delete anything after me, too
			            if (next)
			                delete next;
			        }
	
			        UserDataEntry   *next;
			        DOMString       key;
			        DOMUserData     *data;
			        UserDataHandler *handler;
			    };
	
			    UserDataEntry *userDataEntries;
			    TypeInfo typeInfo;
			    std::map<DOMString, DOMString> bindings;
			};

		}
	}
}

#endif
