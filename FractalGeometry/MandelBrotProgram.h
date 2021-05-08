#pragma once
#include<glm/glm.hpp>
class MandelBrotProgram
{
public:
	void init(/*&_inputManager*/float w, int SW, int SH, int limit, glm::vec2 center, float odmakOdRuba);
	int getLimit() { return _limit; }
	glm::vec2 getUVMin() { return _uvMin; }
	glm::vec2 getUVMax() { return _uvMax; }
	void prepareOverlapingCoordinatePlanes();
private:
	int _limit;
	glm::vec2 _uvMin, _uvMax, _center;
	float _w, _odmakOdRuba;
	int _SH, _SW;
};

