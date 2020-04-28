#pragma once

#define DEBUG_OPENGL(mark)														\
	if (auto error = glGetError(); error)										\
    {																			\
    	std::cerr << "Mark = " << mark << std::endl;							\
        std::cerr << "OpenGL Error: " << error << std::endl;					\
        std::terminate();														\
    }