#pragma once

#include <string.h>
#include <malloc.h>
#include <regolith\types.h>

namespace regolith {
	namespace system {

		// Our saved state data.
		class SavedState {
		public:
			float angle;
			int32 x;
			int32 y;

			void load(void* data, size_t size) {
				if (data != NULL) {
					memcpy(this, data, size);
				}
			}

			void save(void*& out_data, size_t& out_size) {
				// The system has asked us to save our current state.  Do so.
				out_size = sizeof(SavedState);
				out_data = malloc(out_size);
				memcpy(out_data, this, out_size);
			}

		};

	}
}