#ifndef GLLIB_GLLCORE_H_INCLUDED
#define GLLIB_GLLCORE_H_INCLUDED

#define THIS_IS_STATIC_CLASS(class_name) \
	class_name() = delete;\
	class_name(const class_name&) = delete;\
	class_name(class_name&&) = delete;\
	class_name& operator=(const class_name&) = delete;\
	class_name& operator=(class_name&&) = delete;\
	~class_name() = delete;

#endif