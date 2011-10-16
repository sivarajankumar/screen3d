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
 * \file Screen/Fields/FieldBool.cpp
 * \brief FieldBool source code
 * \author
 */

#include <Screen/Fields/FieldBool.h>
#include <cstring>

namespace screen{
	namespace fields{
		FieldBool::FieldBool()
			:Field(){
			SCREEN_DECL_CONSTRUCTOR(FieldBool)
		}
		FieldBool::~FieldBool(){
			SCREEN_DECL_DESTRUCTOR(FieldBool)
		}
		
		std::string FieldBool::getAsString() const{
			if(isVoid() || !isValid())
				return "false";
			else
				return _value ? "true" : "false";
		}
		
		bool FieldBool::get() const{
			return _value;
		}
		
		void FieldBool::set(const std::string& value){
			if(value == "true"){
				_value = true;
				_isValid = true;
			}
			else if(value == "false"){
				_value = false;
				_isValid = true;
			}
			else{
				_value = false;
				_isValid = false;
			}	
			_isVoid = false;
		}
		
		void FieldBool::set(const char* value){
			if(value == NULL){
				_value = false;
				_isValid = false;
				_isVoid = true;
			}
			else if(::strcmp(value,"true") == 0){
				_value = true;
				_isValid = true;
				_isVoid = false;
			}
			else if(::strcmp(value,"false") == 0){
				_value = false;
				_isValid = true;
				_isVoid = false;
			}
			else{
				_value = false;
				_isValid = false;
				_isVoid = false;
			}	
		}
		
		void FieldBool::set(char* value){
			if(value == NULL){
				_value = false;
				_isValid = false;
				_isVoid = true;
			}
			else if(::strcmp(value,"true") == 0){
				_value = true;
				_isValid = true;
				_isVoid = false;
			}
			else if(::strcmp(value,"false") == 0){
				_value = false;
				_isValid = true;
				_isVoid = false;
			}
			else{
				_value = false;
				_isValid = false;
				_isVoid = false;
			}
		}
		
		void FieldBool::set(bool value){
			_value = value;
			_isValid = true;
			_isVoid = false;
		}
	}
}
