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

#ifndef SCREEN_POLICIES_H
#define SCREEN_POLICIES_H

#include <Screen/Utils/Export.h>
//#include <boost/interprocess/shared_memory_object.hpp>
//#include <boost/interprocess/mapped_region.hpp>
#include <exception>
#include <cstring>

/* Creation Policies*/

namespace Screen {
    namespace Utils {

        /*!  \class CreationWithNew
          *  \brief policy for the creation and the destruction that use new and delete
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        template <class T>
        class SCREEN_EXPORT CreationWithNew {
        public:
            static T* Create();
            static void Delete(T* inst);
        };

        /*!  \class CreationWithStatic
          *  \brief policy for the creation and the destruction that use a static instance
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *  \warning The instance can't be destroy. If the same policy is reused, the state of the instance is the same.
          */
        template <class T>
        class SCREEN_EXPORT CreationWithStatic {
        public:
            static T* Create();
            static void Delete(T* inst);
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

        /*!  \class LifeTimePolicyMother
          *  \brief interface of all life-time policies
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct LifeTimePolicyMother {
            LifeTimePolicyMother() {}
            virtual ~LifeTimePolicyMother() {}
            virtual inline void Instanciated() = 0;
            virtual inline void InstanceUsed() = 0;
            virtual inline bool IsAuthorisedDeletion() = 0;
            virtual inline void Deleted() = 0;
        };

        /*!  \class NoDestructionLifeTime
          *  \brief life-time policy for objet that can't be destructed
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct NoDestructionLifeTime : public LifeTimePolicyMother {
            NoDestructionLifeTime()
                    :LifeTimePolicyMother() {}
            ~NoDestructionLifeTime() {}
            inline void Instanciated() {}
            inline void InstanceUsed() {}
            inline bool IsAuthorisedDeletion() {
                return false;
            }
            inline void Deleted() {}
        }
        ;

        /*!  \class DestroyableInstanceLifeTime
          *  \brief life-time policy for objet that are destructed each time the Deleted method is invoked
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct DestroyableInstanceLifeTime : public LifeTimePolicyMother {
            DestroyableInstanceLifeTime()
                    :LifeTimePolicyMother(),instanced(true) {}
            ~DestroyableInstanceLifeTime() {}
            inline void Instanciated() {
                instanced=true;
            }
            inline void InstanceUsed() {}
            inline bool IsAuthorisedDeletion() {
                return instanced;
            }
            inline void Deleted() {
                instanced=false;
            }
private:
            bool instanced;
        };

        /*!  \class ReferenceCountLifeTime
          *  \brief life-time policy for reference count
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          */
        struct ReferenceCountLifeTime : public LifeTimePolicyMother {
            ReferenceCountLifeTime()
                    :LifeTimePolicyMother(),refcount(-1) {}
            ~ReferenceCountLifeTime() {}
            inline void Instanciated() {
                refcount=0;
            }
            inline void InstanceUsed() {
                ++refcount;
            }
            inline bool IsAuthorisedDeletion() {
                return (refcount<0);
            }
            inline void Deleted() {
                --refcount;
            }
private:
            int refcount;
        };

        /*!  \class SafeReferenceCountLifeTime
          *  \brief life-time policy for reference count with exceptions
          *  \author Ratouit Thomas
          *  \version 1.0
          *  \date 2008
          *
          *  Exception is thrown when too many calls of Delete methodes
          */
        struct SafeReferenceCountLifeTime : public LifeTimePolicyMother {
            SafeReferenceCountLifeTime()
                    :LifeTimePolicyMother(),refcount(-1) {}
            ~SafeReferenceCountLifeTime() {}
            inline void Instanciated() {
                if (refcount>=0)
                    throw std::exception(); /*too many instanciations*/
                else
                    refcount=0;
            }
            inline void InstanceUsed() {
                ++refcount;
            }
            inline bool IsAuthorisedDeletion() {
                return (refcount==0);
            }
            inline void Deleted() {
                if (refcount>=0)
                    --refcount;
                else
                    throw std::exception();  /*too many deletions*/
            }
private:
            int refcount;
        };
    }
}

#endif
