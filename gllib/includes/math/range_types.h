#ifndef GLLIB_RANGE_TYPES_H_INCLUDED
#define GLLIB_RANGE_TYPES_H_INCLUDED
#include <exception>
#include <stdexcept>
#include <cstdint>

namespace gl
{
	namespace math
	{
		template <class T> struct open_range_check
		{
			static bool less_than_check(const T& lhs, const T& rhs)
			{
				return lhs <= rhs;
			}
			static bool greater_than_check(const T& lhs, const T& rhs)
			{
				return lhs > rhs;
			}
		};
		template <class T> struct closed_range_check
		{
			static bool less_than_check(const T& lhs, const T& rhs)
			{
				return lhs < rhs;
			}
			static bool greater_than_check(const T& lhs, const T& rhs)
			{
				return lhs >= rhs;
			}
		};
		enum class range_relation
		{
			inside = 0,
			left,
			right
		};
		template <class T, class _MinCheck, class _MaxCheck>
		struct range_t
		{
			using range_value_type = T;
			range_t(const T& min, const T& max)
			{
				this->set_range(min, max);
			}
			void set_range(const T& min, const T& max)
			{
				if (max > min)
				{
					this->_min = min;
					this->_max = max;
				}
				else throw std::invalid_argument("must be this: min < max");
			}
			range_relation in_range(const T& val) const
			{
				if (_MinCheck::less_than_check(val, this->_min))
					return range_relation::left;
				if (_MaxCheck::greater_than_check(val, this->_max))
					return range_relation::right;
				return range_relation::inside;
				
			}
			T get_min() const
			{
				return this->_min;
			}
			T get_max() const
			{
				return this->_max;
			}
		private:
			T _min, _max;
		};
		template <class T> using closed_range = range_t<T, closed_range_check<T>, closed_range_check<T>>;
		template <class T> using oc_range = range_t<T, open_range_check<T>, closed_range_check<T>>;
		template <class T> using co_range = range_t<T, closed_range_check<T>, open_range_check<T>>;
		template <class T> using open_range = range_t<T, open_range_check<T>, open_range_check<T>>;
	}
	
}
#endif