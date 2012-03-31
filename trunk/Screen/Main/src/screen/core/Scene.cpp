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

// core classes
#include <screen/core/Scene.h>

// object classes
#include <screen/core/objects/Camera.h>

// utils classes
#include <screen/utils/Exception.h>

//stl
#include <iostream>

namespace screen {
	namespace core {

		Scene::Scene(const std::string& iSceneName)
			: _name(iSceneName), _activeCamera(NULL){
			SCREEN_DECL_CONSTRUCTOR(Scene)

			// create default camera
			std::string aDefaultCameraName = "DefaultCamera"+iSceneName;
			_activeCamera = createCamera(aDefaultCameraName);
		}


		Scene::~Scene() {
			SCREEN_DECL_DESTRUCTOR(~Scene)

			// Clear cameras
			std::map<std::string, screen::core::objects::Camera*>::iterator it;
			_activeCamera = NULL;
			for (it = _cameraMap.begin(); it != _cameraMap.end(); ++it){
				delete ((*it).second);
				(*it).second = NULL;
			}
			_cameraMap.clear();
		}


		const std::string& Scene::getName() const{
			SCREEN_DECL_METHOD(getName)
			return _name;
		}

		inline
		screen::core::objects::Camera* Scene::getActiveCamera() const{
			SCREEN_DECL_METHOD(getActiveCamera)
			return _activeCamera;
		}

		void Scene::setActiveCamera(const std::string& iCameraName){
			SCREEN_DECL_METHOD(setActiveCamera)
			std::map<std::string, screen::core::objects::Camera*>::iterator it;
			it = _cameraMap.find(iCameraName);
			if (it == _cameraMap.end())
				throw screen::utils::Exception( __FILE__, __LINE__, "Trying to active a camera (" + iCameraName
											   + ") not attached to the scene (" + getName() + ")");
		}

		void Scene::setActiveCamera(const screen::core::objects::Camera& iCamera){
			SCREEN_DECL_METHOD(setActiveCamera)

			setActiveCamera(iCamera.getName());
		}

		screen::core::objects::Camera* Scene::createCamera(const std::string& iCameraName){
			SCREEN_DECL_METHOD(createCamera)
			std::map<std::string, screen::core::objects::Camera*>::iterator it;
			it = _cameraMap.find(iCameraName);
			if (it != _cameraMap.end()){
				throw screen::utils::Exception( __FILE__, __LINE__, "Trying to create a camera (" + iCameraName
											   + ") that already exists in the scene (" + getName() + ")");
			}

			screen::core::objects::Camera* aNewCamera = new screen::core::objects::Camera(iCameraName, this);
			_cameraMap[iCameraName] = aNewCamera;
			return aNewCamera;
		}

	}
}
