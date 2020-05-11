#pragma once

#define IMPLEMENT_SHARED_POINTER_FUNCTIONALITY(class_name)						\
	using				ptr = shared_ptr<class_name>;							\
																				\
	template			<typename ...args_type>									\
	static inline auto	make_ptr(args_type ...args)								\
	{																			\
		return (make_shared<class_name>(args...));								\
	}

#define IMPLEMENT_UNIQUE_POINTER_FUNCTIONALITY(class_name)						\
	using				ptr = unique_ptr<class_name>;							\
																				\
	template			<typename ...args_type>									\
	static inline auto	make_ptr(args_type ...args)								\
	{																			\
		return (make_unique<class_name>(args...));								\
	}