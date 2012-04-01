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
 * \file screen/utils/Declaration.h
 * \brief Screen/Utils declaration handling header file
 * \author
 *
 */

#ifndef SCREEN_DECLARATION_H
#define SCREEN_DECLARATION_H

#include <screen/utils/Logger.h>
#include <screen/utils/Profiler.h>
#include <screen/utils/Export.h>
#include <screen/utils/Exception.h>
#include <string>

//class

#if defined(USE_SCREEN_PROFILE) || defined(USE_SCREEN_LOG_CALL_TRACER)
#	define SCREEN_DECL_CLASS(c) \
		inline static const char* _getClassName(){ \
			static const char ret[] = #c; \
			return ret; \
		}
#else
#	define SCREEN_DECL_CLASS(c)
#endif

//method

#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_METHOD_LOG(m) \
		std::stringstream _internal_ss; \
		_internal_ss << this; \
		SCREEN_SCOPE_CALL(screen::utils::CALL_METHOD,_getClassName(),#m,_internal_ss.str());
#else
#	define SCREEN_DECL_METHOD_LOG(m)
#endif

#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_METHOD_PROFILE(m) \
		std::stringstream _internal_ss2; \
		_internal_ss2 << "method | " << _getClassName() << "::" << #m << "() | " << this; \
		SCREEN_SCOPE_PROFILE(_internal_ss2.str());
#else
#	define SCREEN_DECL_METHOD_PROFILE(m)
#endif


#define SCREEN_DECL_METHOD(m) \
	SCREEN_DECL_METHOD_LOG(m) \
	SCREEN_DECL_METHOD_PROFILE(m)

//static method

#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_STATIC_METHOD_LOG(m) \
		SCREEN_SCOPE_CALL(screen::utils::CALL_STATIC_METHOD,_getClassName(),#m,"");
#else
#	define SCREEN_DECL_STATIC_METHOD_LOG(m)
#endif

#ifdef USE_SCREEN_PROFILE
#	define SCREEN_DECL_STATIC_METHOD_PROFILE(m) \
		std::stringstream _internal_ss2; \
		_internal_ss2 << "static method | " << _getClassName() << "::" << #m << "()"; \
		SCREEN_SCOPE_PROFILE(_internal_ss2.str());
#else
#	define SCREEN_DECL_STATIC_METHOD_PROFILE(m)
#endif


#define SCREEN_DECL_STATIC_METHOD(m) \
	SCREEN_DECL_STATIC_METHOD_LOG(m) \
	SCREEN_DECL_STATIC_METHOD_PROFILE(m)

// constructor

#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_CONSTRUCTOR_LOG(m) \
		std::stringstream _internal_ss; \
		_internal_ss << this; \
		SCREEN_SCOPE_CALL(screen::utils::CALL_CONSTRUCTOR,_getClassName(),#m,_internal_ss.str());
#else
#	define SCREEN_DECL_CONSTRUCTOR_LOG(m)
#endif

#ifdef USE_SCREEN_PROFILE
#	define SCREEN_DECL_CONSTRUCTOR_PROFILE(m) \
		std::stringstream _internal_ss2; \
		_internal_ss2 << "constructor | " << _getClassName() << "::" << #m << "() | " << this; \
		SCREEN_SCOPE_PROFILE(_internal_ss2.str());
#else
#	define SCREEN_DECL_CONSTRUCTOR_PROFILE(m)
#endif


#define SCREEN_DECL_CONSTRUCTOR(m) \
	SCREEN_DECL_CONSTRUCTOR_LOG(m) \
	SCREEN_DECL_CONSTRUCTOR_PROFILE(m)

//destructor

#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_DESTRUCTOR_LOG(m) \
		std::stringstream _internal_ss; \
		_internal_ss << this; \
		SCREEN_SCOPE_CALL(screen::utils::CALL_DESTRUCTOR,_getClassName(),#m,_internal_ss.str());
#else
#	define SCREEN_DECL_DESTRUCTOR_LOG(m)
#endif

#ifdef USE_SCREEN_PROFILE
#	define SCREEN_DECL_DESTRUCTOR_PROFILE(m) \
		std::stringstream _internal_ss2; \
		_internal_ss2 << "destructor | " << _getClassName() << "::" << #m << "() | " << this; \
		SCREEN_SCOPE_PROFILE(_internal_ss2.str());
#else
#	define SCREEN_DECL_DESTRUCTOR_PROFILE(m)
#endif


#define SCREEN_DECL_DESTRUCTOR(m) \
	SCREEN_DECL_DESTRUCTOR_LOG(m) \
	SCREEN_DECL_DESTRUCTOR_PROFILE(m)

//function
#ifdef USE_SCREEN_LOG_CALL_TRACER
#	define SCREEN_DECL_FUNCTION_LOG(f) \
		SCREEN_SCOPE_CALL(screen::utils::CALL_FUNCTION,"",#f,"");
#else
#	define SCREEN_DECL_FUNCTION_LOG(f)
#endif

#ifdef USE_SCREEN_PROFILE
#	define SCREEN_DECL_FUNCTION_PROFILE(f) \
		std::stringstream _internal_ss2; \
		_internal_ss2 << "function | " << #f << "()"; \
		SCREEN_SCOPE_PROFILE(_internal_ss2.str());
#else
#	define SCREEN_DECL_FUNCTION_PROFILE(f)
#endif
#define SCREEN_DECL_FUNCTION(f) \
	SCREEN_DECL_FUNCTION_LOG(f) \
	SCREEN_DECL_FUNCTION_PROFILE(f)

		

#endif
