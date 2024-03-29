///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-22
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_tvec4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype4
#define glm_core_type_gentype4

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"
#include "_detail.hpp"

namespace glm
{
	namespace test
	{
		void main_vec4();
	}//namespace test

	namespace detail
	{
		template <typename T> struct tref2;
		template <typename T> struct tref3;
		template <typename T> struct tref4;
		template <typename T> struct tvec2;
		template <typename T> struct tvec3;

		template <typename T>
		struct tvec4
		{
			enum ctor{null};
			typedef T value_type;
			typedef std::size_t size_type;
			static size_type value_size();

			typedef tvec4<T> type;
			typedef tvec4<bool> bool_type;

			//////////////////////////////////////
			// Data

#	if defined(GLM_USE_ONLY_XYZW)
			value_type x, y, z, w;
#	else//GLM_USE_ONLY_XYZW
#		ifdef GLM_USE_ANONYMOUS_UNION
			union 
			{
				struct{value_type x, y, z, w;};
				struct{value_type r, g, b, a;};
				struct{value_type s, t, p, q;};
			};
#		else//GLM_USE_ANONYMOUS_UNION
			union {value_type x, r, s;};
			union {value_type y, g, t;};
			union {value_type z, b, p;};
			union {value_type w, a, q;};
#		endif//GLM_USE_ANONYMOUS_UNION
#	endif//GLM_USE_ONLY_XYZW

			//////////////////////////////////////
			// Accesses

			value_type & operator[](size_type i);
			value_type const & operator[](size_type i) const;

			//////////////////////////////////////
			// Implicit basic constructors

			tvec4();
			tvec4(type const & v);

			//////////////////////////////////////
			// Explicit basic constructors

			explicit tvec4(
				ctor);
			explicit tvec4(
				value_type const & s);
			explicit tvec4(
				value_type const & s0, 
				value_type const & s1, 
				value_type const & s2, 
				value_type const & s3);

			//////////////////////////////////////
			// Swizzle constructors

			tvec4(tref4<T> const & r);

			//////////////////////////////////////
			// Convertion scalar constructors

			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec4(
				U const & x);
			//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C, typename D> 
			explicit tvec4(
				A const & x, 
				B const & y, 
				C const & z, 
				D const & w);			

			//////////////////////////////////////
			// Convertion vector constructors

			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(tvec2<A> const & v, B const & s1, C const & s2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(A const & s1, tvec2<B> const & v, C const & s2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B, typename C> 
			explicit tvec4(A const & s1, B const & s2, tvec2<C> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(tvec3<A> const & v, B const & s);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(A const & s, tvec3<B> const & v);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename A, typename B> 
			explicit tvec4(tvec2<A> const & v1, tvec2<B> const & v2);
			//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
			template <typename U> 
			explicit tvec4(tvec4<U> const & v);

			//////////////////////////////////////
			// Unary arithmetic operators

			tvec4<T> & operator= (tvec4<T> const & v);

			tvec4<T> & operator+=(value_type const & s);
			tvec4<T> & operator+=(type const & v);
			tvec4<T> & operator-=(value_type const & s);
			tvec4<T> & operator-=(type const & v);
			tvec4<T> & operator*=(value_type const & s);
			tvec4<T> & operator*=(type const & v);
			tvec4<T> & operator/=(value_type const & s);
			tvec4<T> & operator/=(type const & v);
			tvec4<T> & operator++();
			tvec4<T> & operator--();

			//////////////////////////////////////
			// Unary bit operators

			tvec4<T> & operator%= (value_type const & s);
			tvec4<T> & operator%= (type const & v);
			tvec4<T> & operator&= (value_type const & s);
			tvec4<T> & operator&= (type const & v);
			tvec4<T> & operator|= (value_type const & s);
			tvec4<T> & operator|= (type const & v);
			tvec4<T> & operator^= (value_type const & s);
			tvec4<T> & operator^= (type const & v);
			tvec4<T> & operator<<=(value_type const & s);
			tvec4<T> & operator<<=(type const & v);
			tvec4<T> & operator>>=(value_type const & s);
			tvec4<T> & operator>>=(type const & v);

			//////////////////////////////////////
			// Swizzle operators

			value_type swizzle(comp X) const;
			tvec2<T> swizzle(comp X, comp Y) const;
			tvec3<T> swizzle(comp X, comp Y, comp Z) const;
			tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
			tref4<T> swizzle(comp X, comp Y, comp Z, comp W);
		};

		template <typename T>
		struct tref4
		{
			tref4(T & x, T & y, T & z, T & w);
			tref4(tref4<T> const & r);
			tref4(tvec4<T> const & v);

			tref4<T> & operator= (tref4<T> const & r);
			tref4<T> & operator= (tvec4<T> const & v);

			T & x;
			T & y;
			T & z;
			T & w;
		};
	} //namespace detail

	namespace core{
	namespace type{

	//////////////////////////
	// Float definition

	namespace precision
	{
		//! 4 components vector of high precision floating-point numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		typedef detail::tvec4<highp_float>		highp_vec4;
		//! 4 components vector of medium precision floating-point numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		typedef detail::tvec4<mediump_float>	mediump_vec4;
		//! 4 components vector of low precision floating-point numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.5.2 Precision Qualifiers.
		typedef detail::tvec4<lowp_float>		lowp_vec4;

		//! 4 components vector of high precision signed integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<highp_int>		highp_ivec4;
		//! 4 components vector of medium precision signed integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<mediump_int>		mediump_ivec4;
		//! 4 components vector of low precision signed integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<lowp_int>			lowp_ivec4;

		//! 4 components vector of high precision unsigned integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<highp_uint>		highp_uvec4;
		//! 4 components vector of medium precision unsigned integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<mediump_uint>		mediump_uvec4;
		//! 4 components vector of low precision unsigned integer numbers. 
		//! There is no garanty on the actual precision.
		//! From GLSL 1.30.8 specification, section 4.1.5 Precision Qualifiers.
		typedef detail::tvec4<lowp_uint>		lowp_uvec4;
	}
	//namespace precision

	}//namespace type
	}//namespace core

	using namespace core::type;

}//namespace glm

#include "type_vec4.inl"

#endif//glm_core_type_gentype4
