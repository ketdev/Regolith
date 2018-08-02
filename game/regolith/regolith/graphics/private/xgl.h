#pragma once

#if defined _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/wglew.h>
#include <GLFW/glfw3.h>
#elif defined __ANDROID__
#include <EGL/egl.h>
//#include <GLES/gl.h>
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#endif

#include <glm/glm.hpp>
using namespace glm;

#if defined _MSC_VER
#define ALIGN(x) __declspec(align(x))
#elif defined __GNUC__
#define ALIGN(x) __attribute__((aligned(x)))
#endif
