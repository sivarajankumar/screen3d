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

#include <Screen/Core/Loaders/ImageLoader.h>
#include <Screen/Core/Enums.h>
#include <Screen/Math/Vector2i.h>
#include <Screen/Utils/Exception.h>
#include <IL/il.h>

namespace Screen {
	namespace Core {
		using Screen::Core::Objects::Image;
		
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

		Image* ImageLoader::loadFromFile(const std::string& filename) const{
			SCREEN_DECL_METHOD(loadFromFile)
		    ILuint texture;
		    ilGenImages(1, &texture);
		    ilBindImage(texture);

		    if (!ilLoadImage(const_cast<ILstring>(filename.c_str())))
		        throw Screen::Utils::LoadingException(filename, "Erreur DevIL : ilLoadImage call failed. Can't load image");

		    Screen::Math::Vector2i size(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
		    const unsigned char* pixels = ilGetData();
		    Image* image = new Image(size, Screen::Core::PXF_A8R8G8B8, pixels);

		    ilBindImage(0);
		    ilDeleteImages(1, &texture);

		    return image;
		}
	}
}
