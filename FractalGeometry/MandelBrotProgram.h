#pragma once
#include<glm/glm.hpp>
class MandelBrotProgram
{
public:
	void init(/*&_inputManager*/float w, float SW, float SH, int limit, glm::vec2 center, float odmakOdRuba);
	int getLimit() { return _limit; }
	glm::vec2 getUVMin() { return _uvMin; }
	glm::vec2 getUVMax() { return _uvMax; }
	void overlapCoordinatePlanes();
	float getW() { return _w; }
	void setW(float w) { _w = w; }
	glm::vec2 convertDisplayToComplexCoords(glm::vec2 displayCoords);
	glm::vec2 getCenter() { return _center; }
	void setCenter(glm::vec2 center) { _center = center; }
private:
	int _limit;
	glm::vec2 _uvMin, _uvMax, _center;
	float _w, _odmakOdRuba;
	float _SH, _SW;
};

