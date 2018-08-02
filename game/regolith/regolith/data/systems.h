#pragma once

#include <vector>

namespace data {

	struct ISystem {
		// Called per iteration on active systems
		virtual void update() = 0;
	};

	// All our system instances
	extern std::vector<ISystem*> Systems;
	
}