#pragma once

#define IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(class_name)						\
using				ptr = shared_ptr<class_name>;								\
																				\
template			<typename ...args_type>										\
static inline auto	make_ptr(args_type ...args)									\
{																				\
	auto			*raw = new class_name(args...);								\
	return (shared_ptr<class_name>(raw));										\
}

#define IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(class_name)						\
using				ptr = unique_ptr<class_name>;								\
																				\
template			<typename ...args_type>										\
static inline auto	make_ptr(args_type ...args)									\
{																				\
	auto			*raw = new class_name(args...);								\
	return (unique_ptr<class_name>(raw));										\
}