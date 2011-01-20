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

#ifndef SCREEN_REFERENCE_RESTRICTION_H
#define SCREEN_REFERENCE_RESTRICTION_H

#include <screen/utils/Type.h>
#include <screen/utils/Typelist.h>

namespace screen {
    namespace utils {

        typedef Append<UnsignedIntList,
        Append<SignedIntList,
        Append<OtherIntList,
        FloatList
        >::List
        >::List
        >::List UnusedReferenceTypeList;

        /*!  \class ConstReference
          *  \brief Helper to choose between const reference and copy of an object
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template<class T>
        struct ConstReference {
            typedef typename ConditionalType<
            BelongsTo<UnusedReferenceTypeList,T>::Result,
            T,
            const T& >::Type Type;
        };

        /*!  \class Reference
          *  \brief Helper to choose between reference and copy of an object
          *  \author Ratouit Thomas
          *  \version 1.0
          *
          */
        template<class T>
        struct Reference {
            typedef typename ConditionalType<
            BelongsTo<UnusedReferenceTypeList,T>::Result,
            T,
            T& >::Type Type;
        };

        template<class T>
        struct ConstReference<T*> {
            typedef T* Type;
        };

        template<class T>
        struct Reference<T*> {
            typedef T* Type;
        };
    }
}

#endif
