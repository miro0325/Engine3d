#include "framework.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;
	_frameCount++;

	_frameTime += _deltaTime;

	if (_frameTime >= 1.0f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);
		_frameCount = 0;
		_frameTime = 0;
	}
}

