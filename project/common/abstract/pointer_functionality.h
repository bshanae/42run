#pragma once

#include <memory>

#define IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(class_name)						\
using				ptr = std::shared_ptr<class_name>;							\
																				\
template			<typename ...args_type>										\
static inline auto	make_ptr(args_type &&...args)								\
{																				\
	auto			*raw = new class_name(args...);								\
	return (std::shared_ptr<class_name>(raw));									\
}

#define IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(class_name)						\
using				ptr = std::unique_ptr<class_name>;							\
																				\
template			<typename ...args_type>										\
static inline auto	make_ptr(args_type &&...args)								\
{																				\
	auto			*raw = new class_name(args...);								\
	return (std::unique_ptr<class_name>(raw));									\
}