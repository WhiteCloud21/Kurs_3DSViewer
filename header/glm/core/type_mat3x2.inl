///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-01-05
// Licence : This source is under MIT License
// File    : glm/core/type_mat3x2.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	inline typename tmat3x2<T>::size_type tmat3x2<T>::col_size()
	{
		return 2;
	}

	template <typename T>
	inline typename tmat3x2<T>::size_type tmat3x2<T>::row_size()
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	inline typename tmat3x2<T>::col_type &
	tmat3x2<T>::operator[]
	(
		size_type i
	)
	{
		assert(i >= size_type(0) && i < col_size());
		return this->value[i];
	}

	template <typename T>
	inline typename tmat3x2<T>::col_type const & 
	tmat3x2<T>::operator[]
	(
		size_type i
	) const
	{
		assert(i >= size_type(0) && i < col_size());
		return this->value[i];
	}

    //////////////////////////////////////////////////////////////
    // Constructors

    template <typename T> 
    inline tmat3x2<T>::tmat3x2()
    {
        this->value[0] = col_type(1, 0);
        this->value[1] = col_type(0, 1);
        this->value[2] = col_type(0, 0);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		value_type const & s
	)
    {
        this->value[0] = col_type(s, 0);
        this->value[1] = col_type(0, s);
        this->value[2] = col_type(0, 0);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
    (
        value_type const & x0, value_type const & y0,
        value_type const & x1, value_type const & y1,
        value_type const & x2, value_type const & y2
    )
    {
        this->value[0] = col_type(x0, y0);
        this->value[1] = col_type(x1, y1);
        this->value[2] = col_type(x2, y2);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
    (
        col_type const & v0, 
        col_type const & v1, 
        col_type const & v2
    )
    {
        this->value[0] = v0;
        this->value[1] = v1;
        this->value[2] = v2;
    }

    // Conversion
    template <typename T> 
    template <typename U> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat3x2<U> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
	}

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat2x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = col_type(T(0));
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat3x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat4x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat2x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(T(0));
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat2x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(T(0));
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat3x4<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat4x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
    }

    template <typename T> 
    inline tmat3x2<T>::tmat3x2
	(
		tmat4x3<T> const & m
	)
    {
        this->value[0] = col_type(m[0]);
        this->value[1] = col_type(m[1]);
        this->value[2] = col_type(m[2]);
    }

    //////////////////////////////////////////////////////////////
    // Unary updatable operators

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator= 
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator+= 
	(
		value_type const & s
	)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator+= 
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator-= 
	(
		value_type const & s
	)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator-= 
	(
		tmat3x2<T> const & m
	)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator*= 
	(
		value_type const & s
	)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator*= 
	(
		tmat3x2<T> const & m
	)
    {
        return (*this = tmat3x2<T>(*this * m));
    }

    template <typename T> 
    inline tmat3x2<T> & tmat3x2<T>::operator/= 
	(
		value_type const & s
	)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator++ ()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

    template <typename T> 
    inline tmat3x2<T>& tmat3x2<T>::operator-- ()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

    //////////////////////////////////////////////////////////////
    // Binary operators

    template <typename T> 
    inline tmat3x2<T> operator+ 
	(
		tmat3x2<T> const & m, 
		typename tmat3x2<T>::value_type const & s
	)
    {
        return tmat3x2<T>(
            m[0] + s,
            m[1] + s,
            m[2] + s);
    }

    template <typename T> 
    inline tmat3x2<T> operator+ 
	(
		tmat3x2<T> const & m1, 
		tmat3x2<T> const & m2
	)
    {
        return tmat3x2<T>(
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2]);
    }

    template <typename T> 
    inline tmat3x2<T> operator- 
	(
		tmat3x2<T> const & m, 
		typename tmat3x2<T>::value_type const & s
	)
    {
        return tmat3x4<T>(
            m[0] - s,
            m[1] - s,
            m[2] - s);
    }

    template <typename T> 
    inline tmat3x2<T> operator- 
	(	
		tmat3x2<T> const & m1, 
		tmat3x2<T> const & m2
	)
    {
        return tmat3x2<T>(
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2]);
    }

    template <typename T> 
    inline tmat3x2<T> operator* 
	(
		tmat3x2<T> const & m, 
		typename tmat3x2<T>::value_type const & s
	)
    {
        return tmat3x2<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }

    template <typename T> 
    inline tmat3x2<T> operator* 
	(
		typename tmat3x2<T>::value_type const & s, 
		const tmat3x2<T> & m
	)
    {
        return tmat3x2<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s);
    }
   
    template <typename T>
    inline detail::tvec2<T> operator* 
	(
		tmat3x2<T> const & m, 
		detail::tvec3<T> const & v
	)
    {
        return detail::tvec2<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z);
    }

    template <typename T> 
    inline detail::tvec3<T> operator* 
	(
		detail::tvec2<T> const & v, 
		tmat3x2<T> const & m
	)
    {
        return detail::tvec3<T>(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w);
    }

    template <typename T> 
    inline tmat2x2<T> operator* 
	(
		tmat3x2<T> const & m1, 
		tmat2x3<T> const & m2
	)
    {
        const T SrcA00 = m1[0][0];
        const T SrcA01 = m1[0][1];
        const T SrcA10 = m1[1][0];
        const T SrcA11 = m1[1][1];
        const T SrcA20 = m1[2][0];
        const T SrcA21 = m1[2][1];

        const T SrcB00 = m2[0][0];
        const T SrcB01 = m2[0][1];
        const T SrcB02 = m2[0][2];
        const T SrcB10 = m2[1][0];
        const T SrcB11 = m2[1][1];
        const T SrcB12 = m2[1][2];

        tmat2x2<T> Result(tmat2x2<T>::null);
        Result[0][0] = SrcA00 * SrcB00 + SrcA01 * SrcB01 + SrcA20 * SrcB02;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
        return Result;
    }

    template <typename T> 
    inline tmat3x2<T> operator/ 
	(
		tmat3x2<T> const & m, 
		typename tmat3x2<T>::value_type const & s
	)
    {
        return tmat3x2<T>(
            m[0] / s,
            m[1] / s,
            m[2] / s,
            m[3] / s);        
    }

    template <typename T> 
    inline tmat3x2<T> operator/ 
	(
		typename tmat3x2<T>::value_type const & s, 
		tmat3x2<T> const & m
	)
    {
        return tmat3x2<T>(
            s / m[0],
            s / m[1],
            s / m[2],
            s / m[3]);        
    }

	// Unary constant operators
    template <typename T> 
    inline tmat3x2<T> const operator- 
	(
		tmat3x2<T> const & m
	)
    {
        return tmat3x2<T>(
            -m[0], 
            -m[1],
            -m[2]);
    }

    template <typename T> 
    inline tmat3x2<T> const operator++ 
	(
		tmat3x2<T> const & m, 
		int
	) 
    {
		typename tmat3x2<T>::value_type One(1);
        return tmat3x2<T>(
            m[0] + One,
            m[1] + One,
            m[2] + One);
    }

    template <typename T> 
    inline tmat3x2<T> const operator-- 
	(
		tmat3x2<T> const & m, 
		int
	) 
    {
		typename tmat3x2<T>::value_type One(1);
        return tmat3x2<T>(
            m[0] - One,
            m[1] - One,
            m[2] - One);
    }

} //namespace detail
} //namespace glm
