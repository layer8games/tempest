/*========================================================================
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

This is not free to use, and cannot be used without the express permission
of Layer 8 Games.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/Quaternion.h>

namespace KillerMath
{
    /**
     * Keeps track of one random stream: i.e. a seed and its output.
     * This is used to get random numbers. Rather than a funcion, this
     * allows there to be several streams of repeatable random numbers
     * at the same time. Uses the RandRotB algorithm.
     */
    class Random
    {
    public:
    	/**
    	 * left bitwise rotation
    	 */

    	unsigned rotl(unsigned n, unsigned r);
    	/**
    	 * right bitwise rotation
    	 */
    	unsigned rotr(unsigned n, unsigned r);

        /**
         * Creates a new random number stream with a seed based on
         * timing data.
         */
        Random();

        /**
         * Creates a new random stream with the given seed.
         */
        explicit Random(unsigned seed);

        static shared_ptr<Random> Instance(void);

        /**
         * Sets the seed value for the random stream.
         */
        void Seed(unsigned seed);

        /**
         * Returns the next random bitstring from the stream. This is
         * the fastest method.
         */
        unsigned RandomBits();

        /**
         * Returns a random floating point number between 0 and 1.
         */
        real RandomReal();

        /**
         * Returns a random floating point number between 0 and scale.
         */
        real RandomReal(real scale);

        /**
         * Returns a random floating point number between min and max.
         */
        real RandomReal(real min, real max);

        /**
         * Returns a random integer less than the given value.
         */
        unsigned RandomInt(unsigned max);

        /**
         * Returns a random binomially distributed number between -scale
         * and +scale.
         */
        real RandomBinomial(real scale);

        /**
         * Returns a random vector where each component is binomially
         * distributed in the range (-scale to scale) [mean = 0.0f].
         */
        Vector3& RandomVector3(real scale);

        Vector2& RandomVector2(real scale);

        /**
         * Returns a random vector where each component is binomially
         * distributed in the range (-scale to scale) [mean = 0.0f],
         * where scale is the corresponding component of the given
         * vector.
         */
        Vector3& RandomVector3(const Vector3& scale);

        Vector2& RandomVector2(const Vector2& scale);

        /**
         * Returns a random vector in the cube defined by the given
         * minimum and maximum vectors. The probability is uniformly
         * distributed in this region.
         */
        Vector3& RandomVector3(const Vector3& min, const Vector3& max);

        Vector2& RandomVector2(const Vector2& min, const Vector2& max);

        /**
         * Returns a random vector where each component is binomially
         * distributed in the range (-scale to scale) [mean = 0.0f],
         * except the y coordinate which is zero.
         */
        Vector3& RandomXZVector3(real scale);

        /**
         * Returns a random orientation (i.e. normalized) quaternion.
         */
        Quaternion& RandomQuaternion();

    private:
        // Internal mechanics
        int p1, p2;
        unsigned buffer[17];
        static shared_ptr<Random> _instance;
    };

} // namespace KillerMath