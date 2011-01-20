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

#ifndef SCREEN_SMART_POLICIES_H
#define SCREEN_SMART_POLICIES_H

#include <screen/utils/Declaration.h>

namespace screen {
	namespace utils {
	    template <class T>
	    class RefCountSmartPolicy{
	    	SCREEN_DECL_CLASS(screen::utils::RefCountSmartPolicy)
	    public :
	    	RefCountSmartPolicy()
	    		:counter(new int(1)){
	    		SCREEN_DECL_CONSTRUCTOR(RefCountSmartPolicy)
	    	}
	
	        T* clone(T* ptr){
	        	SCREEN_DECL_METHOD(clone)
	            ++(*counter);
	            return ptr;
	        }
	
	        void release(T* ptr){
	        	SCREEN_DECL_METHOD(release)
	        	--(*counter);
	            if ( (*counter) == 0){
	                delete counter;
	                delete ptr;
	            }
	        }
	
	        void swap(RefCountSmartPolicy& rcsp){
	        	SCREEN_DECL_METHOD(swap)
	            std::swap(rcsp.counter, counter);
	        }
	    private :    	
	        int* counter;
	    };
	
	    ////////////////////////////////////////////////////////////
	    /// Police de pointeur intelligent :
	    /// objets COM et ressources du moteur - comptage de référence intrusif
	    ////////////////////////////////////////////////////////////
	    template <class T>
	    class ResourceSmartPolicy{
	    	SCREEN_DECL_CLASS(ResourceSmartPolicy)
	    public :
	    	T* clone(T* ptr){
	    		SCREEN_DECL_METHOD(clone)
	            if (ptr)
	                ptr->add();
	            return ptr;
	        }
	
	        void release(T* ptr){
	        	SCREEN_DECL_METHOD(release)
	            if (ptr)
	                ptr->remove();
	        }
	
	        void swap(ResourceSmartPolicy&){
	        	SCREEN_DECL_METHOD(swap)
	        }
	    };
	}
}

#endif
