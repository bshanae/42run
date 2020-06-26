#pragma once

#define	IMPLEMENT_GLOBAL_INSTANCER(class_name)									\
static std::shared_ptr<class_name>		&instance(bool safe = true)				\
{																				\
	static std::shared_ptr<class_name>	instance;								\
																				\
	if (safe and not instance)													\
		common::error::raise(common::error::id::empty_global_object);			\
	return (instance);															\
}

#define	IMPLEMENT_GLOBAL_INITIALIZER(class_name)								\
static void								initialize()							\
{																				\
	instance(false) = std::shared_ptr<class_name>(new class_name());			\
}