#pragma once

//¼ÓÔØÊ±¼ä
inline bool LoadTime(int time)
{
	static float gLoadBeginTime, gLoadEndTime;
	gLoadEndTime = 0;
	gLoadBeginTime = GetTickCount();
	if (gLoadEndTime == 0)
		gLoadEndTime = gLoadBeginTime;
	if (gLoadBeginTime - gLoadEndTime >= time)
	{
		return false;
	}
	return true;
}


