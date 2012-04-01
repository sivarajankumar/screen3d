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
 * \file Scene.h
 * \brief The Scene. The Scene is the repensation of one displayable world
 * \author pjdemaret
 *
 * The scene contains all renderable objects. A scene is rendered thanks to a Camera.
 */

#ifndef SCREEN_SCENE_H
#define SCREEN_SCENE_H

#include <screen/utils/Declaration.h>
#include <screen/main/Export.h>

#include <map>
#include <iostream>

/**
 * Namespace all screen classes
 */
namespace screen {
	/**
	 * Namespace for the core classes of the engine
	 */
    namespace core {

		namespace objects {
			class Camera;
		}

		/**
		 * \brief The scene is the displayable world. Contains all displayable objects.
		 * The scene is rendered thanks to a camera.
		 * The scene object is also used to create camera objects
		 *
		 * \bug Temporary limitation: we can only have one scene
		 */
        class SCREEN_MAIN_EXPORT Scene {
        	SCREEN_DECL_CLASS(screen::core::Scene)

        public:

			/**
			 * \brief Constructor
			 *
			 * A default camera is also created with the scene (name is DefaultCamera<SceneName>)
			 *\param[in] iSceneName name of the scene
			 */
			Scene(const std::string& iSceneName);

			/**
			 * \brief Destructor
			 */
			virtual ~Scene();

			/**
			 * \brief Get the name of the scene
			 * \return Name of the scene
			 */
			virtual const std::string& getName() const;

			/**
			 * \brief Get the current active camera.
			 * The active camera is the camera rendering the scene if this scene is currently being rendered
			 * \return reference on the active camera
			 */
			screen::core::objects::Camera& getActiveCamera() const;

			/**
			 * \brief Set a camera as the active one
			 * \param[in] iCameraName name of the camera to set active (must be already attached to the scene)
			 * \exception screen::utils::Exception camera not attached to this scene
			 */
			void setActiveCamera(const std::string& iCameraName);

			/**
			 * \brief Set a camera as the active one
			 * \param[in] iCamera pointer on the camera to set active (must be already attached to the scene)
			 * \exception screen::utils::Exception camera not attached to this scene
			 */
			void setActiveCamera(const screen::core::objects::Camera& iCamera);

			/**
			 * \brief Create a camera and attach it to the scene
			 *
			 * \param[in] iCameraName name of the  new camera
			 * \exception screen::utils::Exception camera already exists
			 */
			screen::core::objects::Camera& createCamera(const std::string& iCameraName);

			/**
			 * \brief Drop a camera attached to the scene
			 * \param[in] iCameraName name of the  new camera
			 * \exception screen::utils::Exception camera doesn't exists
			 */
			void dropCamera(const std::string& iCameraName);

		protected:

			std::string _name;	///< Name of the scene
			std::map<std::string, screen::core::objects::Camera*> _cameraMap;	///< map of cameras attached to the scene
			screen::core::objects::Camera* _activeCamera;	///< active camera

		private:

			/**
			 * Default constructor
			 */
			Scene();

        };
    }
}

#endif
