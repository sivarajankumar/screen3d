 /*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2011 Ratouit Thomas                                    *
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

#ifndef SCREEN_MEMORY_ALGORITHMS_BUFFER_CONVERTER_H
#define SCREEN_MEMORY_ALGORITHMS_BUFFER_CONVERTER_H

#include <screen/memory/Buffer.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/memory/Export.h>

namespace screen {
    namespace memory {
		namespace algorithms {
			template <
				typename Input,
				typename Output,
				class Func>
			class TypedBufferConverter {
				SCREEN_DECL_CLASS(screen::memory::TypedBufferConverter)
			public:
				TypedBufferConverter(){
					SCREEN_DECL_CONSTRUCTOR(TypedBufferConverter);
				}
				TypedBufferConverter(const Func& func)
					:func(func){
					SCREEN_DECL_CONSTRUCTOR(TypedBufferConverter);
				}
				virtual ~TypedBufferConverter(){
					SCREEN_DECL_DESTRUCTOR(~TypedBufferConverter);
				}

				void convert(const screen::memory::TypedBuffer<Input>& input,
							 screen::memory::TypedBuffer<Output>& output){
					SCREEN_DECL_METHOD(convert);

					unsigned int inputSize = input.size();
					output.allocate(inputSize);

					const Input* inputTable = input.getAt(0);
					Output* outputTable = output.getAt(0);

					for(unsigned int i = 0; i<inputSize; i++){
						func(inputTable[i], outputTable[i]);
					}
				}

			private:
				Func func;
			};

			template <
				typename Input,
				typename Output>
			struct DefautTypedBufferConverterFunc{
				void operator ()(const Input& input, Output& output){
					output = input;
				}
			};

		}
	}
}

#endif
