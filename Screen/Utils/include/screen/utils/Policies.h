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
 * \file screen/utils/Policies.h
 * \brief Screen/Utils policy header file
 * \author
 *
 */

#ifndef SCREEN_POLICIES_H
#define SCREEN_POLICIES_H

#include <screen/utils/Export.h>
#include <screen/utils/SingletonLazyInstance.h>
//#include <boost/interprocess/shared_memory_object.hpp>
//#include <boost/interprocess/mapped_region.hpp>
#include <exception>
#include <cstring>

/**
 * Namespace for all screen classes
 */
namespace screen {
	/**
	 * Namespace for all utility classes
	 */
	namespace utils {

		/**
		 * \brief policy for the creation and the destruction that use new and delete
		 *
		 * \tparam T Instance type
		 */
        template <class T>
        class CreationWithNew {
        public:
			/**
			 * \brief Create a new instance and returns its pointer
			 *
			 * \return Returns an instance pointer
			 */
			static T* Create(){
				return new T();
			}

			/**
			 * \brief Destroy an instance
			 *
			 * \param[in] iInst instance to destroy
			 */
			static void Delete(T* iInst){
				delete iInst;
			}
        };

		/**
		 * \brief policy for the creation and the destruction that use a static instance
		 *
		 * Be careful. The instance can't manually be destroy.
		 * If the same policy is reused, the state of the instance is the same.
		 *
		 * \tparam T Instance type
		 */
        template <class T>
        class CreationWithStatic {
        public:
			/**
			 * \brief Returns the static instance pointer
			 *
			 * \return Returns an instance pointer
			 */
			static T* Create(){
				return &T::_policy_instance;
			}

			/**
			 * \brief To nothing
			 *
			 * This method is here to be compatible with all creation policies
			 * In pratice, the method does nothing
			 *
			 * \param[in] iInst instance to destroy
			 */
			static void Delete(T* iInst){}
		};

		/**
		 * \brief policy for the creation and the destruction that use a static instance
		 *
		 * Be careful. The instance can't manually be destroy.
		 * If the same policy is reused, the state of the instance is the same.
		 *
		 * \tparam T Instance type
		 */
        template <class T>
        class CreationWithLazy {
        public:
			/**
			 * \brief Returns the lazy instance pointer
			 *
			 * \return Returns an instance pointer
			 */
			static T* Create(){
				SingletonLazyInstance<T>* instance = new screen::utils::SingletonLazyInstance<T>();
				return &instance->get();
			}

			/**
			 * \brief To nothing
			 *
			 * This method is here to be compatible with all creation policies
			 * In pratice, the method does nothing
			 *
			 * \param[in] iInst instance to destroy
			 */
			static void Delete(T* iInst){}
		};
        
//        /*!  \class CreationWithStatic
//	      *  \brief policy for the creation and the destruction that use a static instance
//	      *  \author Ratouit Thomas
//	      *  \version 1.0
//	      *  \date 2008
//	      *  \warning The instance can't be destroy. If the same policy is reused, the state of the instance is the same.
//	      */
//        template <class T>
//        class CreationWithSharedMemory {
//        private:
//        	struct Block{
//        		int refCount;
//        		T instance;
//        	};
//        	
//        public:
//        	
//        	struct SharedMemoryHandler{
//        		
//        		SharedMemoryHandler(){
//        			using namespace boost::interprocess;
//        			static T instanceToCopy;
//        			try{
//	                	//try to open a shared memory object
//	            		shmObj = new shared_memory_object(
//	                		open_only,              	 //open
//	                		T::getSharedObjectName(),    //name
//	                		read_write                   //read-write mode
//	                	   	);
//	                	shmObj->truncate(sizeof(Block));
//	                	
//	                	//map the region of shared memory
//	                	mapped_region region(*shmObj, read_write);
//	                	
//	                	//add a reference count
//	                	block = static_cast<Block*>(region.get_address());
//	                	(block->refCount)++;
//	                	
//        			}catch(const interprocess_exception& e){
//	                	
//        				//failure -> creation of the shared memory object
//	                	shmObj = new shared_memory_object(
//	                		create_only,               	//open or create
//	                		T::getSharedObjectName(),   //name
//	                		read_write                  //read-write mode
//	                	   	);
//	                	shmObj->truncate(sizeof(Block));
//	                	
//	                	//map the region of shared memory
//	                	mapped_region region(*shmObj, read_write);
//	                	
//	                	//creation an instance of T in shared memory by copy
//	                	block = static_cast<Block*>(region.get_address());
//	                	std::memcpy(&(block->instance),&instanceToCopy,sizeof(T));
//	                }
//        		}
//        		
//        		~SharedMemoryHandler(){
//        			
//        		}
//        		
//        		boost::interprocess::shared_memory_object* shmObj;
//        		Block* block;
//        	};
//        	
//        	static SharedMemoryHandler smh;
//        	
//            static T* Create() {
//            	return &(smh.block->instance);
//            }
//
//            static void Delete(T* inst) {}
//        };
//        
//        template <class T>
//        typename CreationWithSharedMemory<T>::SharedMemoryHandler CreationWithSharedMemory<T>::smh;
        
		/**
		 * \brief policy interface for the instance lifetime
		 */
		struct LifeTimePolicyMother {
            /**
             * \brief Default constructor
             */
            LifeTimePolicyMother() {}

            /**
             * \brief Destructor
             */
            virtual ~LifeTimePolicyMother() {}

            /**
             * \brief Register the fact that an instanciation has been performed
             */
            virtual inline void instanciated() = 0;

            /**
             * \brief Register the instance usage
             */
            virtual inline void instanceUsed() = 0;

            /**
             * \brief Indicate if the deletion of the instance is allowed
             *
             * \return Is deletion allowed
             */
            virtual inline bool isAuthorisedDeletion() = 0;

            /**
             * \brief Register the fact that an instance has been deleted
             */
            virtual inline void deleted() = 0;
        };

		/**
		 * \brief policy for undestroyable instance
		 */
		struct NoDestructionLifeTime : public LifeTimePolicyMother {
            /**
             * \brief Default constructor
             */
            NoDestructionLifeTime()
                    :LifeTimePolicyMother() {}

            /**
             * \brief Destructor
             */
            ~NoDestructionLifeTime() {}

            /**
             * \brief To nothing
             */
            inline void instanciated() {}

            /**
             * \brief To nothing
             */
            inline void instanceUsed() {}

            /**
             * \brief Always refuse instance deletion
             */
            inline bool isAuthorisedDeletion() {
                return false;
            }

            /**
             * \brief To nothing
             */
            inline void deleted() {}
        };

		/**
		 * \brief policy for destroyable instance
		 */
		struct DestroyableInstanceLifeTime : public LifeTimePolicyMother {
            /**
             * \brief Default constructor
             */
            DestroyableInstanceLifeTime()
					:LifeTimePolicyMother(),_instanced(true) {}

            /**
             * \brief Destructor
             */
            ~DestroyableInstanceLifeTime() {}

            /**
             * \brief Register the fact that an instanciation has been performed
             */
			inline void instanciated() {
				_instanced=true;
            }

            /**
             * \brief Register the instance usage
             *
             * Do nothing in this case
             */
			inline void instanceUsed() {}

            /**
             * \brief Indicate if the deletion of the instance is allowed
             *
             * \return Is deletion allowed
             */
			inline bool isAuthorisedDeletion() {
				return _instanced;
            }

            /**
             * \brief Register the fact that an instance has been deleted
             */
			inline void deleted() {
				_instanced=false;
            }
        private:
            bool _instanced; ///< Internal flag
        };

		/**
		 * \brief policy for destroyable instance based on reference count
		 */
		struct ReferenceCountLifeTime : public LifeTimePolicyMother {
            /**
             * \brief Default constructor
             */
            ReferenceCountLifeTime()
					:LifeTimePolicyMother(),_refcount(-1) {}

            /**
             * \brief Destructor
             */
            ~ReferenceCountLifeTime() {}

            /**
             * \brief Register the fact that an instanciation has been performed
             *
             * Set the counter to 0
             */
            inline void instanciated() {
				_refcount=0;
            }

            /**
             * \brief Register the instance usage
             *
             * Bump the counter
             */
			inline void instanceUsed() {
				++_refcount;
            }

            /**
             * \brief Indicate if the deletion of the instance is allowed
             *
             * the deletion is allowed if count is -1
             *
             * \return Is deletion allowed
             */
			inline bool isAuthorisedDeletion() {
				return (_refcount<0);
            }

            /**
             * \brief Register the fact that an instance has been deleted
             *
             * Decrease the counter
             */
			inline void deleted() {
				--_refcount;
            }
        private:
            int _refcount; ///< Internal counter
        };

		/**
		 * \brief policy for destroyable instance based on reference count
		 *
		 * Throws exception if too many destructions
		 */
		struct SafeReferenceCountLifeTime : public LifeTimePolicyMother {
            /**
             * \brief Default constructor
             */
            SafeReferenceCountLifeTime()
					:LifeTimePolicyMother(),_refcount(-1) {}

            /**
             * \brief Destructor
             */
            ~SafeReferenceCountLifeTime() {}

            /**
             * \brief Register the fact that an instanciation has been performed
             *
             * Set the counter to 0
             */
			inline void instanciated() {
				if (_refcount>=0)
                    throw std::exception(); /*too many instanciations*/
                else
					_refcount=0;
            }

            /**
             * \brief Register the instance usage
             *
             * Bump the counter
             */
			inline void instanceUsed() {
				++_refcount;
            }

            /**
             * \brief Indicate if the deletion of the instance is allowed
             *
             * the deletion is allowed if count is -1
             *
             * \return Is deletion allowed
             */
			inline bool isAuthorisedDeletion() {
                return (_refcount<0);
            }

            /**
             * \brief Register the fact that an instance has been deleted
             *
             * Decrease the counter
             */
            inline void deleted() {
				if (_refcount>=0)
					--_refcount;
                else
                    throw std::exception();  /*too many deletions*/
            }
        private:
            int _refcount; ///< Internal counter
        };
    }
}

#endif
