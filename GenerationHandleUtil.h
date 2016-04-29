/*
	Copyright (c) 2016 Benjamin Han

	Permission is hereby granted, free of charge, to any person obtaining a copy of 
	this software and associated documentation files (the "Software"), to deal in the 
	Software without restriction, including without limitation the rights to use, copy, 
	modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
	and to permit persons to whom the Software is furnished to do so, subject to the 
	following conditions:

	The above copyright notice and this permission notice shall be included in all 
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	Benjamin Han
	acodersworld@gmail.com
*/

#pragma once

#include "include/SDL_stdinc.h"

typedef Uint32 GenHandle;
struct GenHandleUtil
{
	enum
	{
		N_generation = 19,
		GENERATION_MASK = ~((Uint32)-1 << N_generation),
		INVALID_HANDLE = -1,
		MAX_INDEX = (Uint32)-1 >> N_generation
	};

	static bool isValid( GenHandle h )
	{
		return INVALID_HANDLE != h;
	}

	static bool isInvalid( GenHandle h )
	{
		return INVALID_HANDLE == h;
	}

	static Uint32 nextGeneration( Uint32 generation )
	{
		return (generation + 1) & GENERATION_MASK;
	}

	static Uint32 updateIndex( Uint32 handle, Uint32 index )
	{
		handle &= GENERATION_MASK;
		handle |= ( index << N_generation );
		return handle;
	}

	static Uint32 extractIndex( Uint32 handle )
	{
		return handle >> N_generation;
	}

	static Uint32 composeHandle( Uint32 index, Uint32 generation )
	{
		Uint32 handle;
		handle = generation & GENERATION_MASK;
		handle |= ( index << N_generation );
		return handle;
	}

	struct Decomposed
	{
		Uint32 index;
		Uint32 generation;
	};

	static Decomposed decomposeHandle( Uint32 handle )
	{
		Decomposed output;
		output.generation = handle & GENERATION_MASK;
		output.index = handle >> N_generation;
		return output;
	}

};
