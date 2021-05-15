#pragma once
#include<glm/glm.hpp>
#include <iostream>
#define LIMIT 32
class MandelBrotProgram
{
public:
	void init(/*&_inputManager*/float w, float SW, float SH, int limit, glm::vec2 center, float odmakOdRuba);
	int getLimit() { return _limit; }
	void setLimit(int newLimit) {
		if (newLimit >= LIMIT) {
			_limit = newLimit;
		}
	}
	glm::vec2 getUVMin() { return _uvMin; }
	glm::vec2 getUVMax() { return _uvMax; }
	void overlapCoordinatePlanes();
	float getW() { return _w; }
	void setW(float newW) { 
		if (newW <= _startingW)
			_w = newW;
		else
			std::cout << "do nothing, newW is " << newW << std::endl;
	}
	glm::vec2 convertDisplayToComplexCoords(glm::vec2 displayCoords);
	glm::vec2 getCenter() { return _center; }
	void setCenter(glm::vec2 center) { _center = center; }

	int getScrollCounter() { return _cnt; }
	int getAndIncrementScrollCounter() { return ++_cnt; }
	int getAndDecrementScrollCounter() {
		int cntCalculated = _cnt - 1;
		if (_cnt - 1 >= 0) {
			_cnt--;
			return _cnt;
		}
		return 0; 
	}
	float getStartingW() { return _startingW; }
private:
	int _limit;
	glm::vec2 _uvMin, _uvMax, _center;
	float _startingW;
	float _w, _odmakOdRuba;
	float _SH, _SW;
	int _cnt = 0;
};

