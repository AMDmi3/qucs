/*
 * complex.cpp - complex number class implementation
 *
 * Copyright (C) 2003, 2004, 2005, 2006, 2007 Stefan Jahn <stefan@lkcc.org>
 * Copyright (C) 2006 Gunther Kraut <gn.kraut@t-online.de>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * $Id$
 *
 */

/*!\file complex.cpp

   Implements complex number class and functions
*/

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <cmath>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "precision.h"
#include "complex.h"
#include "complex_missing_std.h"
#include "consts.h"
#include "fspecial.h"


#ifndef HAVE_CXX_COMPLEX_ASIN
namespace std
{
/*! \brief Compute complex arc sinus
    \param[in] z complex arc
    \return arc sinus of z
*/
nr_complex_t asin (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
    return nr_complex_t (0.0, -1.0) * log (nr_complex_t (-i, r) + sqrt (1.0 - z * z));
}
}
#endif

#ifndef HAVE_CXX_COMPLEX_ASINH
namespace std
{
/*! \brief Compute complex argument hyperbolic sinus
    \param[in] z complex arc
    \return argument hyperbolic sinus of z
*/
nr_complex_t asinh (const nr_complex_t z)
{
    return log (z + sqrt (z * z + 1.0));
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_ACOS
namespace std
{
/*! \brief Compute complex arc cosinus
    \param[in] z complex arc
    \return arc cosinus of z
*/
nr_complex_t acos (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
#if 0
    return nr_complex_t (0.0, -2.0) * log (M_SQRT1_2 * (sqrt (z + 1) + sqrt (z - 1)));
#else
    nr_complex_t y = sqrt (z * z - 1.0);
    if (r * i < 0.0) y = -y;
    return nr_complex_t (0, -1.0) * log (z + y);
#endif
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_ACOSH
namespace std
{
/*! \brief Compute complex argument hyperbolic cosinus
    \param[in] z complex arc
    \return argument hyperbolic cosinus of z
*/
nr_complex_t acosh (const nr_complex_t z)
{
    return log (z + sqrt (z * z - 1.0));
}
}
#endif

#ifndef HAVE_CXX_COMPLEX_ATAN
namespace std
{
/*! \brief Compute complex arc tangent
    \param[in] z complex arc
    \return arc tangent of z
*/
nr_complex_t atan (const nr_complex_t z)
{
    return nr_complex_t (0.0, -0.5) * log (nr_complex_t (0, 2) / (z + nr_complex_t (0, 1)) - 1.0);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_ATANH
namespace std
{
/*! \brief Compute complex argument hyperbolic tangent
    \param[in] z complex arc
    \return argument hyperbolic tangent of z
*/
nr_complex_t atanh (const nr_complex_t z)
{
    return 0.5 * log ( 2.0 / (1.0 - z) - 1.0);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_SIN
namespace std
{
/*! \brief Compute complex sinus
    \param[in] z complex angle
    \return sinus of z
*/
nr_complex_t sin (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
    return (std::polar (exp (-i), r - M_PI_2) - std::polar (exp (i), -r - M_PI_2)) / 2.0;
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_SINH
namespace std
{
/*! \brief Compute complex hyperbolic sinus
    \param[in] z complex angle
    \return hyperbolic sinus of z
*/
nr_complex_t sinh (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
    return (std::polar (exp (r), i) - std::polar (exp (-r), -i)) / 2.0;
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_COS
namespace std
{
/*! \brief Compute complex cosinus
    \param[in] z complex angle
    \return cosinus of z
*/
nr_complex_t cos (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
    return (std::polar (exp (-i), r) + std::polar (exp (i), -r)) / 2.0;
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_COSH
namespace std
{
/*! \brief Compute complex hyperbolic cosinus
    \param[in] z complex angle
    \return hyperbolic cosinus of z
*/
nr_complex_t cosh (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
    return (std::polar (exp (r), i) + std::polar (exp (-r), -i)) / 2.0;
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_TAN
namespace std
{
/*!\brief Compute complex tangent
\param[in] z complex angle
\return tangent of z
*/
nr_complex_t tan (const nr_complex_t z)
{
    nr_double_t r = 2.0 * real (z);
    nr_double_t i = 2.0 * imag (z);
    return nr_complex_t (0.0, -1.0) + nr_complex_t (0.0, 2.0) / (std::polar (exp (-i), r) + 1.0);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_TANH
namespace std
{
/*! \brief Compute complex hyperbolic tangent
    \param[in] z complex angle
    \return hyperbolic tangent of z
*/
nr_complex_t tanh (const nr_complex_t z)
{
    nr_double_t r = 2.0 * real (z);
    nr_double_t i = 2.0 * imag (z);
    return 1.0 - 2.0 / (std::polar (exp (r), i) + 1.0);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_EXP
namespace std
{
/*! \brief Compute complex exponential
    \param[in] z complex number
    \return exponential of z
*/
nr_complex_t exp (const nr_complex_t z)
{
    nr_double_t mag = exp (real (z));
    return nr_complex_t (mag * cos (imag (z)), mag * sin (imag (z)));
}
}
#endif

#ifndef HAVE_CXX_COMPLEX_LOG
namespace std
{
/*! \brief Compute principal value of natural logarithm of z
    \param[in] z complex number
    \return principal value of natural logarithm of z
*/
nr_complex_t log (const nr_complex_t z)
{
    nr_double_t phi = arg (z);
    return nr_complex_t (log (abs (z)), phi);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_LOG10
namespace std
{
/*!\brief Compute principal value of decimal logarithm of z
\param[in] z complex number
\return principal value of decimal logarithm of z
*/
nr_complex_t log10 (const nr_complex_t z)
{
    nr_double_t phi = arg (z);
    return nr_complex_t (log10 (abs (z)), phi * M_LOG10E);
}
}
#endif


#ifndef HAVE_CXX_COMPLEX_SQRT
namespace std
{
/*! \brief Compute principal value of square root

    Compute the square root of a given complex number (except negative
    real), and with a branch cut along the negative real axis.
    \param[in] z complex number
    \return principal value of square root z
*/
nr_complex_t sqrt (const nr_complex_t z)
{
    nr_double_t r = real (z);
    nr_double_t i = imag (z);
#if 0
    if (i == 0.0)
    {
        return r < 0.0 ? nr_complex_t (0.0, sqrt (-r)) : nr_complex_t (sqrt (r));
    }
    else
    {
        nr_double_t phi = arg (z);
        return std::polar (sqrt (fabs (z)), phi / 2.0);
    }
#else /* better numerical behaviour, avoiding arg() and polar() */
    if (r == 0.0 && i == 0.0)
    {
        return nr_complex_t (0.0, 0.0);
    }
    else
    {
        nr_double_t x = fabs (r);
        nr_double_t y = fabs (i);
        nr_double_t k;
        if (x >= y)
        {
            nr_double_t t = y / x;
            k = sqrt (x) * sqrt (0.5 * (1.0 + sqrt (1.0 + t * t)));
        }
        else
        {
            nr_double_t t = x / y;
            k = sqrt (y) * sqrt (0.5 * (t + sqrt (1.0 + t * t)));
        }
        if (r >= 0.0)
        {
            return nr_complex_t (k, i / (2.0 * k));
        }
        else
        {
            nr_double_t vi = (i >= 0) ? k : -k;
            return nr_complex_t (i / (2.0 * vi), vi);
        }
    }
#endif
}
}
#endif


using namespace fspecial;

namespace qucs
{

/*!\brief Compute complex arc sine

   \param[in] z complex arc
   \return arc sine of z
*/
nr_complex_t asin (const nr_complex_t z)
{
    return std::asin (z);
}


/*!\brief Compute complex argument hyperbolic sine

   \param[in] z complex arc
   \return argument hyperbolic sine of z
*/
nr_complex_t asinh (const nr_complex_t z)
{
    return std::asinh (z);
}


/*!\brief Compute complex arc cosine

   \param[in] z complex arc
   \return arc cosine of z
*/
nr_complex_t acos (const nr_complex_t z)
{
    return std::acos (z);
}

/*!\brief Compute complex argument hyperbolic cosine

   \param[in] z complex arc
   \return argument hyperbolic cosine of z
*/
nr_complex_t acosh (const nr_complex_t z)
{
    return std::acosh (z);
}


/*!\brief Compute complex arc tangent

   \param[in] z complex arc
   \return arc tangent of z
*/
nr_complex_t atan (const nr_complex_t z)
{
    return std::atan (z);
}


/*!\brief Compute complex argument hyperbolic tangent

   \param[in] z complex arc
   \return argument hyperbolic tangent of z
*/
nr_complex_t atanh (const nr_complex_t z)
{
    return std::atanh (z);
}

/*!\brief Compute complex sine

   \param[in] z complex angle
   \return sine of z
*/
nr_complex_t sin (const nr_complex_t z)
{
    return std::sin (z);
}

/*!\brief Compute complex hyperbolic sine

   \param[in] z complex angle
   \return hyperbolic sine of z
*/
nr_complex_t sinh (const nr_complex_t z)
{
    return std::sinh (z);
}

/*!\brief Compute complex cosine

   \param[in] z complex angle
   \return cosine of z
*/
nr_complex_t cos (const nr_complex_t z)
{
    return std::cos (z);
}


/*!\brief Compute complex hyperbolic cosine

   \param[in] z complex angle
   \return hyperbolic cosine of z
*/
nr_complex_t cosh (const nr_complex_t z)
{
    return std::cosh (z);
}


/*!\brief Compute complex tangent

   \param[in] z complex angle
   \return tangent of z
*/
nr_complex_t tan (const nr_complex_t z)
{
    return std::tan (z);
}


/*!\brief Compute complex hyperbolic tangent

   \param[in] z complex angle
   \return hyperbolic tangent of z
*/
nr_complex_t tanh (const nr_complex_t z)
{
    return std:: tanh (z);
}

/*!\brief Compute complex exponential

   \param[in] z complex number
   \return exponential of z
*/
nr_complex_t exp (const nr_complex_t z)
{
    return std::exp (z);
}


/*!\brief Compute principal value of natural logarithm of z

   \param[in] z complex number
   \return principal value of natural logarithm of z
*/
nr_complex_t log (const nr_complex_t z)
{
    return std::log (z);
}

/*!\brief Compute principal value of decimal logarithm of z

   \param[in] z complex number
   \return principal value of decimal logarithm of z
*/
nr_complex_t log10 (const nr_complex_t z)
{
    return std::log10 (z);
}

/*!\brief Compute euclidian norm of complex number

   Compute \f$(\Re\mathrm{e}\;z )^2+ (\Im\mathrm{m}\;z)^2=|z|^2\f$
   \param[in] z Complex number
   \return Euclidian norm of z
*/
nr_double_t norm (const nr_complex_t z)
{
    return std::norm (z);
}


/*!\brief Construct a complex number using polar notation
   \param[in] mag Magnitude
   \param[in] ang Angle
   \return complex number in rectangular form
*/
nr_complex_t polar (const nr_double_t mag, const nr_double_t ang)
{
    return std::polar (mag, ang);
}


/*!\brief Compute power function with real exponent

   \param[in] z complex mantisse
   \param[in] d real exponent
   \return z power d (\f$z^d\f$)
*/
nr_complex_t pow (const nr_complex_t z, const nr_double_t d)
{
    return std::pow (z, d);
}

/*!\brief Compute power function with complex exponent but real mantisse

   \param[in] d real mantisse
   \param[in] z complex exponent
   \return d power z (\f$d^z\f$)
*/
nr_complex_t pow (const nr_double_t d, const nr_complex_t z)
{
    return std::pow (d, z);
}

/*!\brief Compute complex power function

   \param[in] z1 complex mantisse
   \param[in] z2 complex exponent
   \return d power z (\f$z_1^{z_2}\f$)
*/
nr_complex_t pow (const nr_complex_t z1, const nr_complex_t z2)
{
    return std::pow (z1, z2);
}

/*!\brief Compute principal value of square root

    Compute the square root of a given complex number (except negative
    real), and with a branch cut along the negative real  axis.

   \param[in] z complex number
   \return principal value of square root z
*/
nr_complex_t sqrt (const nr_complex_t z)
{
    return std::sqrt (z);
}


/*!\brief Extension of polar construction to complex
   \param[in] a Magnitude
   \param[in] p Angle
   \return complex number in rectangular form
   \bug Do not seems holomorph form of real polar
   \todo Move near real polar
*/
nr_complex_t polar (const nr_complex_t a, const nr_complex_t p)
{
#ifndef HAVE_CXX_COMPLEX_POLAR_COMPLEX
    return a * exp (nr_complex_t (imag (p),-real (p)));
#else
    return std::polar (a, p);
#endif
}

nr_complex_t round (const nr_complex_t z)
{
    nr_double_t zreal = real (z);
    nr_double_t zimag = imag (z);
#ifndef HAVE_ROUND
    zreal = qucs::round (zreal);
    zimag = qucs::round (zimag);
#else
    zreal = std::round (zreal);
    zimag = std::round (zimag);
#endif
    return nr_complex_t (zreal, zimag);
}

nr_complex_t trunc (const nr_complex_t z)
{
    nr_double_t zreal = real (z);
    nr_double_t zimag = imag (z);
#ifdef HAVE_TRUNC
    zreal = std::trunc (zreal);
    zimag = std::trunc (zimag);
#else
    zreal = qucs::trunc (zreal);
    zimag = qucs::trunc (zimag);
#endif
    return nr_complex_t (zreal, zimag);
}

/*!\brief Compute complex hyperbolic secant

   \param[in] z complex angle
   \return hyperbolic secant of z
*/
nr_complex_t sech (const nr_complex_t z)
{
    return (1.0 / std::cosh (z));
}


/*!\brief Compute complex argument hyperbolic cosec

   \param[in] z complex arc
   \return argument hyperbolic cosec of z
*/
nr_complex_t     cosech (const nr_complex_t z)
{
    return (1.0 / std::sinh(z));
}

nr_double_t dB (const nr_complex_t z)
{
    return 10.0 * std::log10 (std::norm (z));
}

/*!\brief Compute limited complex exponential

   \param[in] z complex number
   \return limited exponential of z
   \todo Change limexp(real) limexp(complex) file order
*/
nr_complex_t limexp (const nr_complex_t z)
{
    nr_double_t mag = limexp (real (z));
    return nr_complex_t (mag * cos (imag (z)), mag * sin (imag (z)));
}



/*!\brief Compute principal value of binary logarithm of z

   \param[in] z complex number
   \return principal value of binary logarithm of z
*/
nr_complex_t log2 (const nr_complex_t z)
{
#ifndef HAVE_CXX_COMPLEX_LOG2
    nr_double_t phi = std::arg (z);
    return nr_complex_t (std::log (std::abs (z)) * M_LOG2E, phi * M_LOG2E);
#else
    return std::log2 (z);
#endif
}



#ifndef HAVE_CXX_COMPLEX_ATAN2
/*!\brief Compute complex arc tangent fortran like function

   atan2 is a two-argument function that computes the arc tangent of y / x
   given y and x, but with a range of \f$(-\pi;\pi]\f$

   \param[in] z complex angle
   \return arc tangent of z
*/
nr_complex_t atan2 (const nr_complex_t y, const nr_complex_t x)
{
    nr_complex_t a = std::atan (y / x);
    return real (x) > 0.0 ? a : -a;
}
#endif


/*!\brief Compute complex cotangent

   \param[in] z complex angle
   \return cotangent of z
*/
nr_complex_t cot (const nr_complex_t z)
{
    nr_double_t r = 2.0 * std::real (z);
    nr_double_t i = 2.0 * std::imag (z);
    return nr_complex_t (0.0, 1.0) + nr_complex_t (0.0, 2.0) / (std::polar (std::exp (-i), r) - 1.0);
}

/*!\brief Compute complex arc cotangent

   \param[in] z complex arc
   \return arc cotangent of z
*/
nr_complex_t acot (const nr_complex_t z)
{
    return nr_complex_t (0.0, -0.5) * std::log (nr_complex_t (0, 2) / (z - nr_complex_t (0, 1)) + 1.0);
}

/*!\brief Compute complex argument hyperbolic secant

   \param[in] z complex arc
   \return argument hyperbolic secant of z
   \todo for symetry reason implement sech
*/
nr_complex_t asech (const nr_complex_t z)
{
    return std::log ((1.0 + std::sqrt (1.0 - z * z)) / z);
}

/*!\brief Compute complex hyperbolic cotangent

   \param[in] z complex angle
   \return hyperbolic cotangent of z
*/
nr_complex_t coth (const nr_complex_t z)
{
    nr_double_t r = 2.0 * std::real (z);
    nr_double_t i = 2.0 * std::imag (z);
    return 1.0 + 2.0 / (std::polar (std::exp (r), i) - 1.0);
}

/*!\brief Compute complex argument hyperbolic cotangent

   \param[in] z complex arc
   \return argument hyperbolic cotangent of z
*/
nr_complex_t acoth (const nr_complex_t z)
{
    return 0.5 * std::log (2.0 / (z - 1.0) + 1.0);
}


/*!\brief Converts impedance to reflexion coefficient

   \param[in] z impedance
   \param[in] zref normalisation impedance
   \return reflexion coefficient
*/
nr_complex_t ztor (const nr_complex_t z, nr_complex_t zref)
{
    return (z - zref) / (z + zref);
}

/*!\brief Converts admittance to reflexion coefficient
   \param[in] y admitance
   \param[in] zref normalisation impedance
   \return reflexion coefficient
*/
nr_complex_t ytor (const nr_complex_t y, nr_complex_t zref)
{
    return (1.0 - y * zref) / (1.0 + y * zref);
}

/*!\brief Converts reflexion coefficient to impedance
   \param[in] r reflexion coefficient
   \param[in] zref normalisation impedance
   \return impedance
*/
nr_complex_t rtoz (const nr_complex_t r, nr_complex_t zref)
{
    return zref * (1.0 + r) / (1.0 - r);
}

/*!\brief Converts reflexion coefficient to admittance
   \param[in] r reflexion coefficient
   \param[in] zref normalisation impedance
   \return admittance
*/
nr_complex_t rtoy (const nr_complex_t r, nr_complex_t zref)
{
    return (1.0 - r) / (1.0 + r) / zref;
}


/*!\brief complex signum function

    compute \f[
    \mathrm{signum}\;z= \mathrm{signum} (re^{i\theta})
                     = \begin{cases}
		       0 & \text{if } z=0 \\
		       e^{i\theta} & \text{else}
		       \end{cases}
	    \f]
   \param[in] z complex number
   \return signum of z
   \todo Better implementation z/abs(z) is not really stable
*/
nr_complex_t signum (const nr_complex_t z)
{
    if (z == 0) return 0;
    return z / abs (z);
}

/*!\brief complex sign function

    compute \f[
    \mathrm{sign}\;z= \mathrm{sign} (re^{i\theta})
                     = \begin{cases}
		       1 & \text{if } z=0 \\
		       e^{i\theta} & \text{else}
		       \end{cases}
	    \f]
   \param[in] z complex number
   \return sign of z
   \todo Better implementation z/abs(z) is not really stable
*/
nr_complex_t sign (const nr_complex_t z)
{
    if (z == 0) return nr_complex_t (1);
    return z / abs (z);
}

nr_complex_t    sinc (const nr_complex_t z)
{
    if (real(z) == 0 && imag(z)) return 1;
#ifndef HAVE_CXX_COMPLEX_SIN
    return std::sin (z) / z;
#else
    return std::sin (z) / z;
#endif
}

/*!\brief Euclidean distance function for complex argument

   The xhypot() function returns \f$\sqrt{a^2+b^2}\f$.
   This is the length of the hypotenuse of a right-angle triangle with sides
   of length a and b, or the distance
   of the point (a,b) from the origin.

   \param[in] a first length
   \param[in] b second length
   \return Euclidean distance from (0,0) to (a,b): \f$\sqrt{a^2+b^2}\f$
*/
nr_double_t xhypot (const nr_complex_t a, const nr_complex_t b)
{
    nr_double_t c = norm (a);
    nr_double_t d = norm (b);
    if (c > d)
        return abs (a) * std::sqrt (1 + d / c);
    else if (d == 0)
        return 0;
    else
        return abs (b) * std::sqrt (1 + c / d);
}

/*!\brief Euclidean distance function for a double b complex */
nr_double_t xhypot (nr_double_t a, nr_complex_t b)
{
    return xhypot (nr_complex_t (a), b);
}

/*!\brief Euclidean distance function for b double a complex */
nr_double_t xhypot (nr_complex_t a, nr_double_t b)
{
    return xhypot (a, nr_complex_t (b));
}


/*!\brief Heaviside step function for complex number

   Apply Heaviside to real and imaginary part
   \param[in] z Heaviside argument
   \return Heaviside step
   \todo Create Heaviside alias
   \todo Why not using real heaviside
*/
nr_complex_t step (const nr_complex_t z)
{
    nr_double_t x = real (z);
    nr_double_t y = imag (z);
    if (x < 0.0)
        x = 0.0;
    else if (x > 0.0)
        x = 1.0;
    else
        x = 0.5;
    if (y < 0.0)
        y = 0.0;
    else if (y > 0.0)
        y = 1.0;
    else
        y = 0.5;
    return nr_complex_t (x, y);
}

nr_complex_t cbesselj (unsigned int, nr_complex_t);

#include "cbesselj.cpp"

/*!\brief Bessel function of first kind

   \param[in] n order
   \param[in] z argument
   \return Bessel function of first kind of order n
   \bug Not implemented
*/
nr_complex_t jn (const int n, const nr_complex_t z)
{
    return cbesselj (n, z);
}

/*!\brief Bessel function of second kind

   \param[in] n order
   \param[in] z argument
   \return Bessel function of second kind of order n
   \bug Not implemented
*/
nr_complex_t yn (const int n, const nr_complex_t z)
{
    return nr_complex_t (::yn (n, std::real (z)), 0);
}

/*!\brief Modified Bessel function of first kind

   \param[in] z argument
   \return Modified Bessel function of first kind of order 0
   \bug Not implemented
*/
nr_complex_t i0 (const nr_complex_t z)
{
    return nr_complex_t (fspecial::i0 (std::real (z)), 0);
}

/*!\brief Error function

   \param[in] z argument
   \return Error function
   \bug Not implemented
*/
nr_complex_t erf (const nr_complex_t z)
{
#ifndef HAVE_ERF
    nr_double_t zerf = fspecial::erf (std::real (z));
#else
    nr_double_t zerf = std::erf (std::real (z));
#endif
    return nr_complex_t (zerf, 0);
}

/*!\brief Complementart error function

   \param[in] z argument
   \return Complementary error function
   \bug Not implemented
*/
nr_complex_t erfc (const nr_complex_t z)
{
#ifndef HAVE_ERFC
    nr_double_t zerfc = fspecial::erfc (std::real (z));
#else
    nr_double_t zerfc = std::erfc (std::real (z));
#endif
    return nr_complex_t (zerfc, 0);
}

/*!\brief Inverse of error function

   \param[in] z argument
   \return Inverse of error function
   \bug Not implemented
*/
nr_complex_t erfinv (const nr_complex_t z)
{
    return nr_complex_t (fspecial::erfinv (std::real (z)), 0);
}

/*!\brief Inverse of complementart error function

   \param[in] z argument
   \return Inverse of complementary error function
   \bug Not implemented
*/
nr_complex_t erfcinv (const nr_complex_t z)
{
    return nr_complex_t (fspecial::erfcinv (std::real (z)), 0);
}

/*!\brief Equality of two complex
  \todo Why not inline
  \note Like equality of double this test
        is meaningless in finite precision
	Use instead fabs(x-x0) < tol
*/
bool operator==(const nr_complex_t z1, const nr_complex_t z2)
{
    return (std::real (z1) == std::real (z2)) && (std::imag (z1) == std::imag (z2));
}

/*!\brief Inequality of two complex
  \todo Why not inline
  \note Like inequality of double this test
        is meaningless in finite precision
	Use instead fabs(x-x0) > tol
*/
bool operator!=(const nr_complex_t z1, const nr_complex_t z2)
{
    return (std::real (z1) != std::real (z2)) || (std::imag (z1) != std::imag (z2));
}

/*!\brief Superior of equal
   \todo Why not inline
*/
bool operator>=(const nr_complex_t z1, const nr_complex_t z2)
{
    return norm (z1) >= norm (z2);
}

/*!\brief Inferior of equal
   \todo Why not inline
*/
bool operator<=(const nr_complex_t z1, const nr_complex_t z2)
{
    return norm (z1) <= norm (z2);
}

/*!\brief Superior
   \todo Why not inline
*/
bool operator>(const nr_complex_t z1, const nr_complex_t z2)
{
    return norm (z1) > norm (z2);
}

/*!\brief Inferior
   \todo Why not inline
*/
bool operator<(const nr_complex_t z1, const nr_complex_t z2)
{
    return norm (z1) < norm (z2);
}

/*!\brief Modulo
   \todo Why not inline
*/
nr_complex_t operator%(const nr_complex_t z1, const nr_complex_t z2)
{
    return z1 - z2 * floor (z1 / z2);
}

/*!\brief Modulo
   \todo Why not inline
*/
nr_complex_t operator%(const nr_complex_t z1, const nr_double_t r2)
{
    return z1 - r2 * floor (z1 / r2);
}

/*!\brief Modulo
   \todo Why not inline
*/
nr_complex_t operator%(const nr_double_t r1, const nr_complex_t z2)
{
    return r1 - z2 * floor (r1 / z2);
}

} // namespace qucs
