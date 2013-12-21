/************************************************************************************

 Authors     :   Bradley Austin Davis <bdavis@saintandreas.org>
 Copyright   :   Copyright Brad Davis. All Rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 ************************************************************************************/

#pragma once


#ifdef WIN32
#include <Windows.h>
#endif

#define __STDC_FORMAT_MACROS 1

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>
#include <list>
#include <algorithm>
#include <array>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtx/noise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifdef __APPLE__
#define GL_GLEXT_PROTOTYPES
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <GL/glew.h>
#endif
#include <OVR.h>
#undef new

#ifdef __APPLE__
//#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
//#define glGenVertexArrays glGenVertexArraysAPPLE
//#define glBindVertexArray glBindVertexArrayAPPLE
#pragma thanks_obama
#endif

#include <GlDebug.h>
#include <GlMethods.h>

#include <GlBuffers.h>
#include <GlFrameBuffer.h>
#include <GlStacks.h>
#include <GlQuery.h>
#include <GlShaders.h>
#include <GlGeometry.h>
#include <GlLighting.h>

#include <Resources.h>

template<class T>
class circular_buffer : public std::list<T>{
  size_t max;
public:
  circular_buffer(size_t max) : max(max) {
  }
  void push_back(const T & t) {
    std::list<T>::push_back(t);
    while (std::list<T>::size() > max) {
      std::list<T>::pop_front();
    }
  }
};


class Platform {
public:
	static const std::string & getResourcePath(Resource resource) {
		return ::getResourcePath(resource);
	}
    static void sleepMillis(int millis);
    static long elapsedMillis();
    static void fail(const char * file, int line, const char * message, ...);
    static void say(std::ostream & out, const char * message, ...);
};

#ifndef PI
#define PI 3.14159265f
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES (180.0f / PI)
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS (PI / 180.0f)
#endif

// Windows has a non-standard main function prototype
#ifdef WIN32
    #define MAIN_DECL int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
    #define MAIN_DECL int main(int argc, char ** argv)
#endif

#define FAIL(...) Platform::fail(__FILE__, __LINE__, __VA_ARGS__)
#define SAY(...) Platform::say(std::cout, __VA_ARGS__)
#define SAY_ERR(...) Platform::say(std::cerr, __VA_ARGS__)

// Combine some macros together to create a single macro
// to run an example app
#define RUN_APP(AppClass) \
    MAIN_DECL { \
        try { \
            return AppClass().run(); \
        } catch (const std::string & error) { \
            SAY(error.c_str()); \
        } \
        return -1; \
    }

#include "Shaders.h"
#include "Config.h"

#include "Font.h"
#include "Files.h"

#include "GlMesh.h"
#include "GlUtils.h"
#include "GlfwApp.h"

#include "Interaction.h"

#include "Rift.h"
