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

#include <screen/opengl/OpenGLRenderer.h>
#include <screen/opengl/OpenGLException.h>
#include <screen/opengl/OpenGLBuffer.h>
#include <screen/opengl/OpenGLTexture.h>
#include <screen/opengl/OpenGLPixelFormat.h>
#include <screen/core/objects/TextureBase.h>
#include <screen/math/Matrix4x4f.h>
#include <screen/math/Vector2i.h>
#include <glm/gtc/type_ptr.hpp>

#define BUFFER_OFFSET(n) ((char*)NULL + (n))

namespace screen {
    namespace opengl {
    	OpenGLRenderer::OpenGLRenderer()
    		:Renderer(){
    	}
    	
    	OpenGLRenderer::~OpenGLRenderer(){}
    	
    	OpenGLRenderer* OpenGLRenderer::instance(){
    		return new OpenGLRenderer();
    	}
    
    	void OpenGLRenderer::initialize(){
    	    // Enable Z-buffer read and write
    	    glEnable(GL_DEPTH_TEST);
    	    glDepthMask(GL_TRUE);
    	    glClearDepth(1.f);

    	    // Setup a perspective projection
    	    glMatrixMode(GL_PROJECTION);
    	    glLoadIdentity();
    	    gluPerspective(90.f, 1.f, 1.f, 500.f);
    	    
    	    openGLExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
    	    loadExtensions();
    	}

		template <class T> inline void loadExtension(T& Proc, const char* Name){
#ifdef WIN32
		    if (!(Proc = reinterpret_cast<T>(wglGetProcAddress(Name))))
		        throw OpenGLException("wglGetProcAddress", "LoadExtension");
#else
		    if (!(Proc = reinterpret_cast<T>(glXGetProcAddress((const GLubyte *)Name))))
		        throw OpenGLException("glXGetProcAddress", "LoadExtension");
#endif
		}
		
		bool OpenGLRenderer::checkExtension(const std::string& extension) const{
		    return openGLExtensions.find(extension) != std::string::npos;
		}
		
#define LOAD_EXTENSION(Ext) loadExtension(Ext, #Ext)
#define CHECK_EXTENSION(Ext) if (!checkExtension(Ext)) throw OpenGLException(#Ext, "CheckExtensions");
    	
    	void OpenGLRenderer::loadExtensions(){
    	    // Vérification des extensions de base
    	    CHECK_EXTENSION("GL_ARB_vertex_buffer_object");
    	    CHECK_EXTENSION("GL_ARB_multitexture");
    	    //CHECK_EXTENSION("GL_ARB_texture_non_power_of_two");
    	    //CHECK_EXTENSION("WGL_ARB_pbuffer");

    	    // Chargement des extensions
    	    LOAD_EXTENSION(glBindBufferARB);
    	    LOAD_EXTENSION(glDeleteBuffersARB);
    	    LOAD_EXTENSION(glGenBuffersARB);
    	    LOAD_EXTENSION(glBufferDataARB);
    	    LOAD_EXTENSION(glBufferSubDataARB);
    	    LOAD_EXTENSION(glGetBufferSubDataARB);
    	    LOAD_EXTENSION(glMapBufferARB);
    	    LOAD_EXTENSION(glUnmapBufferARB);
    	    LOAD_EXTENSION(glActiveTextureARB);
    	    LOAD_EXTENSION(glClientActiveTextureARB);
    	    LOAD_EXTENSION(glCompressedTexSubImage2DARB);
#ifdef WIN32
    	    LOAD_EXTENSION(wglChoosePixelFormatARB);
    	    LOAD_EXTENSION(wglCreatePbufferARB);
    	    LOAD_EXTENSION(wglGetPbufferDCARB);
    	    LOAD_EXTENSION(wglReleasePbufferDCARB);
    	    LOAD_EXTENSION(wglDestroyPbufferARB);
    	    LOAD_EXTENSION(wglQueryPbufferARB);
#else
    	    
#endif
    	    //check OpenGL capabilities
    	    capabilityTable[screen::core::CAPABILITY_NON_POWER_OF_TWO_TEXTURE] = checkExtension("GL_ARB_texture_non_power_of_two");
   	    	capabilityTable[screen::core::CAPABILITY_COMPRESSED_TEXTURE] = checkExtension("GL_ARB_texture_compression") && checkExtension("GL_EXT_texture_compression_s3tc");
    		capabilityTable[screen::core::CAPABILITY_HARDWARE_MIPMAP] = checkExtension("GL_SGIS_generate_mipmap");
    	}
    	
#undef LOAD_EXTENSION
#undef CHECK_EXTENSION
    	
    	void OpenGLRenderer::beginScene(){
	        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    	}
    	
    	void OpenGLRenderer::endScene(){
	        renderWindow->swapBuffers();
    	}
    	
    	bool OpenGLRenderer::hasCapability(screen::core::ApiCapability caps) const{
    		return capabilityTable[caps];
    	}
    	
    	void OpenGLRenderer::pushMatrix(screen::core::MatrixType type){
    	    if (type >= screen::core::MATRIX_TEXTURE0)
    	        glActiveTextureARB(GL_TEXTURE0_ARB + type - screen::core::MATRIX_TEXTURE0);

    	    glMatrixMode(glMatrixType[type]);
    	    glPushMatrix();
    	}

    	void OpenGLRenderer::popMatrix(screen::core::MatrixType type){
    	    if (type >= screen::core::MATRIX_TEXTURE0)
    	        glActiveTextureARB(GL_TEXTURE0_ARB + type - screen::core::MATRIX_TEXTURE0);

    	    glMatrixMode(glMatrixType[type]);
    	    glPopMatrix();
    	}

        void OpenGLRenderer::setMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix){
    	    if (type >= screen::core::MATRIX_TEXTURE0)
    	        glActiveTextureARB(GL_TEXTURE0_ARB + type - screen::core::MATRIX_TEXTURE0);

    	    glMatrixMode(glMatrixType[type]);
            glLoadMatrixf(glm::value_ptr(matrix));
    	}

        void OpenGLRenderer::multipleMatrix(screen::core::MatrixType type, const glm::mat4x4& matrix){
    	    if (type >= screen::core::MATRIX_TEXTURE0)
    	        glActiveTextureARB(GL_TEXTURE0_ARB + type - screen::core::MATRIX_TEXTURE0);

    	    glMatrixMode(glMatrixType[type]);
            glMultMatrixf(glm::value_ptr(matrix));
    	}

        void OpenGLRenderer::getMatrix(screen::core::MatrixType type, glm::mat4x4& matrix){
    	    if (type >= screen::core::MATRIX_TEXTURE0)
    	        glActiveTextureARB(GL_TEXTURE0_ARB + type - screen::core::MATRIX_TEXTURE0);

            glGetFloatv(glMatrixType[type], glm::value_ptr(matrix));
    	}
    	
    	unsigned long OpenGLRenderer::convertColor(const screen::core::Color& color) const{
    		return color.convertABGR();
    	}
    	
    	const screen::core::Color& OpenGLRenderer::retrieveColor(unsigned long color) const{
    		static screen::core::Color c;
    		screen::core::Color tmp(color);
    		c.set(tmp.convertABGR()); //convert * convert = Id
    		return c;
    	}
    	
    	screen::core::BufferBase* OpenGLRenderer::createVB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{
    	    // buffer creation
    	    unsigned int vertexBuffer = 0;
    	    glGenBuffersARB(1, &vertexBuffer);

    	    // fill
    	    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBuffer);
    	    glBufferDataARB(GL_ARRAY_BUFFER_ARB, size * stride, NULL, glBufferFlags[flags]);

    	    return new OpenGLVertexBuffer(size, vertexBuffer);
    	}
    	
    	screen::core::BufferBase* OpenGLRenderer::createIB(unsigned long size, unsigned long stride, screen::core::BufferFlag flags) const{
            // buffer creation
            unsigned int indexBuffer = 0;
            glGenBuffersARB(1, &indexBuffer);

            // fill
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, indexBuffer);
            glBufferDataARB(GL_ARRAY_BUFFER_ARB, size * stride, NULL, glBufferFlags[flags]);

            return new OpenGLIndexBuffer(size, indexBuffer);
        }
        
        void OpenGLRenderer::setVB(const screen::core::BufferBase* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex,const screen::core::VertexFormat& vf){
            // send OpenGL buffer to API
            const OpenGLVertexBuffer* vertexBuffer = static_cast<const OpenGLVertexBuffer*>(buffer);
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertexBuffer->getBuffer());

            // Tables de correspondance
            static const unsigned int size[] = {1, 2, 3, 4, 4};
            static const unsigned int offsetInc[] = {4, 8, 12, 16, 4};
            static const unsigned int type[] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

            unsigned int offset = 0;
            // Paramètrage des glPointer
            for (screen::core::VertexFormat::const_iterator i = vf.begin(); i != vf.end(); ++i){
                switch ((*i)->getUsage()){
                    // Position
                    case screen::core::VERTEX_USAGE_POSITION :
                        glEnableClientState(GL_VERTEX_ARRAY);
                        glVertexPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Normale
                    case screen::core::VERTEX_USAGE_NORMAL :
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glNormalPointer(type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Couleur diffuse
                    case screen::core::VERTEX_USAGE_DIFFUSE :
                        glEnableClientState(GL_COLOR_ARRAY);
                        glColorPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Coordonnées de texture 0
                    case screen::core::VERTEX_USAGE_TEXCOORD0 :
                        glActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnable(GL_TEXTURE_2D);
                        glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glTexCoordPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Coordonnées de texture 1
                    case screen::core::VERTEX_USAGE_TEXCOORD1 :
                        glActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnable(GL_TEXTURE_2D);
                        glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glTexCoordPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Coordonnées de texture 2
                    case screen::core::VERTEX_USAGE_TEXCOORD2 :
                        glActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnable(GL_TEXTURE_2D);
                        glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glTexCoordPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;

                    // Coordonnées de texture 3
                    case screen::core::VERTEX_USAGE_TEXCOORD3 :
                        glActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnable(GL_TEXTURE_2D);
                        glClientActiveTextureARB(GL_TEXTURE0_ARB);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glTexCoordPointer(size[(*i)->getType()], type[(*i)->getType()], stride, BUFFER_OFFSET(offset + minVertex * stride));
                        break;
                }
                offset += offsetInc[(*i)->getType()];
            }
        }
        
        void OpenGLRenderer::setIB(const screen::core::BufferBase* buffer, unsigned long stride){
            // send OpenGL buffer to API
            const OpenGLIndexBuffer* indexBuffer = static_cast<const OpenGLIndexBuffer*>(buffer);
            glEnableClientState(GL_INDEX_ARRAY);
            glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indexBuffer->getBuffer());

            // Sauvegarde de la taille des indices
            indexStride = stride;
        }
        
        void OpenGLRenderer::drawIndexedPrimitives(screen::core::PrimitiveType type, unsigned long firstIndex, unsigned long count) const{
            const void* offset = BUFFER_OFFSET(firstIndex * indexStride);
            unsigned long indicesType = (indexStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);

            // Affichage des primitives
            switch (type)
            {
                case screen::core::PRIMITIVE_TRIANGLELIST :  glDrawElements(GL_TRIANGLES,      count * 3, indicesType, offset); break;
                case screen::core::PRIMITIVE_TRIANGLESTRIP : glDrawElements(GL_TRIANGLE_STRIP, count + 2, indicesType, offset); break;
                case screen::core::PRIMITIVE_TRIANGLEFAN :   glDrawElements(GL_TRIANGLE_FAN,   count + 1, indicesType, offset); break;
                case screen::core::PRIMITIVE_LINELIST :      glDrawElements(GL_LINES,          count * 2, indicesType, offset); break; 
                case screen::core::PRIMITIVE_LINESTRIP :     glDrawElements(GL_LINE_STRIP,     count + 1, indicesType, offset); break;
                case screen::core::PRIMITIVE_POINTLIST :     glDrawElements(GL_POINTS,         count,     indicesType, offset); break;
            }
        }
        
        screen::core::objects::TextureBase* OpenGLRenderer::createTexture(const screen::math::Vector2i& size, screen::core::PixelFormat pxf, screen::core::TextureFlag flags) const{
            // Texture generation
            unsigned int texture;
            glGenTextures(1, &texture);

            // texture binding
            glBindTexture(GL_TEXTURE_2D, texture);

            // parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            
            OpenGLPixelFormat texturePxf = oglPxf[pxf];
            glTexImage2D(GL_TEXTURE_2D, 0, texturePxf.fullFormat, size.getX(), size.getY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

            // mipmapping (0 for now)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

            // texture unbinding
            glBindTexture(GL_TEXTURE_2D, 0);

            return new OpenGLTexture(texture, size, pxf, screen::core::TEXTURE_NO_MIPMAP);
        }
        
        void OpenGLRenderer::setTextureBase(const screen::core::objects::TextureBase* texture){
            glActiveTextureARB(GL_TEXTURE0_ARB);
            const OpenGLTexture* glTexture = dynamic_cast<const OpenGLTexture*>(texture);

            if (glTexture != NULL){
            	SCREEN_LOG_DEBUG("Bind texture");
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, glTexture->getTextureNumber());
            }
            else{
            	SCREEN_LOG_DEBUG("Unbind texture");
            	glDisable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

    	unsigned long OpenGLRenderer::glMatrixType[] ={
		    GL_MODELVIEW,
		    GL_PROJECTION,
		    GL_TEXTURE,
		    GL_TEXTURE,
		    GL_TEXTURE,
		    GL_TEXTURE
    	};
    	
    	unsigned long OpenGLRenderer::glBufferFlags[] ={
    		GL_STATIC_DRAW_ARB,
    		GL_DYNAMIC_DRAW_ARB
    	};
    	
    	PFNGLBINDBUFFERARBPROC          	OpenGLRenderer::glBindBufferARB;
    	PFNGLDELETEBUFFERSARBPROC       	OpenGLRenderer::glDeleteBuffersARB;
    	PFNGLGENBUFFERSARBPROC          	OpenGLRenderer::glGenBuffersARB;
    	PFNGLBUFFERDATAARBPROC          	OpenGLRenderer::glBufferDataARB;
    	PFNGLBUFFERSUBDATAARBPROC       	OpenGLRenderer::glBufferSubDataARB;
    	PFNGLGETBUFFERSUBDATAARBPROC    	OpenGLRenderer::glGetBufferSubDataARB;
    	PFNGLMAPBUFFERARBPROC           	OpenGLRenderer::glMapBufferARB;
    	PFNGLUNMAPBUFFERARBPROC         	OpenGLRenderer::glUnmapBufferARB;
    	PFNGLACTIVETEXTUREARBPROC       	OpenGLRenderer::glActiveTextureARB;
    	PFNGLCLIENTACTIVETEXTUREARBPROC 	OpenGLRenderer::glClientActiveTextureARB;
        PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC OpenGLRenderer::glCompressedTexSubImage2DARB;
#ifdef WIN32
    	PFNWGLCHOOSEPIXELFORMATARBPROC  	OpenGLRenderer::wglChoosePixelFormatARB;
    	PFNWGLCREATEPBUFFERARBPROC      	OpenGLRenderer::wglCreatePbufferARB;
    	PFNWGLGETPBUFFERDCARBPROC       	OpenGLRenderer::wglGetPbufferDCARB;
    	PFNWGLRELEASEPBUFFERDCARBPROC   	OpenGLRenderer::wglReleasePbufferDCARB;
    	PFNWGLDESTROYPBUFFERARBPROC     	OpenGLRenderer::wglDestroyPbufferARB;
    	PFNWGLQUERYPBUFFERARBPROC       	OpenGLRenderer::wglQueryPbufferARB;
#else
    	
#endif
    }
}

