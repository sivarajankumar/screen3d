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

#ifndef SCREEN_INDEX_BUFFER_HANDLER_H
#define SCREEN_INDEX_BUFFER_HANDLER_H

#include <screen/core/objects/IndexBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>
#include <screen/utils/Any.h>

namespace screen{
	namespace core{
		namespace objects{
			class SCREEN_MAIN_EXPORT IndexBufferHandler{
				SCREEN_DECL_CLASS(screen::core::objects::IndexBufferHandler)
			public:
				IndexBufferHandler();
				
				template<class T>
				IndexBufferHandler(const typename IndexBuffer<T>::SmartPtr& vb)
					:any(vb){
					SCREEN_DECL_CONSTRUCTOR(IndexBufferHandler)
				}
				
				template<class T>
				IndexBufferHandler(IndexBuffer<T>* vb)
					:any(){
					SCREEN_DECL_CONSTRUCTOR(IndexBufferHandler)
					typename IndexBuffer<T>::SmartPtr sp = vb;
					any = sp;
				}
				
				template<class T>
				IndexBufferHandler& operator = (const typename IndexBuffer<T>::SmartPtr& vb){
					SCREEN_DECL_METHOD(operator =)
					any = vb;
				}
				
				template<class T>
				IndexBufferHandler& operator = (IndexBuffer<T>* vb){
					SCREEN_DECL_METHOD(operator =)
					typename IndexBuffer<T>::SmartPtr sp = vb;
					any = sp;
				}
				
				template<class T>
				typename IndexBuffer<T>::SmartPtr get() const{
					SCREEN_DECL_METHOD(get)
					if(screen::utils::any_cast<typename IndexBuffer<T>::SmartPtr>(&any) == NULL)
						return NULL;
					else
						return screen::utils::any_cast<typename IndexBuffer<T>::SmartPtr>(any);
				}
				
				template<class T>
				bool isValid() const{
					SCREEN_DECL_METHOD(get)
					return screen::utils::any_cast<typename IndexBuffer<T>::SmartPtr>(&any) != NULL;
				}
				
				typedef screen::utils::SmartPtr<IndexBufferHandler> SmartPtr;
				
			protected:
				screen::utils::Any any;
			};
		}
	}
}

#endif
