#pragma once

#include "common/error/error.h"

namespace							common
{
	template						<typename final_type>
	class							global
	{
	public :
									global() = default;
		virtual						~global() = default;

		static void					initialize()
		{
			global					temporary;

			pointer = temporary.initializer();
		}

	protected :

		static auto					instance()
		{
			if (not pointer)
				common::error::raise(common::error::id::empty_global_object);

			return (pointer);
		}

		virtual
		std::shared_ptr<final_type>	initializer()
		{
			return (std::make_shared<final_type>());
		}

	private :

		static
		inline
		std::shared_ptr<final_type>	pointer;
	};
}