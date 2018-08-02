#pragma once

#include <regolith/types.h>

namespace regolith {
	namespace math {

		template<uint32 _Dim>
		struct ALIGN(1) Vector {
			typedef float type_t;
			static const uint32 Dimension = _Dim;

			type_t data[Dimension];
		};

	}
}