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
 * \file Screen/Image/IL/ImageLoader.h
 * \brief Image loader source file
 * \author
 *
 */

#include <screen/image/il/ImageLoader.h>
#include <screen/core/Enums.h>
#include <screen/math/Vector2i.h>
#include <screen/utils/Exception.h>
#include <IL/il.h>

namespace screen {
	namespace image {
		namespace il{

			using screen::core::objects::Image;

			ImageLoader::ImageLoader(){
				SCREEN_DECL_CONSTRUCTOR(ImageLoader)
				ilInit();
				ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
				ilEnable(IL_ORIGIN_SET);
				//ilEnable(IL_FILE_OVERWRITE);
				ilSetInteger(IL_FORMAT_MODE, IL_BGRA);
				ilEnable(IL_FORMAT_SET);
			}

			ImageLoader::~ImageLoader(){
				SCREEN_DECL_DESTRUCTOR(~ImageLoader)
				ilShutDown();
			}

			Image* ImageLoader::loadFromFile(const std::string& iFilename) const{
				SCREEN_DECL_METHOD(loadFromFile);

				ILuint aTexture;
				ilGenImages(1, &aTexture);
				ilBindImage(aTexture);

				if (!ilLoadImage(const_cast<ILstring>(iFilename.c_str())))
					throw screen::utils::LoadingException(iFilename, "Erreur DevIL : ilLoadImage call failed. Can't load image");

				screen::math::Vector2i aSize(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
				const unsigned char* aPixels = ilGetData();
				Image* aImage = new Image(aSize, screen::core::PXF_A8R8G8B8, aPixels);

				ilBindImage(0);
				ilDeleteImages(1, &aTexture);

				return aImage;
			}
		}
	}
}
