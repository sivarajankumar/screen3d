/*****************************************************************************
 * This source file is part of SCREEN (SCalable REndering ENgine)            *
 *                                                                           *
 * Copyright (c) 2008-2012 Ratouit Thomas                                    *
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
 * \file screen/utils/Any.h
 * \brief Screen/Utils generic instance handler implementation header file
 * \author
 *
 */

#ifndef SCREEN_ANY_H
#define SCREEN_ANY_H

#include <screen/utils/Exception.h>
#include <screen/utils/Declaration.h>


/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {

		/**
		 * \brief Container used to store any type of classes
		 */
		class Any {

			SCREEN_DECL_CLASS(screen::utils::Any)

	        template<class T>
	        friend T * any_cast(Any *);

		public:

			/**
			 * \brief Constructor
			 *
			 * Holder is set to NULL
			 */
			Any()
				:_holder(NULL){
				SCREEN_DECL_CONSTRUCTOR(Any)
			}
			
			/**
			 * \brief Constructor
			 *
			 * \tparam T class to hold
			 * \param[in] iValue instance of the classe stored
			 */
			template<class T>
			Any(const T& iValue)
			 :_holder(new Holder<T>(iValue)){
				SCREEN_DECL_CONSTRUCTOR(Any)
			}
			
			/**
			 * \brief Copy-constructor
			 */
			Any(const Any & iAny)
			  :_holder(iAny._holder != NULL ? iAny._holder->clone() : NULL){
	        	SCREEN_DECL_CONSTRUCTOR(Any)
	        }
			
			/**
			 * \brief Destructor
			 *
			 * The destructor remove the instance stored
			 */
			~Any(){
				SCREEN_DECL_DESTRUCTOR(~Any)
				delete _holder;
			}
			
			/**
			 * \brief Swape the content of two Any
			 * \param[in,out] ioAny object to swap with
			 * \return Returns current object
			 */
			Any& swap(Any & ioAny){
				SCREEN_DECL_METHOD(swap)
				std::swap(_holder, ioAny._holder);
	            return *this;
	        }
	        
			/**
			 * \brief Assignation operator
			 * \tparam T Class assigned
			 * \param[in] iRhs object to assign
			 * \return Returns current object
			 */
			template<class T>
			Any& operator=(const T& iRhs){
				SCREEN_DECL_METHOD(operator=)
				Any(iRhs).swap(*this);
	            return *this;
	        }

			/**
			 * \brief Assignation operator
			 * \param[in] iRhs object to assign
			 * \return Returns current object
			 */
			Any & operator=(const Any & iRhs){
	        	SCREEN_DECL_METHOD(operator=)
				Any(iRhs).swap(*this);
	            return *this;
	        }
	        
			/**
			 * \brief Test if Any container is empty
			 * \return True if is empty
			 */
	        bool isEmpty() const{
	        	SCREEN_DECL_METHOD(isEmpty)
				return _holder == NULL;
	        }

			/**
			 * \brief Get the type of the object stored in the container
			 * \return Type of the stored object
			 * \exception screen::utils::Exception No object stored
			 */
	        const std::type_info& getType() const{
	        	SCREEN_DECL_METHOD(getType)
				if(_holder == NULL){
	            	throw screen::utils::Exception("Any instance doesn't have a type (null instance of holder)");
	            }
				return _holder->getType();
	        }
	        
	        /* do not use. Use any_cast */
//	        template<class T>
//        	T operator()() const{
//	        	SCREEN_DECL_METHOD(operator())
//    			if (holder == NULL) {
//    				throw screen::utils::Exception("Empty Any Holder");
//    			}
//
//				Holder<ValueType>* h = static_cast<Holder<ValueType>* >(holder);
//				if(h == NULL){
//					throw screen::utils::Exception("Bad cast for Any Holder");
//				}
//				
//				return h->value;
//    		}

		private:

			/**
			 * \brief Base struct for object held in Any
			 */
	        struct HolderBase{    
	            virtual ~HolderBase(){}
	            virtual HolderBase * clone() const = 0;
	            virtual const std::type_info& getType() const = 0;
	        };
	        
			/**
			 * \brief Struct for object held in Any
			 * \tparam T class held
			 */
	        template<class T>
	        struct Holder : public HolderBase{

	        	SCREEN_DECL_CLASS(screen::utils::Any::Holder)

				/**
				 * \brief Constructor
				 * \param[in] iValue instance of the classe stored
				 */
				Holder(const T& iValue)
					:_value(iValue){
	            	SCREEN_DECL_CONSTRUCTOR(Holder)
	            }
	            
				/**
				 * \brief Destructor
				 */
	            ~Holder(){
	            	SCREEN_DECL_DESTRUCTOR(~Holder)
	            }

				/**
				 * \brief Clone the object
				 * \return Returns a copy of the object
				 */
	            HolderBase* clone() const{
	            	SCREEN_DECL_METHOD(clone)
					return new Holder(_value);
	            }
	            
				/**
				 * \brief Get the type of the internal object
				 * \return Type of the internal object
				 */
	            virtual const std::type_info & getType() const{
	            	SCREEN_DECL_METHOD(getType)
                    return typeid(T);
                }

				T _value;				///< Stored object
	        };
			
			HolderBase* _holder;	///< Holder for the stored class
		};
		
		/**
		 * \brief Cast a Any pointer into T class pointer
		 * \tparam T Class to be casted to
		 * \param[in] iAny pointer to cast
		 * \return Pointer of the object casted to the correct class or NULL if cast is not posssible
		 */
	    template<class T>
		T* any_cast(Any * iAny){
	    	SCREEN_DECL_FUNCTION(any_cast)
			if(iAny != NULL){
				if(!iAny->isEmpty()){
					if(iAny->getType() == typeid(T)){
						return &(static_cast<Any::Holder<T>* >(iAny->_holder)->_value);
		    		}
	    		}
	    	}
	    	return NULL;
	    }
	    
		/**
		 * \brief Cast a const Any pointer into const T class pointer
		 * \tparam T Class to be casted to
		 * \param[in] iAny pointer to cast
		 * \return Pointer of the object casted to the correct class or NULL if cast is not posssible
		 */
	    template<class T>
		const T* any_cast(const Any * iAny){
	    	SCREEN_DECL_FUNCTION(any_cast)
			return any_cast<T>(const_cast<Any *>(iAny));
	    }

		/**
		 * \brief Cast a const Any instance into const T class instance
		 * \tparam T Class to be casted to
		 * \param[in] iAny instance to cast
		 * \return Instance of the object casted to the correct class
		 * \exception screen::utils::Exception Cast not possible
		 */
	    template<class T>
		T any_cast(const Any & iAny){
	    	SCREEN_DECL_FUNCTION(any_cast)
			const T* aResult = any_cast<T>(&iAny);
			if(aResult == NULL){
				std::stringstream aBuf;
				aBuf << "Bad any_cast from type " << iAny.getType().name()
					<< " to " << typeid(T).name();
				throw screen::utils::Exception(aBuf.str());
			}
			return *aResult;
	    }
	}
}

#endif
