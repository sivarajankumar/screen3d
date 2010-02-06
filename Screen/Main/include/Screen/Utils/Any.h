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

#ifndef SCREEN_ANY_H
#define SCREEN_ANY_H

#include <Screen/Utils/Exception.h>
#include <Screen/Utils/Declaration.h>

namespace Screen {
	namespace Utils {
		/*!  \class Any
		 *   \brief 
		 *   \author Ratouit Thomas
		 *   \date 17 oct. 09
		 */

		class Any {
			SCREEN_DECL_CLASS(Screen::Utils::Any)
	        template<class T>
	        friend T * any_cast(Any *);
		public:
			Any()
				:holder(NULL){
				SCREEN_DECL_CONSTRUCTOR(Any)
			}
			
			template<class T>
			Any(const T& value)
			          :holder(new Holder<T>(value)){
				SCREEN_DECL_CONSTRUCTOR(Any)
			}
			
	        Any(const Any & any)
	          :holder(any.holder != NULL ? any.holder->clone() : NULL){
	        	SCREEN_DECL_CONSTRUCTOR(Any)
	        }
			
			~Any(){
				SCREEN_DECL_DESTRUCTOR(~Any)
				delete holder;
			}
			
			Any& swap(Any & any){
				SCREEN_DECL_METHOD(swap)
	            std::swap(holder, any.holder);
	            return *this;
	        }
	        
			template<class T>
	        Any& operator=(const T& rhs){
				SCREEN_DECL_METHOD(operator=)
	            Any(rhs).swap(*this);
	            return *this;
	        }

	        Any & operator=(const Any & rhs){
	        	SCREEN_DECL_METHOD(operator=)
	        	Any(rhs).swap(*this);
	            return *this;
	        }
	        
	        bool isEmpty() const{
	        	SCREEN_DECL_METHOD(isEmpty)
	            return holder == NULL;
	        }

	        const std::type_info& getType() const{
	        	SCREEN_DECL_METHOD(getType)
	            if(holder == NULL){
	            	throw Screen::Utils::Exception("Any instance doesn't have a type (null instance of holder)");
	            }
	            return holder->getType();
	        }
	        
	        /* do not use. Use any_cast */
//	        template<class T>
//        	T operator()() const{
//	        	SCREEN_DECL_METHOD(operator())
//    			if (holder == NULL) {
//    				throw Screen::Utils::Exception("Empty Any Holder");
//    			}
//
//				Holder<ValueType>* h = static_cast<Holder<ValueType>* >(holder);
//				if(h == NULL){
//					throw Screen::Utils::Exception("Bad cast for Any Holder");
//				}
//				
//				return h->value;
//    		}

		private:
	        struct HolderBase{    
	            virtual ~HolderBase(){}
	            virtual HolderBase * clone() const = 0;
	            virtual const std::type_info& getType() const = 0;
	        };
	        
	        template<class T>
	        struct Holder : public HolderBase{
	        	SCREEN_DECL_CLASS(Screen::Utils::Any::Holder)
	            Holder(const T& value)
	            	:value(value){
	            	SCREEN_DECL_CONSTRUCTOR(Holder)
	            }
	            
	            ~Holder(){
	            	SCREEN_DECL_DESTRUCTOR(~Holder)
	            }

	            HolderBase* clone() const{
	            	SCREEN_DECL_METHOD(clone)
	                return new Holder(value);
	            }
	            
	            virtual const std::type_info & getType() const{
	            	SCREEN_DECL_METHOD(getType)
                    return typeid(T);
                }

	            T value;
	        };
			
			HolderBase* holder;
		};
		
	    template<class T>
	    T* any_cast(Any * any){
	    	SCREEN_DECL_FUNCTION(any_cast)
	    	if(any != NULL){
	    		if(!any->isEmpty()){
		    		if(any->getType() == typeid(T)){
		    			return &(static_cast<Any::Holder<T>* >(any->holder)->value);
		    		}
	    		}
	    	}
	    	return NULL;
	    }
	    
	    template<class T>
	    const T* any_cast(const Any * any){
	    	SCREEN_DECL_FUNCTION(any_cast)
	    	return any_cast<T>(const_cast<Any *>(any));
	    }

	    template<class T>
	    T any_cast(const Any & any){
	    	SCREEN_DECL_FUNCTION(any_cast)
	        const T* result = any_cast<T>(&any);
	        if(result == NULL){
				std::stringstream buf;
				buf << "Bad any_cast from type " << any.getType().name()
					<< " to " << typeid(T).name();
				throw Screen::Utils::Exception(buf.str());
			}
	        return *result;
	    }
	}
}

#endif
