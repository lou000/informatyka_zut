#pragma once
#include <cstdint>
#include "l_assert.h"

// becouse i hate std random generators
// this code is borrowed from OneLoneCoder
// https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/Videos/OneLoneCoder_PGE_ProcGen_Universe.cpp
// who in turn borrowed rnd function from https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/


static uint32_t ___seed = 1;

inline uint32_t rnd()
{
    ___seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)___seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

inline double rndDouble(double min, double max)
{
    return ((double)rnd() / (double)(0x7FFFFFFF)) * (max - min) + min;
}

inline int rndInt(int min, int max)
{
    if(max - min == 0) return min;
    return (rnd() % (max - min)) + min;
}

inline void rndSeed(uint32_t s)
{
    ___seed = s;
}
