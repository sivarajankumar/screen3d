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

#ifndef SCREEN_TYPE_H
#define SCREEN_TYPE_H

namespace screen {
    namespace utils {

        /*!  \class SameType
          *  \brief Equality of two types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <class T, class U>
        struct SameType {
            enum {
                Result = false
            };
        };

        template <class T>
        struct SameType<T,T> {
            enum {
                Result = true
            };
        };

        /*!  \class ConditionalType
          *  \brief Conditional selection between two types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <
        bool B,
        class T,
        class U
        >
        struct ConditionalType {
            typedef T Type;
        };

        template <
        class T,
        class U
        >
        struct ConditionalType<false,T,U> {
            typedef U Type;
        };

    }
}

#endif
