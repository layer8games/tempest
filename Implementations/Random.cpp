/*
 * Implementation file for random number generation.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 The MIT License

Copyright (c) 2003-2009 Ian Millington

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <cstdlib>
#include <ctime>
#include <Engine/Random.h>

using namespace KillerMath;

shared_ptr<Random> Random::_instance = NULL;

Random::Random()
{
    Seed(0);
}

Random::Random(unsigned seed)
{
    Random::Seed(seed);
}

shared_ptr<Random> Random::Instance(void)
{
	if(_instance == NULL)
	{
		_instance = shared_ptr<Random>(new Random());
	}

	return _instance;
}

void Random::Seed(unsigned s)
{
    if (s == 0) {
        s = (unsigned)clock();
    }

    // Fill the buffer with some basic random numbers
    for (unsigned i = 0; i < 17; i++)
    {
        // Simple linear congruential generator
        s = s * 2891336453 + 1;
        buffer[i] = s;
    }

    // Initialize pointers into the buffer
    p1 = 0;  p2 = 10;
}

unsigned Random::rotl(unsigned n, unsigned r)
{
	  return	(n << r) |
			  (n >> (32 - r));
}

unsigned Random::rotr(unsigned n, unsigned r)
{
	  return	(n >> r) |
				(n << (32 - r));
}

unsigned Random::RandomBits()
{
    unsigned result;

    // Rotate the buffer and store it back to itself
    result = buffer[p1] = rotl(buffer[p2], 13) + rotl(buffer[p1], 9);

    // Rotate pointers
    if (--p1 < 0) p1 = 16;
    if (--p2 < 0) p2 = 16;

    // Return result
    return result;
}

#ifdef SINGLE_PRECISION
real Random::RandomReal()
{
    // Get the random number
    unsigned bits = RandomBits();

    // Set up a reinterpret structure for manipulation
    union {
        real value;
        unsigned word;
    } convert;

    // Now assign the bits to the word. This works by fixing the ieee
    // sign and exponent bits (so that the size of the result is 1-2)
    // and using the bits to create the fraction part of the float.
    convert.word = (bits >> 9) | 0x3f800000;

    // And return the value
    return convert.value - 1.0f;
}
#else
real Random::RandomReal()
{
    // Get the random number
    unsigned bits = RandomBits();

    // Set up a reinterpret structure for manipulation
    union {
        real value;
        unsigned words[2];
    } convert;

    // Now assign the bits to the words. This works by fixing the ieee
    // sign and exponent bits (so that the size of the result is 1-2)
    // and using the bits to create the fraction part of the float. Note
    // that bits are used more than once in this process.
    convert.words[0] =  bits << 20; // Fill in the top 16 bits
    convert.words[1] = (bits >> 12) | 0x3FF00000; // And the bottom 20

    // And return the value
    return convert.value - 1.0;
}
#endif

real Random::RandomReal(real min, real max)
{
    return RandomReal() * (max-min) + min;
}

real Random::RandomReal(real scale)
{
    return RandomReal() * scale;
}

unsigned Random::RandomInt(unsigned max)
{
    return RandomBits() % max;
}

real Random::RandomBinomial(real scale)
{
    return (RandomReal()-RandomReal())*scale;
}

Vector3& Random::RandomVector3(real scale)
{
    return Vector3(
        RandomBinomial(scale),
        RandomBinomial(scale),
        RandomBinomial(scale)
        );
}

Vector2& Random::RandomVector2(real scale)
{
    return Vector2(
        RandomBinomial(scale),
        RandomBinomial(scale)
        );
}

Vector3& Random::RandomVector3(const Vector3 &scale)
{
    return Vector3(
        RandomBinomial(scale.GetX()),
        RandomBinomial(scale.GetY()),
        RandomBinomial(scale.GetZ())
        );
}

Vector2& Random::RandomVector2(const Vector2 &scale)
{
    return Vector2(
        RandomBinomial(scale.GetX()),
        RandomBinomial(scale.GetY())
        );
}

Vector3& Random::RandomVector3(const Vector3 &min, const Vector3 &max)
{
    return Vector3(
        RandomReal(min.GetX(), max.GetX()),
        RandomReal(min.GetY(), max.GetY()),
        RandomReal(min.GetZ(), max.GetZ())
        );
}

Vector2& Random::RandomVector2(const Vector2 &min, const Vector2 &max)
{
    return Vector2(
        RandomReal(min.GetX(), max.GetX()),
        RandomReal(min.GetY(), max.GetY())
        );
}

Vector3& Random::RandomXZVector3(real scale)
{
    return Vector3(
        RandomBinomial(scale),
        0,
        RandomBinomial(scale)
        );
}

Quaternion& Random::RandomQuaternion()
{
    Quaternion q(
        RandomReal(),
        RandomReal(),
        RandomReal(),
        RandomReal()
        );
    q.Normalise();
    return q;
}