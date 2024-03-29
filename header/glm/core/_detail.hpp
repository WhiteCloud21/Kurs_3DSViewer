///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-07-24
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : glm/core/_detail.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_detail
#define glm_core_detail

#include "../setup.hpp"
#include <cassert>

//#define valType			typename genType::value_type
//#define valType_cref	typename genType::value_type const &
//#define genType_cref	typename genType const &

namespace glm{
namespace detail{

	class thalf;

#if(defined(GLM_COMPILER) && (GLM_COMPILER & GLM_COMPILER_VC))
	typedef signed __int64						sint64;
	typedef unsigned __int64					uint64;
#elif(defined(GLM_COMPILER) && (GLM_COMPILER & GLM_COMPILER_GCC))
	__extension__ typedef signed long long		sint64;
	__extension__ typedef unsigned long long	uint64;
#else//unknown compiler
	typedef signed long							sint64;
	typedef unsigned long						uint64;
#endif//GLM_COMPILER

	template<bool C>
	struct If
	{
		template<typename F, typename T>
		static inline T apply(F functor, const T& val)
		{
			return functor(val);
		}
	};

	template<>
	struct If<false>
	{
		template<typename F, typename T>
		static inline T apply(F, const T& val)
		{
			return val;
		}
	};

	//template <typename T>
	//struct traits
	//{
	//	static const bool is_signed = false;
	//	static const bool is_float = false;
	//	static const bool is_vector = false;
	//	static const bool is_matrix = false;
	//	static const bool is_genType = false;
	//	static const bool is_genIType = false;
	//	static const bool is_genUType = false;
	//};

	//template <>
	//struct traits<half>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <>
	//struct traits<float>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <>
	//struct traits<double>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <typename genType>
	//struct desc
	//{
	//	typedef genType							type;
	//	typedef genType *						pointer;
	//	typedef genType const*					const_pointer;
	//	typedef genType const *const			const_pointer_const;
	//	typedef genType *const					pointer_const;
	//	typedef genType &						reference;
	//	typedef genType const&					const_reference;
	//	typedef genType const&					param_type;

	//	typedef typename genType::value_type	value_type;
	//	typedef typename genType::size_type		size_type;
	//	static const typename size_type			value_size;
	//};

	//template <typename genType>
	//const typename desc<genType>::size_type desc<genType>::value_size = genType::value_size();

	union uif32
	{
		uif32() :
			i(0)
		{}

		uif32(float f) :
			f(f)
		{}

		uif32(unsigned int i) :
			i(i)
		{}

		float f;
		unsigned int i;
	};

	union uif64
	{
		uif64() :
			i(0)
		{}

		uif64(double f) :
			f(f)
		{}

		uif64(uint64 i) :
			i(i)
		{}

		double f;
		uint64 i;
	};

	typedef uif32 uif;

	//////////////////
	// int

	template <typename T>
	struct is_int
	{
		enum is_int_enum
		{
			YES = 0,
			NO = 1
		};
	};

#define GLM_DETAIL_IS_INT(T)	\
	template <>					\
	struct is_int<T>			\
	{							\
		enum is_int_enum		\
		{						\
			YES = 1,			\
			NO = 0				\
		};						\
	}

	//////////////////
	// uint

	template <typename T>
	struct is_uint
	{
		enum is_uint_enum
		{
			YES = 0,
			NO = 1
		};
	};

#define GLM_DETAIL_IS_UINT(T)	\
	template <>					\
	struct is_uint<T>			\
	{							\
		enum is_uint_enum		\
		{						\
			YES = 1,			\
			NO = 0				\
		};						\
	}

	//GLM_DETAIL_IS_UINT(unsigned long long)

	//////////////////
	// float

	template <typename T>
	struct is_float
	{
		enum is_float_enum
		{
			YES = 0,
			NO = 1
		};
	};

#define GLM_DETAIL_IS_FLOAT(T)	\
	template <>					\
	struct is_float<T>			\
	{							\
		enum is_float_enum		\
		{						\
			YES = 1,			\
			NO = 0				\
		};						\
	}

	//////////////////
	// bool

	template <typename T>
	struct is_bool
	{
		enum is_bool_enum
		{
			YES = 0,
			NO = 1
		};
	};
	
	template <>
	struct is_bool<bool>
	{
		enum is_bool_enum
		{
			YES = 1,
			NO = 0
		};
	};
	
	//////////////////
	// vector

	template <typename T>
	struct is_vector
	{
		enum is_vector_enum
		{
			YES = 0,
			NO = 1
		};
	};

#define GLM_DETAIL_IS_VECTOR(T)	\
	template <>					\
	struct is_vector			\
	{							\
		enum is_vector_enum		\
		{						\
			YES = 1,			\
			NO = 0				\
		};						\
	}

	//////////////////
	// matrix

	template <typename T>
	struct is_matrix
	{
		enum is_matrix_enum
		{
			YES = 0,
			NO = 1
		};
	};

#define GLM_DETAIL_IS_MATRIX(T)	\
	template <>					\
	struct is_matrix			\
	{							\
		enum is_matrix_enum		\
		{						\
			YES = 1,			\
			NO = 0				\
		};						\
	}

	//////////////////
	// type

	template <typename T>
	struct type
	{
		enum type_enum
		{
			is_float = is_float<T>::YES,
			is_int = is_int<T>::YES,
			is_uint = is_uint<T>::YES,
			is_bool = is_bool<T>::YES
		};
	};

	//////////////////
	// type

	typedef signed char							int8;
	typedef signed short						int16;
	typedef signed int							int32;
	typedef detail::sint64						int64;

	typedef unsigned char						uint8;
	typedef unsigned short						uint16;
	typedef unsigned int						uint32;
	typedef detail::uint64						uint64;

	typedef detail::thalf						float16;
	typedef float								float32;
	typedef double								float64;

}//namespace detail
}//namespace glm

#endif//glm_core_detail
