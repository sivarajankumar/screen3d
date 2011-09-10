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

#ifndef SCREEN_INDEX_BUFFER_INTERPRETER_H
#define SCREEN_INDEX_BUFFER_INTERPRETER_H

#include <screen/utils/Any.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

namespace screen{
	namespace core{
		namespace objects{
			template <class Func>
			class IndexBufferInterpreter{
				SCREEN_DECL_CLASS(screen::core::objects::IndexBufferInterpreter);
			public:
				IndexBufferInterpreter(){

				}

				IndexBufferInterpreter(const Func& functor)
					:functor(functor){

				}

				~IndexBufferInterpreter(){

				}

				void operator() (screen::utils::Any& buffer){
					SCREEN_DECL_METHOD(operator());
					screen::memory::TypedBuffer<unsigned short>* shortBuffer =
							screen::utils::any_cast<screen::memory::TypedBuffer<unsigned short> >
							(&buffer);
					if(shortBuffer != NULL)
					{
						functor(*shortBuffer);
					}
					else
					{
						screen::memory::TypedBuffer<unsigned long>* longBuffer =
								screen::utils::any_cast<screen::memory::TypedBuffer<unsigned long> >
								(&buffer);
						if(longBuffer != NULL){
							functor(*longBuffer);
						}
					}
				}

				void operator() (const screen::utils::Any& buffer){
					SCREEN_DECL_METHOD(operator());
					const screen::memory::TypedBuffer<unsigned short>* shortBuffer =
							screen::utils::any_cast<screen::memory::TypedBuffer<unsigned short> >
							(&buffer);
					if(shortBuffer != NULL)
					{
						functor(*shortBuffer);
					}
					else
					{
						const screen::memory::TypedBuffer<unsigned long>* longBuffer =
								screen::utils::any_cast<screen::memory::TypedBuffer<unsigned long> >
								(&buffer);
						if(longBuffer != NULL){
							functor(*longBuffer);
						}
					}
				}

			private:
				Func functor;
			};
		}
	}
}

#endif

