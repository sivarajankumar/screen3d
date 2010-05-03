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

#ifndef SCREEN_FIELD_H
#define SCREEN_FIELD_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Fields/Export.h>
#include <string>

namespace Screen{
	namespace Fields{
		class SCREEN_FIELDS_EXPORT Field{
			SCREEN_DECL_CLASS(Screen::Fields::Field)
		public:
			virtual bool isVoid() const;
			virtual bool isValid() const;
			
			virtual std::string getAsString() const = 0;
			
			virtual void set(const std::string& value) = 0;
			virtual void set(const char* value) = 0;
			virtual void set(char* value) = 0;
		protected:
			Field();
			virtual ~Field();
			bool _isVoid;
			bool _isValid;
		};	
	}
}

#endif
