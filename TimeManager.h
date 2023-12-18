#pragma once
class TimeManager
{
	DECLARE_SINGLETON(TimeManager);

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }
	uint64 GetFrequency() { return _frequency; }
	uint64 GetCount() {	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));  return _prevCount; }

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.0f;

private:
	uint32 _frameCount = 0;
	float _frameTime = 0.0f;
	uint32 _fps = 0;
};

