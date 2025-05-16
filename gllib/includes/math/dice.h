#ifndef GLLIB_DICE_H_INCLUDED
#define GLLIB_DICE_H_INCLUDED
#include "rng.h"
#include <list>
namespace gl::math
{
	uint32_t roll(const uint32_t face, rng_ui32& rng);

	uint32_t roll_list(const std::list<uint32_t>& faces, rng_ui32& rng);

	std::list<uint32_t> parted_roll_list(const std::list<uint32_t>& faces, rng_ui32& rng);

	uint32_t min_roll(const std::list<uint32_t>& faces);

	uint32_t max_roll(const std::list<uint32_t>& faces);

	float average_roll(const uint32_t face);

	float average_roll_list(const std::list<uint32_t>& faces);

	std::list<float> parted_average_roll_list(const std::list<uint32_t>& faces);
}

#endif
