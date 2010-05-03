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

#ifndef SCREEN_FIELD_BOOL_H
#define SCREEN_FIELD_BOOL_H

#include <Screen/Fields/Field.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Fields/Export.h>

namespace Screen{
	namespace Fields{
		class SCREEN_FIELDS_EXPORT FieldBool : public Field{
			SCREEN_DECL_CLASS(Screen::Fields::FieldBool)
		public:
			FieldBool();
			virtual ~FieldBool();
			
			virtual std::string getAsString() const;
			virtual bool get() const;

			virtual void set(const std::string& value);
			virtual void set(const char* value);
			virtual void set(char* value);
			virtual void set(bool value);
		protected:
			bool _value;
		};	
	}
}

#endif
