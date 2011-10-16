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
/**
 * \file Screen/Fields/Field.cpp
 * \brief Field source code
 * \author
 */

#include <Screen/Fields/Field.h>

namespace Screen{
	namespace Fields{

		Field::Field()
			:_isVoid(true),_isValid(false){
			SCREEN_DECL_CONSTRUCTOR(Field)
		}

		Field::~Field(){
			SCREEN_DECL_DESTRUCTOR(Field)
		}
		
		bool Field::isVoid() const{
			SCREEN_DECL_METHOD(isVoid)
			return _isVoid;
		}
		
		bool Field::isValid() const{
			SCREEN_DECL_METHOD(isValid)
			return _isValid;
		}
	}
}
