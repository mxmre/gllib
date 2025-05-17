#ifndef GLLIB_ALGORITHMS_H_INCLUDED
#define GLLIB_ALGORITHMS_H_INCLUDED
#include "../math/range_types.h"
#include <numeric>
namespace gl::algorithms
{
	template <class _Iter, class _RangeType>
	void from_range(_Iter first, _Iter last, const math::closed_range<_RangeType> range)
	{
		_from_range(first, last, range.get_min(), range.get_max());
	}
	template <class _Iter, class _RangeType>
	void _from_range(_Iter first, _Iter last, const _RangeType min_val, const _RangeType max_val)
	{
		_STD _Adl_verify_range(first, last);
		auto _UFirst = _STD _Get_unwrapped(first);
		const auto _ULast = _STD _Get_unwrapped(last);
		if (_UFirst == _ULast) 
		{
			return;
		}

		auto _UTarget = _UFirst;
		auto _FromRange = min_val;
		auto _FromRangeMax = max_val;
			
		for (; ++_UTarget != _ULast; ++_FromRange)
		{
			*_UTarget = _FromRange;
			if(_FromRange == _FromRangeMax)
				_FromRange = min_val;
		}
	}
}


#endif
