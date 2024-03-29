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
 * \file Screen/Fields/Field.h
 * \brief Field header file
 * \author
 *
 */
#ifndef SCREEN_FIELD_H
#define SCREEN_FIELD_H

#include <Screen/Utils/Declaration.h>
#include <Screen/Fields/Export.h>
#include <string>

/**
 * Namespace for all screen classes
 */
namespace screen{
	/**
	 * Namespace for all Fields classes
	 */
	namespace fields{

		/**
		 * \brief Base class for all Fields classes
		 */
		class SCREEN_FIELDS_EXPORT Field{

		SCREEN_DECL_CLASS(Screen::Fields::Field)

		public:

			/**
			 * \brief Test if the field is void
			 * \return true if field is void
			 */
			virtual bool isVoid() const;

			/**
			 * \brief Test if the field is valid
			 * \return true if the field is valid
			 */
			virtual bool isValid() const;
			
			/**
			 * \brief Get the value of the field as a string
			 * \return value of the field converted in a string
			 */
			virtual std::string getAsString() const = 0;
			
			/**
			 * \brief string setter
			 * \param[in] iValue value to set
			 * \sa set(const char* iValue) and set(char* iValue)
			 */
			virtual void set(const std::string& iValue) = 0;

			/**
			 * \brief const char* setter
			 * \param[in] iValue value to set
			 * \sa set(std::sring iValue) and set(char* iValue)
			 */
			virtual void set(const char* iValue) = 0;

			/**
			 * \brief char* setter
			 * \param[in] iValue value to set
			 * \sa set(std::sring iValue) and set(const char* iValue)
			 */
			virtual void set(char* iValue) = 0;

		protected:

			/**
			 * \brief Constructor
			 *
			 * This class should never be instanciated directly
			 */
			Field();

			/**
			 * \brief Destructor
			 */
			virtual ~Field();

			bool _isVoid;	///< is field empty
			bool _isValid;	///< is field valid

		};
	}
}

#endif
