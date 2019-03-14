/*------------------------------------------------------------
This file will test the functionality of the Point class which
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
#include <Engine/Point.h>
#include <Engine/Vector4.h>


namespace KM = KillerMath;

BOOST_AUTO_TEST_CASE(PointefaultConstructorAndAccessor) 
{
	KM::Point v {};

	BOOST_CHECK_EQUAL(v[0], 0.0f);
	BOOST_CHECK_EQUAL(v[1], 0.0f);
	BOOST_CHECK_EQUAL(v[2], 0.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointSingleContructor) 
{
	KM::Point v {5.0f};

	BOOST_CHECK_EQUAL(v[0], 5.0f);
	BOOST_CHECK_EQUAL(v[1], 5.0f);
	BOOST_CHECK_EQUAL(v[2], 5.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointDoubleContructor) 
{
	KM::Point v {1.0f, 2.0f};

	BOOST_CHECK_EQUAL(v[0], 1.0f);
	BOOST_CHECK_EQUAL(v[1], 2.0f);
	BOOST_CHECK_EQUAL(v[2], 0.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointTrippleContructor) 
{
	KM::Point v {1.0f, 2.0f, 3.0f};

	BOOST_CHECK_EQUAL(v[0], 1.0f);
	BOOST_CHECK_EQUAL(v[1], 2.0f);
	BOOST_CHECK_EQUAL(v[2], 3.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointCopyContructor) 
{
	KM::Point Point1 {3.0f, 6.0f, 9.0f};

	KM::Point Point(Point1);

	BOOST_CHECK_EQUAL(Point[0], 3.0f);
	BOOST_CHECK_EQUAL(Point[1], 6.0f);
	BOOST_CHECK_EQUAL(Point[2], 9.0f);
	BOOST_CHECK_EQUAL(Point[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointSetters) 
{
	KM::Point v{};

	v[0] = 5.0f;
	v[1] = 10.0f;
	v[2] = 20.0f;
	v[3] = 1.0f;

	BOOST_CHECK_EQUAL(v[0], 5.0f);
	BOOST_CHECK_EQUAL(v[1], 10.0f);
	BOOST_CHECK_EQUAL(v[2], 20.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointCopyAssignment) 
{
	KM::Point v1 {4.5f, 5.4f, 6.8f};

	KM::Point v2 = v1;

	BOOST_CHECK_EQUAL(v2[0], 4.5f);
	BOOST_CHECK_EQUAL(v2[1], 5.4f);
	BOOST_CHECK_EQUAL(v2[2], 6.8f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);

	KM::Point v3 {4.5f, 5.4f};
	v3.Make2D();

	KM::Point v4 = v3;

	BOOST_CHECK_EQUAL(v2[0], 4.5f);
	BOOST_CHECK_EQUAL(v2[1], 5.4f);
	BOOST_CHECK_EQUAL(v2[2], 6.8f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAssignment) 
{
	KM::Point v1{};
	v1 = 3.0f;

	BOOST_CHECK_EQUAL(v1[0], 3.0f);
	BOOST_CHECK_EQUAL(v1[1], 3.0f);
	BOOST_CHECK_EQUAL(v1[2], 3.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v2{};
	v2.Make2D();
	v2 = 3.0f;

	BOOST_CHECK_EQUAL(v2[0], 3.0f);
	BOOST_CHECK_EQUAL(v2[1], 3.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAddPoint) 
{
	KM::Point v1 {1.0f, 1.0f, 2.0f};
	KM::Point v2 {2.0f, 3.0f, 4.0f};

	KM::Point sum = v1 + v2;

	BOOST_CHECK_EQUAL(sum[0], 3.0f);
	BOOST_CHECK_EQUAL(sum[1], 4.0f);
	BOOST_CHECK_EQUAL(sum[2], 6.0f);
	BOOST_CHECK_EQUAL(sum[3], 1.0f);

	KM::Point v3 {1.0f, 1.0f};
	v3.Make2D();
	KM::Point v4 {2.0f, 3.0f, 4.0f};

	KM::Point sum2 = v3 + v4;

	BOOST_CHECK_EQUAL(sum2[0], 3.0f);
	BOOST_CHECK_EQUAL(sum2[1], 4.0f);
	BOOST_CHECK_EQUAL(sum2[2], 0.0f);
	BOOST_CHECK_EQUAL(sum2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAddVector4) 
{
	KM::Point v1 {1.0f, 1.0f, 2.0f};
	KM::Vector4 v2 {2.0f, 3.0f, 4.0f};

	KM::Point sum = v1 + v2;

	BOOST_CHECK_EQUAL(sum[0], 3.0f);
	BOOST_CHECK_EQUAL(sum[1], 4.0f);
	BOOST_CHECK_EQUAL(sum[2], 6.0f);
	BOOST_CHECK_EQUAL(sum[3], 1.0f);

	KM::Point v3 {1.0f, 1.0f};
	v3.Make2D();
	KM::Vector4 v4 {2.0f, 3.0f, 4.0f};

	KM::Point sum2 = v3 + v4;

	BOOST_CHECK_EQUAL(sum2[0], 3.0f);
	BOOST_CHECK_EQUAL(sum2[1], 4.0f);
	BOOST_CHECK_EQUAL(sum2[2], 0.0f);
	BOOST_CHECK_EQUAL(sum2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAddEqPoint) 
{
	KM::Point v1 {1.0f, 1.0f, 2.0f};
	KM::Point v2 {1.0f, 1.0f, 3.0f};

	v1 += v2;

	BOOST_CHECK_EQUAL(v1[0], 2.0f);
	BOOST_CHECK_EQUAL(v1[1], 2.0f);
	BOOST_CHECK_EQUAL(v1[2], 5.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v3 {1.0f, 1.0f};
	KM::Point v4 {1.0f, 1.0f, 3.0f};

	v3 += v4;

	BOOST_CHECK_EQUAL(v3[0], 2.0f);
	BOOST_CHECK_EQUAL(v3[1], 2.0f);
	BOOST_CHECK_EQUAL(v3[2], 0.0f);
	BOOST_CHECK_EQUAL(v3[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAddEqVector4) 
{
	KM::Point v1 {1.0f, 1.0f, 2.0f};
	KM::Vector4 v2 {1.0f, 1.0f, 3.0f};

	v1 += v2;

	BOOST_CHECK_EQUAL(v1[0], 2.0f);
	BOOST_CHECK_EQUAL(v1[1], 2.0f);
	BOOST_CHECK_EQUAL(v1[2], 5.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v3 {1.0f, 1.0f};
	KM::Vector4 v4 {1.0f, 1.0f, 3.0f};

	v3 += v4;

	BOOST_CHECK_EQUAL(v3[0], 2.0f);
	BOOST_CHECK_EQUAL(v3[1], 2.0f);
	BOOST_CHECK_EQUAL(v3[2], 0.0f);
	BOOST_CHECK_EQUAL(v3[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointSubtractPoint) 
{
	KM::Point v1 {20.0f, 30.0f, 40.0f};
	KM::Point v2 {5.0f, 5.0f, 5.0f};

	KM::Point difference = v1 - v2;

	BOOST_CHECK_EQUAL(difference[0], 15.0f);
	BOOST_CHECK_EQUAL(difference[1], 25.0f);
	BOOST_CHECK_EQUAL(difference[2], 35.0f);
	BOOST_CHECK_EQUAL(difference[3], 1.0f);

	KM::Point v3 {20.0f, 30.0f};
	KM::Point v4 {5.0f, 5.0f, 5.0f};

	KM::Point difference2 = v3 - v4;

	BOOST_CHECK_EQUAL(difference2[0], 15.0f);
	BOOST_CHECK_EQUAL(difference2[1], 25.0f);
	BOOST_CHECK_EQUAL(difference2[2], 0.0f);
	BOOST_CHECK_EQUAL(difference2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointSubtractEqPoint) 
{
	KM::Point v1 {2.0f, 3.0f, 4.0f};
	KM::Point v2 {1.0f, 1.0f, 1.0f};

	v1 -= v2;

	BOOST_CHECK_EQUAL(v1[0], 1.0f);
	BOOST_CHECK_EQUAL(v1[1], 2.0f);
	BOOST_CHECK_EQUAL(v1[2], 3.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v3 {2.0f, 3.0f};
	v3.Make2D();
	KM::Point v4 {1.0f, 1.0f, 1.0f};

	v3 -= v4;

	BOOST_CHECK_EQUAL(v3[0], 1.0f);
	BOOST_CHECK_EQUAL(v3[1], 2.0f);
	BOOST_CHECK_EQUAL(v3[2], 0.0f);
	BOOST_CHECK_EQUAL(v3[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointMultiplyPointScalar) 
{
	KM::Point v1 {2.0f, 3.0f, 4.0f};
	F32 v2 {5.0f};

	KM::Point product = v1 * v2;

	BOOST_CHECK_EQUAL(product[0], 10.0f);
	BOOST_CHECK_EQUAL(product[1], 15.0f);
	BOOST_CHECK_EQUAL(product[2], 20.0f);
	BOOST_CHECK_EQUAL(product[3], 1.0f);

	KM::Point v3 {2.0f, 3.0f};
	v3.Make2D();
	F32 v4 {5.0f};

	KM::Point product2 = v3 * v4;

	BOOST_CHECK_EQUAL(product2[0], 10.0f);
	BOOST_CHECK_EQUAL(product2[1], 15.0f);
	BOOST_CHECK_EQUAL(product2[2], 0.0f);
	BOOST_CHECK_EQUAL(product2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointMultiplyEqPointScalar) 
{
	KM::Point v1 {8.0f, 10.0f, 15.0f};
	F32 v2 {5.0f};

	v1 *= v2;

	BOOST_CHECK_EQUAL(v1[0], 40.0f);
	BOOST_CHECK_EQUAL(v1[1], 50.0f);
	BOOST_CHECK_EQUAL(v1[2], 75.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v3 {8.0f, 10.0f};
	v3.Make2D();
	F32 v4 {5.0f};

	v3 *= v4;

	BOOST_CHECK_EQUAL(v3[0], 40.0f);
	BOOST_CHECK_EQUAL(v3[1], 50.0f);
	BOOST_CHECK_EQUAL(v3[2], 0.0f);
	BOOST_CHECK_EQUAL(v3[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointMultiplyByPoint)
{
	KM::Point A {2.0f, 5.0f, 10.0f};
	KM::Point B {6.0f, 8.0f, 9.0f};

	KM::Point C = A * B;


	BOOST_CHECK_EQUAL(C[0], 12.0f);
	BOOST_CHECK_EQUAL(C[1], 40.0f);
	BOOST_CHECK_EQUAL(C[2], 90.0f);
	BOOST_CHECK_EQUAL(C[3], 1.0f);

	KM::Point D {2.0f, 5.0f};
	D.Make2D();
	KM::Point E {6.0f, 8.0f, 9.0f};

	KM::Point F = D * E;

	BOOST_CHECK_EQUAL(F[0], 12.0f);
	BOOST_CHECK_EQUAL(F[1], 40.0f);
	BOOST_CHECK_EQUAL(F[2], 0.0f);
	BOOST_CHECK_EQUAL(F[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointDotMultiplication) 
{
	KM::Point A {4.0f, 6.0f, 9.0f};
	KM::Point B {-3.0f, 7.0f, 3.0f};

	BOOST_CHECK_EQUAL(A.Dot(B), 57.0f);

//===== TODO:: Need to add 2d dot product test =====
}

BOOST_AUTO_TEST_CASE(PointDividePointByScalar) 
{
	KM::Point v1 {10.0f, 20.0f, 30.0f};

	KM::Point quotient = v1 / 2.0f;

	BOOST_CHECK_EQUAL(quotient[0], 5.0f);
	BOOST_CHECK_EQUAL(quotient[1], 10.0f);
	BOOST_CHECK_EQUAL(quotient[2], 15.0f);
	BOOST_CHECK_EQUAL(quotient[3], 1.0f);

	KM::Point v2 {10.0f, 20.0f};
	v2.Make2D();

	KM::Point quotient2 = v2 / 2.0f;

	BOOST_CHECK_EQUAL(quotient2[0], 5);
	BOOST_CHECK_EQUAL(quotient2[1], 10);
	BOOST_CHECK_EQUAL(quotient2[2], 0.0f);
	BOOST_CHECK_EQUAL(quotient2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointDivideEqPointByScalar) 
{
	KM::Point v1 {10.0f, 20.0f, 40.0f};
	F32 v2 {2.0f};

	v1 /= v2;

	BOOST_CHECK_EQUAL(v1[0], 5);
	BOOST_CHECK_EQUAL(v1[1], 10);
	BOOST_CHECK_EQUAL(v1[2], 20.0f);
	BOOST_CHECK_EQUAL(v1[3], 1.0f);

	KM::Point v3 {10.0f, 20.0f};
	v3.Make2D();
	F32 v4 {2.0f};

	v3 /= v4;

	BOOST_CHECK_EQUAL(v3[0], 5);
	BOOST_CHECK_EQUAL(v3[1], 10);
	BOOST_CHECK_EQUAL(v3[2], 0.0f);
	BOOST_CHECK_EQUAL(v3[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(Point_Comparison_Operators)
{
	KM::Point midValue {5.0f, 10.0f, 15.0f};
	KM::Point highValue {40.0f, 50.0f, 60.0f};
	highValue[3] = 2.0f;
	KM::Point lowValue {1.0f, 2.0f, 3.0f};
	lowValue[3] = 0.0f;
	KM::Point equalValue = midValue;
	
	BOOST_CHECK_EQUAL(midValue > lowValue, true);
	BOOST_CHECK_EQUAL(midValue < highValue, true);
	BOOST_CHECK_EQUAL(midValue >= equalValue, true);
	BOOST_CHECK_EQUAL(midValue <= equalValue, true);
	BOOST_CHECK_EQUAL(midValue == equalValue, true);
	BOOST_CHECK_EQUAL(midValue != highValue, true);

	BOOST_CHECK_EQUAL(midValue < lowValue, false);
	BOOST_CHECK_EQUAL(midValue > highValue, false);
	BOOST_CHECK_EQUAL(midValue <= lowValue, false);
	BOOST_CHECK_EQUAL(midValue >= highValue, false);
	BOOST_CHECK_EQUAL(midValue == lowValue, false);	
	BOOST_CHECK_EQUAL(midValue != equalValue, false);

	highValue[0] = 1.0f;

	BOOST_CHECK_EQUAL(midValue >= highValue, false);
}

BOOST_AUTO_TEST_CASE(PointMagnitude) {
	KM::Point PointTest {5.0f, -4.0f, 10.0f};
	F32 mag = PointTest.Magnitude();

	BOOST_CHECK_EQUAL(RoundFloat(mag), 11.87434f);

//===== TODO:: Add 2D test =====	
}

BOOST_AUTO_TEST_CASE(PointNormalize) 
{
	KM::Point PointTest {12.0f, -5.0f, 25.0f};
	PointTest.Normalize();

	BOOST_CHECK_EQUAL(RoundFloat(PointTest[0]), 0.42586f);
	BOOST_CHECK_EQUAL(RoundFloat(PointTest[1]), -0.17744f);
	BOOST_CHECK_EQUAL(RoundFloat(PointTest[2]), 0.88722f);
	BOOST_CHECK_EQUAL(PointTest[3], 1.0f);

//===== TODO:: Add 2D test =====	
}

BOOST_AUTO_TEST_CASE(PointResetvoid) 
{
	KM::Point PointTest {12.0f, -5.0f, 20.0f};

	BOOST_CHECK_EQUAL(PointTest[0], 12.0f);
	BOOST_CHECK_EQUAL(PointTest[1], -5.0f);
	BOOST_CHECK_EQUAL(PointTest[2], 20.0f);
	BOOST_CHECK_EQUAL(PointTest[3], 1.0f);

	PointTest.Reset();

	BOOST_CHECK_EQUAL(PointTest[0], 0.0f);
	BOOST_CHECK_EQUAL(PointTest[1], 0.0f);
	BOOST_CHECK_EQUAL(PointTest[2], 0.0f);
	BOOST_CHECK_EQUAL(PointTest[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointAddScaledPoint) 
{
	KM::Point PointTest {15.0f, 25.0f, 45.0f};
	KM::Point scaled {45.0f, 10.0f, 20.0f};

	PointTest.AddScaledPoint(scaled, 10);

	BOOST_CHECK_EQUAL(PointTest[0], 465.0f);
	BOOST_CHECK_EQUAL(PointTest[1], 125.0f);
	BOOST_CHECK_EQUAL(PointTest[2], 245.0f);
	BOOST_CHECK_EQUAL(PointTest[3], 1.0f);

	KM::Point PointTest2 {15.0f, 25.0f};
	PointTest2.Make2D();
	PointTest2.AddScaledPoint(scaled, 10);

	BOOST_CHECK_EQUAL(PointTest2[0], 465.0f);
	BOOST_CHECK_EQUAL(PointTest2[1], 125.0f);
	BOOST_CHECK_EQUAL(PointTest2[2], 0.0f);
	BOOST_CHECK_EQUAL(PointTest2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointCrossProduct) 
{
	KM::Point v1 {1, 3, 4};
	KM::Point v2 {2, -5, 8};

	KM::Point cross = v1.CrossProduct(v2);

	BOOST_CHECK_EQUAL(cross[0], 44.0f);
	BOOST_CHECK_EQUAL(cross[1], 0.0f);
	BOOST_CHECK_EQUAL(cross[2], -11.0f);
	BOOST_CHECK_EQUAL(cross[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointSetFunctionTest)
{
	KM::Point v {};

	v.Set(10.0f, 15.0f, 20.0f);

	BOOST_CHECK_EQUAL(v[0], 10.0f);
	BOOST_CHECK_EQUAL(v[1], 15.0f);
	BOOST_CHECK_EQUAL(v[2], 20.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointNegation)
{
	KM::Point v{1.0f, 2.0f, 3.0f};

	v = -v;

	BOOST_CHECK_EQUAL(v[0], -1.0f);
	BOOST_CHECK_EQUAL(v[1], -2.0f);
	BOOST_CHECK_EQUAL(v[2], -3.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);


	KM::Point v2 {3.0f, 5.0f};

	v2 = -v2;

	BOOST_CHECK_EQUAL(v2[0], -3.0f);
	BOOST_CHECK_EQUAL(v2[1], -5.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointPre_PostIncrement)
{
	KM::Point v {1.0f, 2.0f, 3.0f};

	++v;

	BOOST_CHECK_EQUAL(v[0], 2.0f);
	BOOST_CHECK_EQUAL(v[1], 3.0f);
	BOOST_CHECK_EQUAL(v[2], 4.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);

	v++;

	BOOST_CHECK_EQUAL(v[0], 3.0f);
	BOOST_CHECK_EQUAL(v[1], 4.0f);
	BOOST_CHECK_EQUAL(v[2], 5.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);

	KM::Point v2 {3.0f, 5.0f};

	++v2;

	BOOST_CHECK_EQUAL(v2[0], 4.0f);
	BOOST_CHECK_EQUAL(v2[1], 6.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);

	v2++;

	BOOST_CHECK_EQUAL(v2[0], 5.0f);
	BOOST_CHECK_EQUAL(v2[1], 7.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);
}

BOOST_AUTO_TEST_CASE(PointPre_PostDecrement)
{
	KM::Point v {10.0f, 20.0f, 30.0f};

	--v;

	BOOST_CHECK_EQUAL(v[0], 9.0f);
	BOOST_CHECK_EQUAL(v[1], 19.0f);
	BOOST_CHECK_EQUAL(v[2], 29.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);

	v--;

	BOOST_CHECK_EQUAL(v[0], 8.0f);
	BOOST_CHECK_EQUAL(v[1], 18.0f);
	BOOST_CHECK_EQUAL(v[2], 28.0f);
	BOOST_CHECK_EQUAL(v[3], 1.0f);

	KM::Point v2 {5.0f, 2.0f};

	--v2;

	BOOST_CHECK_EQUAL(v2[0], 4.0f);
	BOOST_CHECK_EQUAL(v2[1], 1.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);

	v2--;

	BOOST_CHECK_EQUAL(v2[0], 3.0f);
	BOOST_CHECK_EQUAL(v2[1], 0.0f);
	BOOST_CHECK_EQUAL(v2[2], 0.0f);
	BOOST_CHECK_EQUAL(v2[3], 1.0f);
}