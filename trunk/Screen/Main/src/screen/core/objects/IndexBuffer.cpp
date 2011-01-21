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

#include <screen/core/objects/IndexBuffer.h>

namespace screen {
	namespace core {
		namespace objects {
			template <class T>
			SCREEN_MAIN_EXPORT IndexBuffer<T>::IndexBuffer(BufferBase* buffer)
				:Buffer<T>(buffer){
				SCREEN_DECL_CONSTRUCTOR(IndexBuffer)
			}
			
			template <class T>
			SCREEN_MAIN_EXPORT IndexBuffer<T>::~IndexBuffer(){
				SCREEN_DECL_DESTRUCTOR(~IndexBuffer)
			}
			
			template SCREEN_MAIN_EXPORT class IndexBuffer<unsigned short>;
			template SCREEN_MAIN_EXPORT class IndexBuffer<unsigned long>;
		}
	}
}
