///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-18
// Updated : 2010-10-26
// Licence : This source is under MIT License
// File    : glm/core/type_tvec2.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		template <typename T>
		inline typename tvec2<T>::size_type tvec2<T>::value_size()
		{
			return 2;
		}

		//////////////////////////////////////
		// Accesses

		template <typename T>
		inline typename tvec2<T>::value_type & 
		tvec2<T>::operator[]
		(
			size_type i
		)
		{
			assert(i >= size_type(0) && i < value_size());
			return (&x)[i];
		}

		template <typename T>
		inline typename tvec2<T>::value_type const & 
		tvec2<T>::operator[]
		(
			size_type i
		) const
		{
			assert(i >= size_type(0) && i < value_size());
			return (&x)[i];
		}

		//////////////////////////////////////
		// Implicit basic constructors

		template <typename T>
		inline tvec2<T>::tvec2() :
			x(value_type(0)),
			y(value_type(0))
		{}

		template <typename T>
		inline tvec2<T>::tvec2
		(
			ctor
		)
		{}

		template <typename T>
		inline tvec2<T>::tvec2
		(
			tvec2<T> const & v
		) :
			x(v.x),
			y(v.y)
		{}

		//////////////////////////////////////
		// Explicit basic constructors

		template <typename T>
		inline tvec2<T>::tvec2
		(
			value_type const & s
		) :
			x(s),
			y(s)
		{}

		template <typename T>
		inline tvec2<T>::tvec2
		(
			value_type const & s1, 
			value_type const & s2
		) :
			x(s1),
			y(s2)
		{}

		//////////////////////////////////////
		// Swizzle constructors

		template <typename T>
		inline tvec2<T>::tvec2
		(
			tref2<T> const & r
		) :
			x(r.x),
			y(r.y)
		{}

		//////////////////////////////////////
		// Convertion scalar constructors
		
		template <typename T>
		template <typename U> 
		inline tvec2<T>::tvec2
		(
			U const & x
		) :
			x(value_type(x)),
			y(value_type(x))
		{}

		template <typename T>
		template <typename U, typename V> 
		inline tvec2<T>::tvec2
		(
			U const & x, 
			V const & y
		) :
			x(value_type(x)),
			y(value_type(y))
		{}

		//////////////////////////////////////
		// Convertion vector constructors

		template <typename T>
		template <typename U> 
		inline tvec2<T>::tvec2
		(
			tvec2<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y))
		{}

		template <typename T>
		template <typename U> 
		inline tvec2<T>::tvec2
		(
			tvec3<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y))
		{}

		template <typename T>
		template <typename U> 
		inline tvec2<T>::tvec2
		(
			tvec4<U> const & v
		) :
			x(value_type(v.x)),
			y(value_type(v.y))
		{}

		//////////////////////////////////////
		// Unary arithmetic operators

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator= 
		(
			tvec2<T> const & v
		)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator+=
		(
			value_type const & s
		)
		{
			this->x += s;
			this->y += s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator+=
		(
			tvec2<T> const & v
		)
		{
			this->x += v.x;
			this->y += v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator-=
		(
			value_type const & s
		)
		{
			this->x -= s;
			this->y -= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator-=
		(
			tvec2<T> const & v
		)
		{
			this->x -= v.x;
			this->y -= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator*=
		(
			value_type const & s
		)
		{
			this->x *= s;
			this->y *= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator*=
		(
			tvec2<T> const & v
		)
		{
			this->x *= v.x;
			this->y *= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator/=
		(
			value_type const & s
		)
		{
			this->x /= s;
			this->y /= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator/=
		(
			tvec2<T> const & v
		)
		{
			this->x /= v.x;
			this->y /= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator++()
		{
			++this->x;
			++this->y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator--()
		{
			--this->x;
			--this->y;
			return *this;
		}

		//////////////////////////////////////
		// Unary bit operators

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator%=
		(
			value_type const & s
		)
		{
			this->x %= s;
			this->y %= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator%=
		(
			tvec2<T> const & v
		)
		{
			this->x %= v.x;
			this->y %= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator&=
		(
			value_type const & s
		)
		{
			this->x &= s;
			this->y &= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator&=
		(
			tvec2<T> const & v
		)
		{
			this->x &= v.x;
			this->y &= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator|=
		(
			value_type const & s
		)
		{
			this->x |= s;
			this->y |= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator|=
		(
			tvec2<T> const & v
		)
		{
			this->x |= v.x;
			this->y |= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator^=
		(
			value_type const & s
		)
		{
			this->x ^= s;
			this->y ^= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator^=
		(
			tvec2<T> const & v
		)
		{
			this->x ^= v.x;
			this->y ^= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator<<=
		(
			value_type const & s
		)
		{
			this->x <<= s;
			this->y <<= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator<<=
		(
			tvec2<T> const & v
		)
		{
			this->x <<= v.x;
			this->y <<= v.y;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator>>=
		(
			value_type const & s
		)
		{
			this->x >>= s;
			this->y >>= s;
			return *this;
		}

		template <typename T>
		inline tvec2<T> & tvec2<T>::operator>>=
		(
			tvec2<T> const & v
		)
		{
			this->x >>= v.x;
			this->y >>= v.y;
			return *this;
		}

		//////////////////////////////////////
		// Swizzle operators

		template <typename T>
		inline typename tvec2<T>::value_type tvec2<T>::swizzle
		(
			comp x
		) const
		{
			return (*this)[x];
		}

		template <typename T>
		inline tvec2<T> tvec2<T>::swizzle
		(
			comp x, 
			comp y
		) const
		{
			return tvec2<T>(
				(*this)[x],
				(*this)[y]);
		}

		template <typename T>
		inline tvec3<T> tvec2<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z
		) const
		{
			return tvec3<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z]);
		}

		template <typename T>
		inline tvec4<T> tvec2<T>::swizzle
		(
			comp x, 
			comp y, 
			comp z, 
			comp w
		) const
		{
			return tvec4<T>(
				(*this)[x],
				(*this)[y],
				(*this)[z],
				(*this)[w]);
		}

		template <typename T>
		inline tref2<T> tvec2<T>::swizzle
		(
			comp x, 
			comp y
		)
		{
			return tref2<T>(
				(*this)[x],
				(*this)[y]);
		}

		//////////////////////////////////////
		// Binary arithmetic operators

		template <typename T> 
		inline tvec2<T> operator+ 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x + s,
				v.y + s);
		}

		template <typename T> 
		inline tvec2<T> operator+ 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s + v.x,
				s + v.y);
		}

		template <typename T> 
		inline tvec2<T> operator+ 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x + v2.x,
				v1.y + v2.y);
		}

		//operator-
		template <typename T> 
		inline tvec2<T> operator-
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x - s,
				v.y - s);
		}

		template <typename T> 
		inline tvec2<T> operator- 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s - v.x,
				s - v.y);
		}

		template <typename T> 
		inline tvec2<T> operator- 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x - v2.x,
				v1.y - v2.y);
		}

		//operator*
		template <typename T> 
		inline tvec2<T> operator* 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x * s,
				v.y * s);
		}

		template <typename T> 
		inline tvec2<T> operator* 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s * v.x,
				s * v.y);
		}

		template <typename T> 
		inline tvec2<T> operator*
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x * v2.x,
				v1.y * v2.y);
		}

		//operator/
		template <typename T> 
		inline tvec2<T> operator/
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x / s,
				v.y / s);
		}

		template <typename T> 
		inline tvec2<T> operator/
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s / v.x,
				s / v.y);
		}

		template <typename T> 
		inline tvec2<T> operator/ 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x / v2.x,
				v1.y / v2.y);
		}

		// Unary constant operators
		template <typename T> 
		inline tvec2<T> operator- 
		(
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				-v.x, 
				-v.y);
		}

		template <typename T> 
		inline tvec2<T> operator++ 
		(
			tvec2<T> const & v, 
			int
		)
		{
			return tvec2<T>(
				v.x + T(1), 
				v.y + T(1));
		}

		template <typename T> 
		inline tvec2<T> operator-- 
		(
			tvec2<T> const & v, 
			int
		)
		{
			return tvec2<T>(
				v.x - T(1), 
				v.y - T(1));
		}

		//////////////////////////////////////
		// Binary bit operators

		template <typename T>
		inline tvec2<T> operator% 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x % s,
				v.y % s);
		}

		template <typename T>
		inline tvec2<T> operator%
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s % v.x,
				s % v.y);
		}

		template <typename T>
		inline tvec2<T> operator% 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x % v2.x,
				v1.y % v2.y);
		}

		template <typename T>
		inline tvec2<T> operator& 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x & s,
				v.y & s);
		}

		template <typename T>
		inline tvec2<T> operator& 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s & v.x,
				s & v.y);
		}

		template <typename T>
		inline tvec2<T> operator& 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x & v2.x,
				v1.y & v2.y);
		}

		template <typename T>
		inline tvec2<T> operator| 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x | s,
				v.y | s);
		}

		template <typename T>
		inline tvec2<T> operator| 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s | v.x,
				s | v.y);
		}

		template <typename T>
		inline tvec2<T> operator| 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x | v2.x,
				v1.y | v2.y);
		}
		
		template <typename T>
		inline tvec2<T> operator^ 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x ^ s,
				v.y ^ s);
		}

		template <typename T>
		inline tvec2<T> operator^ 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s ^ v.x,
				s ^ v.y);
		}

		template <typename T>
		inline tvec2<T> operator^ 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x ^ v2.x,
				v1.y ^ v2.y);
		}

		template <typename T>
		inline tvec2<T> operator<< 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x << s,
				v.y << s);
		}

		template <typename T>
		inline tvec2<T> operator<< 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s << v.x,
				s << v.y);
		}

		template <typename T>
		inline tvec2<T> operator<< 
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x << v2.x,
				v1.y << v2.y);
		}

		template <typename T>
		inline tvec2<T> operator>> 
		(
			tvec2<T> const & v, 
			typename tvec2<T>::value_type const & s
		)
		{
			return tvec2<T>(
				v.x >> s,
				v.y >> s);
		}

		template <typename T>
		inline tvec2<T> operator>> 
		(
			typename tvec2<T>::value_type const & s, 
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				s >> v.x,
				s >> v.y);
		}

		template <typename T>
		inline tvec2<T> operator>>
		(
			tvec2<T> const & v1, 
			tvec2<T> const & v2
		)
		{
			return tvec2<T>(
				v1.x >> v2.x,
				v1.y >> v2.y);
		}

		template <typename T> 
		inline tvec2<T> operator~ 
		(
			tvec2<T> const & v
		)
		{
			return tvec2<T>(
				~v.x,
				~v.y);
		}

		//////////////////////////////////////
		// tref definition

		template <typename T> 
		tref2<T>::tref2
		(
			T & x, 
			T & y
		) :
			x(x),
			y(y)
		{}

		template <typename T> 
		tref2<T>::tref2
		(
			tref2<T> const & r
		) :
			x(r.x),
			y(r.y)
		{}

		template <typename T> 
		tref2<T>::tref2
		(
			tvec2<T> const & v
		) :
			x(v.x),
			y(v.y)
		{}

		template <typename T> 
		tref2<T>& tref2<T>::operator= 
		(
			tref2<T> const & r
		)
		{
			x = r.x;
			y = r.y;
			return *this;
		}

		template <typename T> 
		tref2<T>& tref2<T>::operator= 
		(
			tvec2<T> const & v
		)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

	}//namespace detail
}//namespace glm
