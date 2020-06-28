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

#define	START_GLOBAL_INITIALIZER(class_name)									\
static void								initialize()							\
{																				\
	instance(false) = std::make_shared<class_name>();							\

#define	FINISH_GLOBAL_INITIALIZER												\
}