/*------------------------------------------------------------
This file will test the functionality of the Vector4 class which
will be used in the Killer1 Engine. Most of the examples and all
of the equations are from 3D Math Primer for Graphics and Game
Development by Dunn and Parberry (awesome book for those who
wish to learn).

Uses the boost test library.

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.


Written by Maxwell Miller
-------------------------------------------------------------*/

#include <boost/test/unit_test.hpp>
#include <UnitTests/TestHelper.h>
#include <Engine/Atom.h>
#include <Engine/Quaternion.h>


#include <math.h>
#include <string.h>
#include <stdlib.h>

namespace KM = KillerMath;

BOOST_AUTO_TEST_CASE(QuaternionDefaultConstructor)
{
	KM::Quaternion Q{};

	const real* elems = Q.GetElems();

	BOOST_CHECK_EQUAL(elems[0], 0.0f);
	BOOST_CHECK_EQUAL(elems[1], 0.0f);
	BOOST_CHECK_EQUAL(elems[2], 0.0f);
	BOOST_CHECK_EQUAL(elems[3], 0.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionSingleValueConstructor)
{
	KM::Quaternion Q{1.0f};

	const real* elems = Q.GetElems();

	BOOST_CHECK_EQUAL(elems[0], 1.0f);
	BOOST_CHECK_EQUAL(elems[1], 1.0f);
	BOOST_CHECK_EQUAL(elems[2], 1.0f);
	BOOST_CHECK_EQUAL(elems[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionMultiValueConstructor)
{
	KM::Quaternion Q{0.0f, 1.0f, 2.0f, 3.0f};

	const real* elems = Q.GetElems();

	BOOST_CHECK_EQUAL(elems[0], 0.0f);
	BOOST_CHECK_EQUAL(elems[1], 1.0f);
	BOOST_CHECK_EQUAL(elems[2], 2.0f);
	BOOST_CHECK_EQUAL(elems[3], 3.0f);	
}

BOOST_AUTO_TEST_CASE(QuaternionCopyConstructor)
{
	KM::Quaternion Q1{1.0f, 4.0f, 2.0f, 0.004f};
	KM::Quaternion Q2 = Q1;

	const real* elems = Q2.GetElems();

	BOOST_CHECK_EQUAL(elems[0], 1.0f);
	BOOST_CHECK_EQUAL(elems[1], 4.0f);
	BOOST_CHECK_EQUAL(elems[2], 2.0f);
	BOOST_CHECK_EQUAL(elems[3], 0.004f);
}

BOOST_AUTO_TEST_CASE(QuaternionGetters)
{
	KM::Quaternion Q{3.0f, 2.0f, 100.0f, 0.0534f};

	BOOST_CHECK_EQUAL(Q[0], 3.0f);
	BOOST_CHECK_EQUAL(Q[1], 2.0f);
	BOOST_CHECK_EQUAL(Q[2], 100.0f);
	BOOST_CHECK_EQUAL(Q[3], 0.0534f);
}

BOOST_AUTO_TEST_CASE(QuaternionMagnitude)
{
	KM::Quaternion Q{0.5f, 10.0f, 20.0f, 30.0f};

	BOOST_CHECK_EQUAL(RoundReal(Q.Magnitude()), RoundReal(37.41992f));
}

BOOST_AUTO_TEST_CASE(QuaternionConjugate)
{
	KM::Quaternion Q1{1.0f, 3.0f, 5.0f, 2.0f};

	KM::Quaternion Q2{-3.04f, 0.9435f, -0.8443f, -3.043234f};

	KM::Quaternion Q3 = Q1.Conjugate();

	KM::Quaternion Q4 = Q2.Conjugate();

	BOOST_CHECK_EQUAL(Q3[0], 1.0f);
	BOOST_CHECK_EQUAL(Q3[1], -3.0f);
	BOOST_CHECK_EQUAL(Q3[2], -5.0f);
	BOOST_CHECK_EQUAL(Q3[3], -2.0f);

	BOOST_CHECK_EQUAL(Q4[0], -3.04f);
	BOOST_CHECK_EQUAL(Q4[1], -0.9435f);
	BOOST_CHECK_EQUAL(Q4[2], 0.8443f);
	BOOST_CHECK_EQUAL(Q4[3], 3.043234f);
}

BOOST_AUTO_TEST_CASE(QuaternionInverse)
{
	KM::Quaternion Q1{1.0f, 6.0f, 8.0f, 12.0f};

	KM::Quaternion Q2 = Q1.Inverse();

	BOOST_CHECK_EQUAL(RoundReal(Q2[0]), RoundReal(0.06389f));
	BOOST_CHECK_EQUAL(RoundReal(Q2[1]), RoundReal(-0.38333f));
	BOOST_CHECK_EQUAL(RoundReal(Q2[2]), RoundReal(-0.51110f));
	BOOST_CHECK_EQUAL(RoundReal(Q2[3]), RoundReal(-0.76665f));
}

BOOST_AUTO_TEST_CASE(QuaternionDivideByScalar)
{
	KM::Quaternion Q1{2.0f, 4.0f, 6.0f, 8.0f};

	Q1 = Q1 / 2.0f;

	KM::Quaternion Q2{3.0f, 6.0f, 9.0f, 12.0f};

	Q2 /= 3.0f;

	BOOST_CHECK_EQUAL(Q1[0], 1.0f);
	BOOST_CHECK_EQUAL(Q1[1], 2.0f);
	BOOST_CHECK_EQUAL(Q1[2], 3.0f);
	BOOST_CHECK_EQUAL(Q1[3], 4.0f);

	BOOST_CHECK_EQUAL(Q2[0], 1.0f);
	BOOST_CHECK_EQUAL(Q2[1], 2.0f);
	BOOST_CHECK_EQUAL(Q2[2], 3.0f);
	BOOST_CHECK_EQUAL(Q2[3], 4.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionMultipliedByScalar)
{
	KM::Quaternion Q1{4.0f, 2.0f, 6.0f, 9.0f};

	Q1 = Q1 * 5.0f;

	KM::Quaternion Q2{8.0f, 3.0f, 0.0f, 2.0f};

	Q2 *= 14.0f;

	BOOST_CHECK_EQUAL(Q1[0], 20.0f);
	BOOST_CHECK_EQUAL(Q1[1], 10.0f);
	BOOST_CHECK_EQUAL(Q1[2], 30.0f);
	BOOST_CHECK_EQUAL(Q1[3], 45.0f);

	BOOST_CHECK_EQUAL(Q2[0], 112.0f);
	BOOST_CHECK_EQUAL(Q2[1], 42.0f);
	BOOST_CHECK_EQUAL(Q2[2], 0.0f);
	BOOST_CHECK_EQUAL(Q2[3], 28.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionMultipliedByQuaternion)
{
	KM::Quaternion Q1{5.0f, 3.0f, 8.0f, 6.0f};

	KM::Quaternion Q2{6.0f, 12.0f, 1.0f, 5.0f};

	KM::Quaternion Q3 = Q1 * Q2;

	KM::Quaternion Q4{5.0f, 3.0f, 8.0f, 6.0f};

	Q4 *= Q2;

	BOOST_CHECK_EQUAL(Q3[0], -44.0f);
	BOOST_CHECK_EQUAL(Q3[1], 112.0f);
	BOOST_CHECK_EQUAL(Q3[2], 110.0f);
	BOOST_CHECK_EQUAL(Q3[3], -32.0f);

	BOOST_CHECK_EQUAL(Q4[0], -44.0f);
	BOOST_CHECK_EQUAL(Q4[1], 112.0f);
	BOOST_CHECK_EQUAL(Q4[2], 110.0f);
	BOOST_CHECK_EQUAL(Q4[3], -32.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionDifference)
{
	KM::Quaternion Q1{1.0f, 2.0f, 3.0f, 2.0f};

	KM::Quaternion Q2{1.0f, 3.0f, 2.0f, 3.0f};

	KM::Quaternion Q3 = Q1.Difference(Q2);

	BOOST_CHECK_EQUAL(RoundReal(Q3[0]), 4.47834f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[1]), 1.41421f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[2]), -0.2357f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[3]), -0.94281f);
}

BOOST_AUTO_TEST_CASE(QuaternionDot)
{
	KM::Quaternion Q1{6.0f, 4.0f, 12.0f, 0.0f};

	KM::Quaternion Q2{1.0f, 6.0f, 8.0f, 3.0f};

	real dot = Q1.Dot(Q2);

	BOOST_CHECK_EQUAL(dot, 126.0f);	
}

BOOST_AUTO_TEST_CASE(QuaternionNegationAndOpposite)
{
	KM::Quaternion Q1{2.0f, -3.0f, 4.0f, -5.0f};

	Q1.Negate();

	KM::Quaternion Q2{-3.0f, 2.0f, -3.0f, -5.0f};

	KM::Quaternion Q3 = Q2.Opposite();

	BOOST_CHECK_EQUAL(RoundReal(Q1[0]), -2.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q1[1]), 3.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q1[2]), -4.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q1[3]), 5.0f);

	BOOST_CHECK_EQUAL(RoundReal(Q3[0]), 3.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[1]), -2.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[2]), 3.0f);
	BOOST_CHECK_EQUAL(RoundReal(Q3[3]), 5.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionNormalization)
{
	KM::Quaternion Q1{4.0f, 2.0f, 6.0f, 2.0f};

	Q1.Normalize();

	BOOST_CHECK_EQUAL(RoundReal(Q1.Magnitude()), 1.0f);
}

BOOST_AUTO_TEST_CASE(QuaternionAddScaledQuaternion)
{
	KM::Quaternion Q1{1.0f, 2.0f, 3.0f, 4.0f};
	KM::Vector4 vec{1.0f, 1.0f, 1.0f, 1.0f};

	Q1.AddScaledVector(vec, 5.0f);

	BOOST_CHECK_EQUAL(Q1[0], 6.0f);
	BOOST_CHECK_EQUAL(Q1[1], 7.0f);
	BOOST_CHECK_EQUAL(Q1[2], 8.0f);
	BOOST_CHECK_EQUAL(Q1[3], 9.0f);
}