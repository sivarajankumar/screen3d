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
/**
 * \file screen/memory/algorithms/BufferConverter.h
 * \brief Buffer convertion algorithms header file
 * \author
 *
 */
#ifndef SCREEN_MEMORY_ALGORITHMS_BUFFER_CONVERTER_H
#define SCREEN_MEMORY_ALGORITHMS_BUFFER_CONVERTER_H

#include <screen/memory/Buffer.h>
#include <screen/memory/TypedBuffer.h>
#include <screen/utils/Declaration.h>
#include <screen/memory/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all memory classes
	 */
	namespace memory {
		/**
		 * Namespace for all algorithms classes
		 */
		namespace algorithms {

			/**
			 * \brief Algorithm for generic typed buffer convertion.
			 * \tparam Input class parameter of the origin typed buffer
			 * \tparam Output class parameter of the target typed buffer
			 * \tparam Func convertion functor between Input and Output instancies
			 */
			template <  typename Input,
						typename Output,
						class Func>
			class TypedBufferConverter {
				SCREEN_DECL_CLASS(screen::memory::TypedBufferConverter)
			public:

				/**
				 * \brief Default constructor. Create a default functor instance.
				 */
				TypedBufferConverter(){
					SCREEN_DECL_CONSTRUCTOR(TypedBufferConverter);
				}

				/**
				 * \brief Constructor with specified functor instance.
				 */
				TypedBufferConverter(const Func& iFunc)
					:_func(iFunc){
					SCREEN_DECL_CONSTRUCTOR(TypedBufferConverter);
				}

				/**
				 * \brief Destructor.
				 */
				virtual ~TypedBufferConverter(){
					SCREEN_DECL_DESTRUCTOR(~TypedBufferConverter);
				}

				/**
				 * \brief Main convertion method.
				 *
				 * Completely convert a Input typed buffer into an output one.
				 *
				 * \param[in] iInput origin typed buffer
				 * \param[out] oOutput target typed buffer
				 */
				void convert(const screen::memory::TypedBuffer<Input>& iInput,
							 screen::memory::TypedBuffer<Output>& oOutput){
					SCREEN_DECL_METHOD(convert);

					//preallocate target memory
					unsigned int aInputSize = iInput.size();
					oOutput.allocate(aInputSize);

					//retrieve pointers to the beginning of buffers
					const Input* aInputTable = iInput.getAt(0);
					Output* aOutputTable = oOutput.getAt(0);

					//convert each instance
					for(unsigned int i = 0; i<aInputSize; i++){
						_func(aInputTable[i], aOutputTable[i]);
					}
				}

			private:
				Func _func; ///< Convertion functor.
			};


			/**
			 * \brief Default typed buffer convertion functor.
			 * \tparam Input class parameter of the origin typed buffer
			 * \tparam Output class parameter of the target typed buffer
			 */
			template <  typename Input,
						typename Output>
			struct DefautTypedBufferConverterFunc{

				/**
				 * \brief Convertion operator.
				 *
				 * Completely convert a Input instance into an output instance.
				 *
				 * \param[in] iInput origin instance
				 * \param[out] oOutput target instance
				 */
				void operator ()(const Input& iInput, Output& oOutput){
					oOutput = iInput;
				}
			};
		}
	}
}

#endif
