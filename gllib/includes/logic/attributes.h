#ifndef GLLIB_LOGIC_ATTRIBUTES_H_INCLUDED
#define GLLIB_LOGIC_ATTRIBUTES_H_INCLUDED
#include "../math/range_types.h"
namespace gl
{
	template<class T>
	struct modifier_t
	{
		T modifier_value;
		modifier_t(const T mod)
			: modifier_t(mod, mod)
		{

		}
		modifier_t(const T mod, const T mod_setup)
			: modifier_value{ mod }, modifier_setup_value{ mod_setup }
		{

		}

		void reset()
		{
			this->modifier_value = this->modifier_setup_value;
		}

		T get_modifier_setup() const
		{
			return this->modifier_setup_value;
		}
		bool operator==(const modifier_t<T>& other) const
		{
			return this->modifier_setup_value == other.modifier_setup_value &&
				this->modifier_value == other.modifier_value;
		}
	private:
		T modifier_setup_value;
	};
	template<class T>
	struct stat_t
	{
		T value;
		modifier_t<T> modifier;
		stat_t(const T value, const T mod)
			: stat_t(value, mod, mod) {
		}
		stat_t(const T value, const T mod, const T mod_setup)
			: value{ value }, modifier{ mod, mod_setup } {
		}


		stat_t<T>& operator+=(const stat_t<T>& other)
		{
			this->value += other.value;
			return *this;
		}

		bool operator>=(const stat_t<T> other) const
		{
			return this->value >= other.value;
		}
		bool operator>(const stat_t<T> other) const
		{
			return this->value > other.value;
		}
		bool operator<=(const stat_t<T> other) const
		{
			return this->value <= other.value;
		}
		bool operator<(const stat_t<T> other) const
		{
			return this->value < other.value;
		}

		bool operator==(const stat_t<T> other) const
		{
			return this->value == other.value;
		}
		bool operator!=(const stat_t<T> other) const
		{
			return this->value != other.value;
		}
	};
	template <typename T>
	stat_t<T> operator+(stat_t<T> lhs, const stat_t<T>& rhs) {
		lhs.value += rhs.value;
		return lhs;
	}

	template<class T>
	class logic_attribute
	{
	protected:
		math::closed_range<T> _range;
		T _attribute_value;
	public:
		logic_attribute(const T& attribute_value, const math::closed_range<T>& range)
			: _attribute_value(attribute_value), _range(range)
		{
			this->set_attribute(attribute_value);
		}
		void set_attribute(const T& attribute_value)
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
		void add_to_attribute(const T& attribute_value)
		{
			this->set_attribute(attribute_value + this->get_attribute());
		}
		void set_min(const T& min)
		{
			this->_range.set_range(min, this->get_max());
			this->set_attribute(this->get_attribute());
		}
		void set_max(const T& max)
		{
			this->_range.set_range(this->get_min(), max);
			this->set_attribute(this->get_attribute());
		}
		T get_min() const
		{
			return this->_range.get_min();
		}
		T get_max() const
		{
			return this->_range.get_max();
		}
		T get_attribute() const
		{
			return this->_attribute_value;
		}
		bool operator==(const logic_attribute<T>& other) const
		{
			return this->_range == other._range && this->_attribute_value == other._attribute_value;
		}
	};
	template<class T>
	class modified_attribute : public logic_attribute<T>
	{
		
	public:
		modifier_t<T> attribute_modifier;
		modifier_t<T> min_modifier;
		modifier_t<T> max_modifier;

		modified_attribute(const T& attribute_value, const math::closed_range<T>& range,
			const modifier_t<T>& modifiers)
			: modified_attribute<T>(attribute_value, range, modifiers, modifiers, modifiers)
		{

		}
		modified_attribute(const T& attribute_value, const math::closed_range<T>& range,
			const modifier_t<T>& attribute_modifier,
			const modifier_t<T>& min_modifier,
			const modifier_t<T>& max_modifier)
			: logic_attribute<T>(attribute_value, range),
			attribute_modifier{ attribute_modifier },
			min_modifier{ min_modifier },
			max_modifier{ max_modifier }
		{

		}

		void reset_all()
		{
			this->attribute_modifier.reset();
			this->min_modifier.reset();
			this->max_modifier.reset();
		}

		bool operator==(const modified_attribute<T>& other) const
		{
			return static_cast<const logic_attribute<T>&>(*this) == 
				static_cast<const logic_attribute<T>&>(other) &&
				this->attribute_modifier == other.attribute_modifier &&
				this->min_modifier == other.min_modifier &&
				this->max_modifier == other.max_modifier;
		}
	};
}
#endif