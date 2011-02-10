/***************************************************************************
 *   Copyright (C) 2007 by SUSYfit Collaboration                           *
 *   authors@susyfit.org                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/** \file   gsl_complex.cpp
    \author SUSYfit Collaboration
    \date   Thu Nov 21 13:16:42 2007
    \brief  methods and function for gslpp::complex
 */

#include <math.h>
#ifndef GSLPP_COMPLEX_H
#include "gslpp_complex.h"
#endif
/** \include gslpp_complex.h
*/

#define GSLEPS 1.e-15

namespace gslpp
{
  /** Constructor  */
  complex::complex()
  {
    assign(0., 0., false);
  }

  complex::complex(const double& real=0., const double& imag=0., bool polar=false)
  {
    assign(real, imag, polar);
  }
  /** Copy constructor  */
  complex::complex(const complex& z)
  {
    assign(z.real(), z.imag(), false);
  }
  complex::complex(const double& a)
  {
    assign(a, 0., false);
  }
  /** Destructor */
  complex::~complex()
  {
  }
  /** Check if this is purely real  */
  bool complex::is_real() const
    {
      return ::fabs(imag()/real()) < GSLEPS;
    }

  /** Check if this is purely imaginary  */
  bool complex::is_imag() const
    {
      return ::fabs(real()/imag()) < GSLEPS;
    }

    /** Get the real part  */
    const double& complex::real() const
    {
      return GSL_REAL(_complex);
    }

  /** Get imaginary part  */
  const double& complex::imag() const
    {
      return GSL_IMAG(_complex);
    }

  /** Set the real part  */
  double& complex::real()
  {
    return GSL_REAL(_complex);
  }

  /** Set the imaginary part */
  double& complex::imag()
  {
    return GSL_IMAG(_complex);
  }

  /** Get arg */
  double complex::arg() const
    {
      return gsl_complex_arg(_complex);
    }

  /** Get abs */
  double complex::abs() const
    {
      return gsl_complex_abs(_complex);
    }

  /** Get the abs squared */
  double complex::abs2() const
    {
      return gsl_complex_abs2(_complex);
    }

  /** Get the log of the length */

  double complex::log_of_abs() const
    {
      return gsl_complex_logabs(_complex);
    }

  /** Assign */
  complex& complex::operator=(const complex& z)
  {
    GSL_SET_COMPLEX(&_complex, z.real(), z.imag());
    return *this;
  }

  /** Assign */
  complex& complex::operator=(const double& x)
  {
    GSL_SET_COMPLEX(&_complex, x, 0);
    return *this;
  }

  /** compare */
  bool complex::operator==(const complex& z1) const
    {
      return GSL_COMPLEX_EQ(_complex, z1._complex);
    }

  /** compare */
  bool complex::operator!=(const complex& z1) const
    {
      return !(GSL_COMPLEX_EQ(_complex, z1._complex));
    }

  /** Conversion  */
  gsl_complex* complex::as_gsl_type_ptr() const
    {
      return const_cast<gsl_complex*>(&_complex);
    }

  /** Conversion  */
  gsl_complex& complex::as_gsl_type()
  {
    return _complex;
  }

  /** Conversion  */
  const gsl_complex& complex::as_gsl_type() const
    {
      return _complex;
    }

  /** Conversion  */
  complex::operator gsl_complex& ()
  {
    return _complex;
  }

  /** Conversion  */
  complex::operator const gsl_complex& () const
    {
      return _complex;
    }

  std::ostream& operator<<(std::ostream& output, const complex& z)
  {
    double absim = ::fabs(z.imag());
    output << "(" <<  z.real() << (z.imag() < 0.? "-" : "+");
    if (absim != 1.)
      output << fabs(z.imag()) << "*";
    output << "i)";
    return output;
  }

  // const complex* complex::_i = 0;
  const complex& complex::i()
  {
    static complex _i(0.,1.);
    return _i;
  }

  complex::complex(const gsl_complex* z)
  {
//    _complex = (gsl_complex*)malloc(sizeof(gsl_complex));
    GSL_SET_COMPLEX(&_complex, GSL_REAL(*z), GSL_IMAG(*z));
  }

  complex::complex(const gsl_complex& z)
  {
//    _complex = (gsl_complex*)malloc(sizeof(gsl_complex));
    GSL_SET_COMPLEX(&_complex, GSL_REAL(z), GSL_IMAG(z));
  }

  void
  complex::assign(const double& real=0., const double& imag=0.,
                  bool polar=false)
  {
    if (polar)
      _complex = gsl_complex_polar(real,imag);
    else
      {
        GSL_SET_COMPLEX(&_complex, real, imag);
        // *_complex = gsl_complex_rect(real,imag);
      }
  }

  complex complex::operator-() const
    {
      gsl_complex t = gsl_complex_negative(_complex);
      return complex(&t);
    }

  complex complex::operator+(const complex& z1)
  {
    gsl_complex rl = gsl_complex_add(_complex, z1._complex);
    return complex(rl);
  }

  complex complex::operator-(const complex& z1)
  {
    gsl_complex rl = gsl_complex_sub(_complex, z1._complex);
    return complex(rl);
  }

  complex complex::operator*(const complex& z1)
  {
    gsl_complex rl = gsl_complex_mul(_complex, z1._complex);
    return complex(rl);
  }

  complex complex::operator/(const complex& z1)
  {
    gsl_complex rl = gsl_complex_div(_complex, z1._complex);
    return complex(rl);
  }

  complex& complex::operator+=(const complex& z1)
  {
    _complex = gsl_complex_add(_complex, z1._complex);
    return *this;
  }

  complex& complex::operator-=(const complex& z1)
  {
    _complex = gsl_complex_sub(_complex, z1._complex);
    return *this;
  }

  complex& complex::operator*=(const complex& z1)
  {
    _complex = gsl_complex_mul(_complex, z1._complex);
    return *this;
  }

  complex& complex::operator/=(const complex& z1)
  {
    _complex = gsl_complex_div(_complex, z1._complex);
    return *this;
  }

  complex complex::operator+(const double& a)
  {
    gsl_complex rl = gsl_complex_add_real(_complex,a);
    return complex(rl);
  }

  complex complex::operator-(const double& a)
  {
    gsl_complex rl = gsl_complex_sub_real(_complex,a);
    return complex(rl);
  }

  complex complex::operator*(const double& a)
  {
    gsl_complex rl = gsl_complex_mul_real(_complex,a);
    return complex(rl);
  }

  complex complex::operator/(const double& a)
  {
    gsl_complex rl = gsl_complex_div_real(_complex,a);
    return complex(rl);
  }

  complex& complex::operator+=(const double& a)
  {
    _complex = gsl_complex_add_real(_complex,a);
    return *this;
  }

  complex& complex::operator-=(const double& a)
  {
    _complex = gsl_complex_sub_real(_complex,a);
    return *this;
  }

  complex&
  complex::operator*=(const double& a)
  {
    _complex = gsl_complex_mul_real(_complex,a);
    return *this;
  }

  complex& complex::operator/=(const double& a)
  {
    _complex = gsl_complex_div_real(_complex,a);
    return *this;
  }

  complex complex::conjugate() const
    {
      gsl_complex t = gsl_complex_conjugate(_complex);
      return complex(t);
    }

  complex complex::inverse() const
    {
      gsl_complex t = gsl_complex_inverse(_complex);
      return complex(t);
    }

  //==================================================================
  /** @{
  \name Operations on complex numbers  */
  /** Add a real and complex numbers
  \ingroup complex
  \param x1 Real number
  \param z2 Complex number
  \return \f$ x_1 + z_2 \f$ */
  complex operator+(const double& x1, const complex& z2)
  {
    complex z1(x1, 0.);
    return z1 + z2;
  }

  /** Subtract a real and complex numbers
  \ingroup complex
  \param x1 Real number
  \param z2 Complex number
  \return \f$ x_1 - z_2 \f$ */
  complex operator-(const double& x1, const complex& z2)
  {
    complex z1(x1, 0.);
    return z1 - z2;
  }

  /** Multiply a real and complex numbers
  \ingroup complex
  \param x1 Real number
  \param z2 Complex number
  \return \f$ x_1 z_2 \f$ */
  complex operator*(const double& x1, const complex& z2)
  {
    complex z1(x1, 0.);
    return z1 * z2;
  }

  /** Divide a real and complex numbers
  \ingroup complex
  \param x1 Real number
  \param z2 Complex number
  \return \f$ x_1 / z_2 \f$ */
  complex operator/(const double& x1, const complex& z2)
  {
    complex z1(x1, 0);
    return z1 / z2;
  }

  /** @} */

  //==================================================================
  /** @{
  \name Exponential and logarithms of complex numbers */
  /** exponentioal of a complex number
  \ingroup complex
  \param z Complex number
  \return \f$ e^z \f$*/
  complex exp(const complex& z)
  {
    return complex(gsl_complex_exp(z.as_gsl_type()));
  }

  /** Logarithm of a complex number (base e)
  \ingroup complex
  \param z Complex number
  \return \f$ \log z \f$*/
  complex log(const complex& z)
  {
    return complex(gsl_complex_log(z.as_gsl_type()));
  }

  /** Logarithm of a complex number (base 10)
  \ingroup complex
  \param z Complex number
  \return \f$ \log_{10} z \f$*/
  complex log10(const complex& z)
  {
    return complex(gsl_complex_log10(z.as_gsl_type()));
  }

  /** Logarithm of a complex number (base b)
  \ingroup complex
  \param z Complex number
  \param b Complex number
  \return \f$ \log_b z \f$*/
  complex log(const complex& z,
              const complex& b)
  {
    return complex(gsl_complex_log_b(z.as_gsl_type(),b.as_gsl_type()));
  }
  /** @} */

  //==================================================================
  /** @{
  \name Powers of complex numbers */
  /** Square root of a complex number
  \ingroup complex
  \param z Complex number
  \return \f$ \sqrt z \f$*/
  complex sqrt(const complex& z)
  {
    return complex(gsl_complex_sqrt(z.as_gsl_type()));
  }

  /** Complex number to the z2 complex order
  \ingroup complex
  \param z1 Complex number
  \param z2 Complex number
  \return \f$ z_1^{z_2} \f$*/
  complex pow(const complex& z1,
              const complex& z2)
  {
    return complex(gsl_complex_pow(z1.as_gsl_type(),
                                   z2.as_gsl_type()));
  }

  /** Complex number to the x real order
  \ingroup complex
  \param z Complex number
  \param x Real number
  \return \f$ z^x \f$ */
  complex pow(const complex& z, const double  x)
  {
    return complex(gsl_complex_pow_real(z.as_gsl_type(), x));
  }
  /** @} */

  //==================================================================
  /** @{
  \name trigonometric functions on complex numbers */
  /** Sine
  \ingroup complex
  \param z Complex number
  \return \f$ \sin z \f$*/
  complex sin(const complex& z)
  {
    return complex(gsl_complex_sin(z.as_gsl_type()));
  }

  /** Cosine
  \ingroup complex
  \param z Complex number
  \return \f$ \cos z \f$*/
  complex cos(const complex& z)
  {
    return complex(gsl_complex_cos(z.as_gsl_type()));
  }

  /** Tangent
  \ingroup complex
  \param z Complex number
  \return \f$ \tan z \f$*/
  complex tan(const complex& z)
  {
    return complex(gsl_complex_tan(z.as_gsl_type()));
  }

  /** Secant
  \ingroup complex
  \param z Complex number
  \return \f$ \sec z \f$*/
  complex sec(const complex& z)
  {
    return complex(gsl_complex_sec(z.as_gsl_type()));
  }

  /** Cosecant
  \ingroup complex
  \param z Complex number
  \return \f$ \csc z \f$*/
  complex csc(const complex& z)
  {
    return complex(gsl_complex_csc(z.as_gsl_type()));
  }

  /** Cotangent
  \ingroup complex
  \param z Complex number
  \return \f$ \cot z \f$*/
  complex cot(const complex& z)
  {
    return complex(gsl_complex_cot(z.as_gsl_type()));
  }

  /** Inverse sine
  \ingroup complex
  \param z Complex number
  \return \f$ \arcsin z \f$*/
  complex arcsin(const complex& z)
  {
    return complex(gsl_complex_arcsin(z.as_gsl_type()));
  }

  /** Inverse cosine
  \ingroup complex
  \param z Complex number
  \return \f$ \arccos z \f$*/
  complex arccos(const complex& z)
  {
    return complex(gsl_complex_arccos(z.as_gsl_type()));
  }

  /** Inverse tangent
  \ingroup complex
  \param z Complex number
  \return \f$ \arctan z \f$*/
  complex arctan(const complex& z)
  {
    return complex(gsl_complex_arctan(z.as_gsl_type()));
  }

  /** Inverse secant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{asec} z \f$*/
  complex arcsec(const complex& z)
  {
    return complex(gsl_complex_arcsec(z.as_gsl_type()));
  }

  /** Inverse cosecant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{acsc} z \f$*/
  complex arccsc(const complex& z)
  {
    return complex(gsl_complex_arccsc(z.as_gsl_type()));
  }

  /** Inverse cotangent
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{acot} z \f$*/
  complex arccot(const complex& z)
  {
    return complex(gsl_complex_arccot(z.as_gsl_type()));
  }

  /** @} */

  //==================================================================
  /** @{
  \name Hyperbolic functions on complex numbers */
  /** Hyperbolic sine
  \ingroup complex
  \param z Complex number
  \return \f$ \sinh z \f$*/
  complex sinh(const complex& z)
  {
    return complex(gsl_complex_sinh(z.as_gsl_type()));
  }

  /** Hyperbolic cosine
  \ingroup complex
  \param z Complex number
  \return \f$ \cosh z \f$*/
  complex cosh(const complex& z)
  {
    return complex(gsl_complex_cosh(z.as_gsl_type()));
  }

  /** Hyperbolic tangent
  \ingroup complex
  \param z Complex number
  \return \f$ \tanh z \f$*/
  complex tanh(const complex& z)
  {
    return complex(gsl_complex_tanh(z.as_gsl_type()));
  }

  /** Hyperbolic secant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{sech} z \f$*/
  complex sech(const complex& z)
  {
    return complex(gsl_complex_sech(z.as_gsl_type()));
  }

  /** Hyperbolic cosecant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{csch} z \f$*/
  complex csch(const complex& z)
  {
    return complex(gsl_complex_csch(z.as_gsl_type()));
  }

  /** Hyperbolic cotangent
  \ingroup complex
  \param z Complex number
  \return \f$ \coth z \f$*/
  complex coth(const complex& z)
  {
    return complex(gsl_complex_coth(z.as_gsl_type()));
  }

  /** Inverse hyperbolic sine
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{asinh} z \f$*/
  complex arcsinh(const complex& z)
  {
    return complex(gsl_complex_arcsinh(z.as_gsl_type()));
  }

  /** Inverse hyperbolic cosine
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{acosh} z \f$*/
  complex arccosh(const complex& z)
  {
    return complex(gsl_complex_arccosh(z.as_gsl_type()));
  }

  /** Inverse hyperbolic tangent
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{atanh} z \f$*/
  complex arctanh(const complex& z)
  {
    return complex(gsl_complex_arctanh(z.as_gsl_type()));
  }

  /** Inverse hyperbolic secant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{asech} z \f$*/
  complex arcsech(const complex& z)
  {
    return complex(gsl_complex_arcsech(z.as_gsl_type()));
  }

  /** Inverse hyperbolic cosecant
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{acsch} z \f$*/
  complex arccsch(const complex& z)
  {
    return complex(gsl_complex_arccsch(z.as_gsl_type()));
  }

  /** Inverse hyperbolic cotangent
  \ingroup complex
  \param z Complex number
  \return \f$ \mathrm{acoth}(z) \f$*/
  complex arccoth(const complex& z)
  {
    return complex(gsl_complex_arccoth(z.as_gsl_type()));
  }

  /** @} */
}
//
// EOF
//
