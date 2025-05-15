#ifndef GLLIB_LOGIC_ATTRIBUTE_H_INCLUDED
#define GLLIB_LOGIC_ATTRIBUTE_H_INCLUDED
#include "math/range_types.h"
namespace gl
{
	template<class T>
	class LogicAttribute
	{
		math::closed_range<T> _range;
		T _attribute_value;
	public:
		LogicAttribute(const T& attribute_value, const math::closed_range<T>& range)
			: _attribute_value(attribute_value), _range(range)
		{
			this->set_attribute_value(attribute_value);
		}
		void set_game_attribute(const T& attribute_value, const math::closed_range<T>& range)
		{
			this->_range = range;
			this->set_attribute_value(attribute_value);
		}
		void set_attribute_value(const T& attribute_value)
		{
			switch (this->_range.in_range(attribute_value))
			{
			case gl::math::range_relation::inside:
				this->_attribute_value = attribute_value;
				break;
			case gl::math::range_relation::left:
				this->_attribute_value = this->get_min();
				break;
			case gl::math::range_relation::right:
				this->_attribute_value = this->get_max();
				break;
			}
		}
		void add_to_attribute_value(const T& attribute_value)
		{
			this->set_attribute_value(attribute_value + this->get_attribute_value());
		}
		T get_min() const
		{
			return this->_range.get_min();
		}
		T get_max() const
		{
			return this->_range.get_max();
		}
		T get_attribute_value() const
		{
			return this->_attribute_value;
		}
	};
}
#endif