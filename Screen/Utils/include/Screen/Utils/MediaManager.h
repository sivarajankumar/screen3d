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

#ifndef SCREEN_MEDIA_MANAGER_H
#define SCREEN_MEDIA_MANAGER_H

#include <Screen/Utils/ResourceManager.h>
#include <Screen/Utils/SmartPtr.h>
#include <Screen/Utils/SmartPolicies.h>
#include <Screen/Utils/Typelist.h>
#include <Screen/Utils/Loader.h>
#include <Screen/Utils/File.h>
#include <Screen/Utils/Path.h>
#include <Screen/Utils/Declaration.h>
#include <boost/tokenizer.hpp>
#include <string>
#include <set>

namespace Screen {
	namespace Utils {	
	    template <class T>
	    struct MediaHolder{
	        typedef std::map<std::string, SmartPtr<Loader<T> > > LoaderMap;
	        LoaderMap loaderMap;
	    };
	
	    template <class MediaList>
	    class MediaManager : public ScatteredHierarchy<MediaHolder, MediaList>{
	    	SCREEN_DECL_CLASS(Screen::Utils::MediaManager)
	    public :
	    	template <class T> void registerLoader(Loader<T>* loader, const std::string& extensions){
	    		SCREEN_DECL_METHOD(registerLoader)
	    		
	    		SCREEN_LOG_DEBUG("Register " << loader->_selfType() << " As " << loader->_loadedType() << " loader for the following extensions :")
	    		
		    	// extensions parsing
		    	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
		    	boost::char_separator<char> sep("|");
		    	Tokenizer tokens(extensions, sep);
		    	
		    	SCREEN_LOG_DEBUG("<list>")
		    	
		        // add extensions to media manager
		    	
		    	SmartPtr<Loader<T> > ptr = loader;
		    	for (Tokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i){
		    		SCREEN_LOG_DEBUG("\t" << *i)
		    		MediaHolder<T>::loaderMap[*i] = ptr;
		    	}
		    	
		    	SCREEN_LOG_DEBUG("</list>")
	    	}
	    	
	    	template <class T> void unregisterLoader(const std::string& extensions){
	    		SCREEN_DECL_METHOD(unregisterLoader)
	    		
	    		SCREEN_LOG_DEBUG("Unregister loaders with the following extensions :")
	    		
		    	// extensions parsing
		    	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
		    	boost::char_separator<char> sep("|");
		    	Tokenizer tokens(extensions, sep);
		    	
		    	SCREEN_LOG_DEBUG("<list>")

		        // delete extensions to media manager
		    	for (Tokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i){
		    		SCREEN_LOG_DEBUG("\t" << *i << " | " << (MediaHolder<T>::loaderMap[*i]==NULL ? "nothing" : MediaHolder<T>::loaderMap[*i]->_selfType()))
		    		MediaHolder<T>::loaderMap.erase(*i);  
		    	}
		    	
		    	SCREEN_LOG_DEBUG("</list>")
	    	}
	    	
	    	void addPath(const Path& path){
				paths.insert(path.getPath());
			}
	    	
	    protected :
	    	MediaManager(){}
	        virtual ~MediaManager(){}
	        
	        File MediaManager::findMedia(const File& filename) const{
	            // Parcours de la liste des chemins de recherche
	            for (std::set<Path>::const_iterator i = paths.begin(); i != paths.end(); ++i){
	                File ret(i->getPath() + filename.getFullname());
	                if (ret.exists())
	                    return ret;
	            }

	            // Si le fichier est introuvable, on lance une exception
	            throw Screen::Utils::LoadingException(filename.getFullname(), "File not found");
	        }
	        
	    	template <class T> T* loadMediaFromFile(const File& filename) const{
	    		SCREEN_DECL_METHOD(loadMediaFromFile)
	    		SCREEN_LOG_INFO("Load media : " << filename.getFullname())
	    		
	    		typename MediaHolder<T>::LoaderMap::const_iterator i =  MediaHolder<T>::loaderMap.find(filename.getExtension());

		        if (i != MediaHolder<T>::loaderMap.end())
		        	if(i->second != NULL){
		        		SmartPtr<Loader<T> > ptr = (i->second);
		        		SCREEN_LOG_DEBUG("Loader found :")
		        		SCREEN_LOG_DEBUG("\tLoader type : " << ptr->_selfType())
		        		File file = findMedia(filename);
		        		T* ret = ptr->loadFromFile(file.getFullname());
		        		SCREEN_LOG_INFO((ret!=NULL ? "Load successful" : "Load failed (NULL pointer)"))
		        		return ret;
		        	}
		        
		        throw Screen::Utils::LoadingException(filename.getFullname(), "No loader for this extension : "+filename.getExtension());
	    	}
	    	
	    	std::set<Path> paths;
	    };
	    
//	    template <class T>
//	    Screen::Utils::SmartPtr<T,ResourceSmartPolicy> MediaManager::load(const File& filename) const{
//	    	T* ptr = ResourceManager::instance()->get<T>(filename.getFullname());
//	    	if(ptr==NULL){
//	    		ptr = loadMediaFromFile<T>(filename);
//	    		ResourceManager::instance()->add(filename.getFullname(),ptr);
//	    	}
//	    	return ptr;
//	    }
	}
}

#endif
