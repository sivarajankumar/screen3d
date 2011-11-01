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
 * \file Screen/Fields/FieldSizedString.h
 * \brief FieldSizedString header file
 * \author
 *
 */

#ifndef SCREEN_FIELD_SIZED_STRING_H
#define SCREEN_FIELD_SIZED_STRING_H

#include <Screen/Fields/Field.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Fields/Export.h>

/**
 * Namespace for all screen classes
 */
namespace screen{

	/**
	 * Namespace for all Fields classes
	 */
	namespace fields{

		/**
		 * \brief Sized string implementation of the field class
		 *
		 * String Field with size boundaries.
		 *
		 * \tparam MinSize minimum size of the string
		 * \tparam MaxSiwe maximum siwe of the string
		 */
		template <unsigned int MinSize, unsigned int MaxSize>
		class FieldSizedString : public Field{

			SCREEN_DECL_CLASS(Screen::Fields::FieldSizedString)

		public:

			/**
			 * \brief Contructor
			 */
			FieldSizedString();

			/**
			 * \brief Destructor
			 */
			virtual ~FieldSizedString();
			
			/**
			 * \brief Get the value of the field as a string
			 *
			 * \return value of the field converted in a string
			 */
			virtual std::string getAsString() const;

			/**
			 * \brief Get the value of the field
			 * \return value of the field in char*
			 */
			virtual const char* get() const;

			/**
			 * \brief string setter
			 * \param[in] iValue value to set
			 * \sa set(const char* iValue) and set(char* iValue)
			 * \todo present behavior in case of too long or too short strings
			 * use exception command to describe thrown exception
			 */
			virtual void set(const std::string& iValue);

			/**
			 * \brief const char* setter
			 * \param[in] value iValue to set
			 * \sa set(std::sring iValue) and set(char* iValue)
			 */
			virtual void set(const char* iValue);

			/**
			 * \brief char* setter
			 * \param[in] iValue value to set
			 * \sa set(std::sring iValue) and set(const char* iValue)
			 */
			virtual void set(char* iValue);
			
			enum{
				MIN_SIZE = MinSize,	///< Minimum size of the string
				MAX_SIZE = MaxSize	///< Maximum size of the string
			};
		protected:

			char _value[MAX_SIZE]; ///< Internal value

		};
	}
}

#endif
