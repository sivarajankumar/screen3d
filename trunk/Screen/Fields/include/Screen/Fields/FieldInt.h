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
 * \file Screen/Fields/FieldInt.h
 * \brief FieldInt header file
 * \author
 *
 */

#ifndef SCREEN_FIELD_INT_H
#define SCREEN_FIELD_INT_H

#include <Screen/Fields/Field.h>
#include <Screen/Utils/Declaration.h>
#include <Screen/Fields/Export.h>

/**
 * Namespace for all screen classes
 */
namespace Screen{

	/**
	 * Namespace for all Fields classes
	 */
	namespace Fields{

		/**
		 * \brief Integer implementation of the field class
		 */
		class SCREEN_FIELDS_EXPORT FieldInt : public Field{

			SCREEN_DECL_CLASS(Screen::Fields::FieldInt)

		public:

			/**
			 * \brief Constructor
			 */
			FieldInt();

			/**
			 * \brief Destructor
			 */
			virtual ~FieldInt();
			

			/**
			 * \brief Get the value of the field as a string
			 *
			 * \return value of the field converted in a string
			 */
			virtual std::string getAsString() const;

			/**
			 * \brief Get the value of the field
			 * \return value of the field in int
			 */
			virtual int get() const;

			/**
			 * \brief string setter
			 * \param[in] value: value to set
			 * \sa set(const char* value) and set(char* value)
			 */
			virtual void set(const std::string& value);

			/**
			 * \brief const char* setter
			 * \param[in] value: value to set
			 * \sa set(std::sring value) and set(char* value)
			 */
			virtual void set(const char* value);

			/**
			 * \brief char* setter
			 * \param[in] value: value to set
			 * \sa set(std::sring value) and set(const char* value)
			 */
			virtual void set(char* value);

			/**
			 * \brief int setter
			 * \param[in] value: value to set
			 */
			virtual void set(int value);
		protected:

			int _value; ///< Internal value

		}; // FieldInt class
	} // Field namespace
} // Screen namespace

#endif
