#ifndef GLLIB_RNG_H_INCLUDED
#define GLLIB_RNG_H_INCLUDED
#include <random>
#include <array>
#include <algorithm>
#include "range_types.h"
namespace gl::math
{
	template<class _Rg, class _D>
	class random_number_generator
	{
	public:
		using rng_type = _Rg;
		using distribution_type = _D;
		using result_type = typename _D::result_type;
		using seed_type = typename _Rg::result_type;

		random_number_generator(seed_type seed)
			: _rng{ seed }
		{
		}

		result_type get()
		{
			static distribution_type dist;
			return dist(_rng);
		}
		result_type get(const closed_range<result_type>& range)
		{
			distribution_type dist(range.get_min(), range.get_max());
			return dist(_rng);
		}
		rng_type& engine()
		{
			return this->_rng;
		}
		const rng_type& engine() const
		{
			return this->_rng;
		}
	protected:
		rng_type _rng;
	};

	using rng_i16 = random_number_generator<std::mt19937, std::uniform_int_distribution<int16_t>>;
	using rng_i32 = random_number_generator<std::mt19937, std::uniform_int_distribution<int32_t>>;
	using rng_i64 = random_number_generator<std::mt19937_64, std::uniform_int_distribution<int64_t>>;
	using rng_ui16 = random_number_generator<std::mt19937, std::uniform_int_distribution<uint16_t>>;
	using rng_ui32 = random_number_generator<std::mt19937, std::uniform_int_distribution<uint32_t>>;
	using rng_ui64 = random_number_generator<std::mt19937_64, std::uniform_int_distribution<uint64_t>>;

	using rng_f32 = random_number_generator<std::mt19937, std::uniform_real_distribution<float>>;
	using rng_f64 = random_number_generator<std::mt19937_64, std::uniform_real_distribution<double>>;


	constexpr bool is_consecutive_ones(size_t x) {
		return x != 0 && (x == 0xffffffffffffffffUi64 || ((x & (x + 1)) == 0));
	}

	template<class _Rng, size_t _Sz>
	class random_numbers_table
	{

	public:
		using rng_type = _Rng;
		using result_type = typename _Rng::result_type;
		static const size_t table_size = _Sz;
		static_assert(table_size > 0, "table size cannot be zero!");

		random_numbers_table(rng_type& rng)
		{
			this->compute(rng);
		}
		random_numbers_table(rng_type& rng,
			const closed_range<result_type>& range)
		{
			this->compute(rng, range);
		}
		random_numbers_table(const std::array<result_type, table_size>& arr)
		{
			this->set(arr);
		}
		void set(const std::array<result_type, table_size>& arr)
		{
			this->_table = arr;
			this->_table_navigator = 0;
		}
		void compute(rng_type& rng)
		{
			for (size_t i = 0; i < table_size; ++i)
			{
				this->_table[i] = rng.get();
			}
			this->_table_navigator = 0;
		}
		void compute(rng_type& rng, const closed_range<result_type>& range)
		{
			for (size_t i = 0; i < table_size; ++i)
			{
				this->_table[i] = rng.get(range);
			}
			this->_table_navigator = 0;
		}
		void shuffle(rng_type& rng)
		{
			std::shuffle(this->_table.begin(), this->_table.end(), rng.engine());
		}
		void advance(const size_t step = 1)
		{
			this->_table_navigator += step;
			if constexpr (is_consecutive_ones(table_size - 1))
			{
				this->_table_navigator &= table_size - 1;
			}
			else
			{
				this->_table_navigator %= table_size;
			}
		}
		result_type get()
		{
			result_type result = this->_table[this->_table_navigator];
			this->advance();
			return result;
		}
		size_t navigator_position() const
		{
			return this->_table_navigator;
		}
	private:
		std::array<result_type, table_size> _table;
		size_t _table_navigator;
	};
}


#endif