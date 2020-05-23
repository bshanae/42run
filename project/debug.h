#pragma once

#include <iostream>

#define DEBUG_OPENGL(mark)														\
	if (auto error = glGetError(); error)										\
    {																			\
    	std::cerr << "Mark = " << mark << std::endl;							\
        std::cerr << "OpenGL Error: " << error << std::endl;					\
        std::terminate();														\
    }

#define DEBUG_MARK(id) std::cerr << "DEBUG MARK " << id << std::endl;