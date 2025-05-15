#include "../../includes/math/dice.h"
#include <numeric>
#include <algorithm>
uint32_t gl::math::roll(const uint32_t face, rng_ui32& rng)
{
	return rng.get(gl::math::closed_range<uint32_t>(1, face));
}

float gl::math::average_roll(const uint32_t face)
{
	return (1.0f + static_cast<float>(face & 0xffffff)) / 2.0f;
}

uint32_t gl::math::roll_list(const std::list<uint32_t>& faces, rng_ui32& rng)
{
	uint32_t result = 0;
	for (auto d : faces)
	{
		result += roll(d, rng);
	}
	return result;
}

std::list<uint32_t> gl::math::parted_roll_list(const std::list<uint32_t>& faces, rng_ui32& rng)
{
	std::list<uint32_t> result_list;
	for (auto d : faces)
	{
		result_list.push_back(roll(d, rng));
	}
	return result_list;
}

uint32_t gl::math::min_roll(const std::list<uint32_t>& faces)
{
	return static_cast<uint32_t>(faces.size());
}

uint32_t gl::math::max_roll(const std::list<uint32_t>& faces)
{
	return std::accumulate(faces.begin(), faces.end(), 0);
}

float gl::math::average_roll_list(const std::list<uint32_t>& faces)
{
	float result = 0;
	for (auto d : faces)
	{
		result += average_roll(d);
	}
	return result;
}

std::list<float> gl::math::parted_average_roll_list(const std::list<uint32_t>& faces)
{
	std::list<float> result_list;
	for (auto d : faces)
	{
		result_list.push_back(average_roll(d));
	}
	return result_list;
}
