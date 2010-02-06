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

#ifndef SCREEN_INDEX_BUFFER_H
#define SCREEN_INDEX_BUFFER_H

#include <Screen/Core/Objects/Buffer.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Utils/Export.h>

namespace Screen {
	namespace Core {
		namespace Objects {
		
			/**
			 @brief
			 	This class defines a index buffer for the render system.
			 @remarks
			 	Create an index buffer from the API by using
			 	Renderer::createIndexBuffer method.
			 	Send the index buffer to the API by using
			 	Renderer::setIndexBuffer method.
			 */
			template<class T>
			class SCREEN_EXPORT IndexBuffer : public Buffer<T> {
				SCREEN_DECL_CLASS(Screen::Core::Object::IndexBuffer)
			public:
				IndexBuffer(BufferBase* buffer);
				~IndexBuffer();
				
				typedef Screen::Utils::SmartPtr<IndexBuffer<T> > SmartPtr;
			};
		}
	}
}

#endif
