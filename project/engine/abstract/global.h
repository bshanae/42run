#pragma once

#define	IMPLEMENT_GLOBAL_INSTANCER(class_name)									\
static shared_ptr<class_name>		&instance(bool safe = true)					\
{																				\
	static shared_ptr<class_name>	instance;									\
																				\
	if (safe and not instance)													\
		throw (exception::exception<exception::id::empty_global_object>());		\
	return (instance);															\
}

#define	IMPLEMENT_GLOBAL_INITIALIZER(class_name)								\
static void							initialize()								\
{																				\
	instance(false) = shared_ptr<class_name>(new class_name());					\
}

#define	START_GLOBAL_CUSTOM_INITIALIZER(class_name)								\
static void							initialize()								\
{																				\
	instance(false) = shared_ptr<class_name>(new class_name());					\

#define	FINISH_GLOBAL_CUSTOM_INITIALIZER										\
}