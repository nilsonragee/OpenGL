#include "GE_Timer.h"

bCTimer::bCTimer() noexcept
{
	last = steady_clock::now();
}

GEFloat bCTimer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration <GEFloat> frameTime = last - old;

	return frameTime.count();
}

GEFloat bCTimer::Peek() const noexcept
{
	return duration <GEFloat>(steady_clock::now() - last).count();
}