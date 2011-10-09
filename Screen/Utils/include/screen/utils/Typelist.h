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

#ifndef SCREEN_TYPELIST_H
#define SCREEN_TYPELIST_H

#define TYPE_LIST_0 screen::utils::NullType
#define TYPE_LIST_1(T1) \
 screen::utils::TypeList<T1, screen::utils::NullType>
#define TYPE_LIST_2(T1,T2) \
 screen::utils::TypeList<T1, TYPE_LIST_1(T2)>
#define TYPE_LIST_3(T1,T2,T3) \
 screen::utils::TypeList<T1, TYPE_LIST_2(T2,T3)>
#define TYPE_LIST_4(T1,T2,T3,T4) \
 screen::utils::TypeList<T1, TYPE_LIST_3(T2,T3,T4)>
#define TYPE_LIST_5(T1,T2,T3,T4,T5) \
 screen::utils::TypeList<T1, TYPE_LIST_4(T2,T3,T4,T5)>
#define TYPE_LIST_6(T1,T2,T3,T4,T5,T6) \
 screen::utils::TypeList<T1, TYPE_LIST_5(T2,T3,T4,T5,T6)>
#define TYPE_LIST_7(T1,T2,T3,T4,T5,T6,T7) \
 screen::utils::TypeList<T1, TYPE_LIST_6(T2,T3,T4,T5,T6,T7)>
#define TYPE_LIST_8(T1,T2,T3,T4,T5,T6,T7,T8) \
 screen::utils::TypeList<T1, TYPE_LIST_7(T2,T3,T4,T5,T6,T7,T8)>
#define TYPE_LIST_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) \
 screen::utils::TypeList<T1, TYPE_LIST_8(T2,T3,T4,T5,T6,T7,T8,T9)>
#define TYPE_LIST_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) \
 screen::utils::TypeList<T1, TYPE_LIST_9(T2,T3,T4,T5,T6,T7,T8,T9,T10)>
#define TYPE_LIST_11(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) \
 screen::utils::TypeList<T1, TYPE_LIST_10(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)>

namespace screen {
    namespace utils {

        /*!  \class NullType
          *  \brief An empty type
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  End of a type list element
          */
        class NullType {}
        ;


        /*!  \class TypeList
          *  \brief The base struct of a list of type
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  The structure is a pair (head and tail) of types \n
          *  Usely, the head is a type and the tail is a pair or a NullType structure
          */
        template <class T, class U>
        struct TypeList {
            typedef T Head;
            typedef U Tail;
        };

        /*!  \class IndexOf
          *  \brief Give the index of a type into a list of types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  value range : [-1, +infinity[ \n
          *  -1 is returned when the type doesn't belongs to the list
          */

        template <class TList, class T>
        struct IndexOf {}
        ;

        template <class T>
        struct IndexOf<NullType, T> {
            enum {
                Result = -1
            };
        };

        template <
        class T,
        class Tail
        >
        struct IndexOf<TypeList<T, Tail>, T> {
            enum {
                Result = 0
            };
        };

        template <
        class Head,
        class Tail,
        class T
        >
        struct IndexOf<TypeList<Head, Tail>, T> {
		private:
            enum {
                Temp = IndexOf<Tail, T>::Result
            };
		public:
            enum {
                Result = ( (Temp == -1) ? -1 : 1 + Temp)
            };
        };

        /*!  \class BelongsTo
          *  \brief boolean indicating if a type belongs to a list of types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */

        template <
        class TList,
        class T
        >
        struct BelongsTo {
            enum {
                Result = (IndexOf<TList,T>::Result != -1)
            };
        };

        /*!  \class Append
          *  \brief concatens two lists of types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <class TList, class T>
        struct Append {};

        template <>
        struct Append<NullType, NullType> {
            typedef NullType List;
        };

        template <class T>
        struct Append<NullType, T> {
            typedef TYPE_LIST_1(T) List;
        };

        template <class Head, class Tail>
        struct Append<NullType, TypeList<Head, Tail> > {
            typedef TypeList<Head, Tail> List;
        };

        template <class Head, class Tail, class T>
        struct Append<TypeList<Head, Tail>, T> {
            typedef TypeList<Head,
            typename Append<Tail, T>::List>
            List;
        };

        /*!  \class SimpleHierarchy
          *  \brief create a hierarchy from a list of types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <class TList>
        class SimpleHierarchy;

        template <class T1, class T2>
        class SimpleHierarchy<TypeList<T1,T2> >
        	:public T1, public SimpleHierarchy<T2> {}
        ;

        template <>
        class SimpleHierarchy<NullType> {}
        ;
        
        /*!  \class ScatteredHierarchy
          *  \brief create a hierarchy from a list of types
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template < template <class> class Holder, class TList>
        class ScatteredHierarchy;

        template < template <class> class Holder, class T1, class T2>
        class ScatteredHierarchy<Holder, TypeList<T1,T2> >
        	:public Holder<T1>, public ScatteredHierarchy<Holder, T2>
        {};

        template < template <class> class Holder>
        class ScatteredHierarchy<Holder, NullType> {};

        typedef TYPE_LIST_4(unsigned char, unsigned short int, unsigned int, unsigned long int) UnsignedIntList;
        typedef TYPE_LIST_4(signed char, short int, int, long int) SignedIntList;
        typedef TYPE_LIST_3(bool, char, wchar_t) OtherIntList;
        typedef TYPE_LIST_3(float, double, long double) FloatList;
    }
}

#endif
