/*------------------------------------------------------------
Tests the AudioListener, a wrapper to move the listener object of the OpenAL
context.

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
#include <Engine/AudioListener.h>

namespace KE = KillerEngine;

BOOST_AUTO_TEST_CASE(AudioListnerConstructor)
{
	KE::AudioListener listener { };

	const F32* orientation = listener.GetOrientation();

	BOOST_CHECK_EQUAL(orientation[0], 0.0f);
	BOOST_CHECK_EQUAL(orientation[1], 0.0f);
	BOOST_CHECK_EQUAL(orientation[2], 1.0f);
	BOOST_CHECK_EQUAL(orientation[3], 0.0f);
	BOOST_CHECK_EQUAL(orientation[4], 1.0f);
	BOOST_CHECK_EQUAL(orientation[5], 0.0f);
	BOOST_CHECK_EQUAL(listener.GetPosition()[x], 0.0f);
	BOOST_CHECK_EQUAL(listener.GetPosition()[y], 0.0f);
	BOOST_CHECK_EQUAL(listener.GetPosition()[z], 1.0f);
	BOOST_CHECK_EQUAL(listener.GetVelocity()[x], 0.0f);
	BOOST_CHECK_EQUAL(listener.GetVelocity()[y], 0.0f);
	BOOST_CHECK_EQUAL(listener.GetVelocity()[z], 0.0f);
}

BOOST_AUTO_TEST_CASE(AudioListenerAccessors)
{
	KE::AudioListener listener { };

	//Orientation
	F32 newOrientation[6] = { 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f };

	listener.SetOrientation(newOrientation);

	const F32* orientation = listener.GetOrientation();

	BOOST_CHECK_EQUAL(orientation[0], 1.0f);
	BOOST_CHECK_EQUAL(orientation[1], 1.0f);
	BOOST_CHECK_EQUAL(orientation[2], 0.0f);
	BOOST_CHECK_EQUAL(orientation[3], 1.0f);
	BOOST_CHECK_EQUAL(orientation[4], 0.0f);
	BOOST_CHECK_EQUAL(orientation[5], 1.0f);

	F32* orienationCheck = new F32;

	alGetListenerfv(AL_ORIENTATION, orienationCheck);

	BOOST_CHECK_EQUAL(orienationCheck[0], 1.0f);
	BOOST_CHECK_EQUAL(orienationCheck[1], 1.0f);
	BOOST_CHECK_EQUAL(orienationCheck[2], 0.0f);
	BOOST_CHECK_EQUAL(orienationCheck[3], 1.0f);
	BOOST_CHECK_EQUAL(orienationCheck[4], 0.0f);
	BOOST_CHECK_EQUAL(orienationCheck[5], 1.0f);

	orienationCheck = nullptr;
	delete orienationCheck;

	//Position
	listener.SetPosition(1.0f, 2.0f, 3.0f);

	BOOST_CHECK_EQUAL(listener.GetPosition()[x], 1.0f);
	BOOST_CHECK_EQUAL(listener.GetPosition()[y], 2.0f);
	BOOST_CHECK_EQUAL(listener.GetPosition()[z], 3.0f);

	F32 xPos, yPos, zPos;

	alGetListener3f(AL_POSITION, &xPos, &yPos, &zPos);

	BOOST_CHECK_EQUAL(xPos, 1.0f);
	BOOST_CHECK_EQUAL(yPos, 2.0f);
	BOOST_CHECK_EQUAL(zPos, 3.0f);

	//Velocity
	listener.SetVelocity(8.0f, 9.0f, 10.0f);

	BOOST_CHECK_EQUAL(listener.GetVelocity()[x], 8.0f);
	BOOST_CHECK_EQUAL(listener.GetVelocity()[y], 9.0f);
	BOOST_CHECK_EQUAL(listener.GetVelocity()[z], 10.0f);

	F32 xVel, yVel, zVel;

	alGetListener3f(AL_VELOCITY, &xVel, &yVel, &zVel);

	BOOST_CHECK_EQUAL(xVel, 8.0f);
	BOOST_CHECK_EQUAL(yVel, 9.0f);
	BOOST_CHECK_EQUAL(zVel, 10.0f);
}