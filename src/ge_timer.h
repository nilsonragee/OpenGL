#pragma once
#include <chrono>
#include "ge_types.h"
using namespace std::chrono;

class bCTimer
{
public:
	bCTimer() noexcept;
	GEFloat Mark() noexcept;
	GEFloat Peek() const noexcept;

private:
	std::chrono::steady_clock::time_point last;
};
