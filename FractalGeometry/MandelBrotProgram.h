#pragma once
#include<glm/glm.hpp>
#include <iostream>
#define LIMIT 32
class MandelBrotProgram
{
public:
	void init(float w, float SW, float SH, int limit, glm::vec2 center, float odmakOdRuba);
	int getLimit() { return _limit; }
	void setLimit(int newLimit);

	glm::vec2 getUVMin() { return _uvMin; }
	glm::vec2 getUVMax() { return _uvMax; }

	void overlapCoordinatePlanes();

	float getW() { return _w; }
	void setW(float newW);

	glm::vec2 convertDisplayToComplexCoords(glm::vec2 displayCoords);

	glm::vec2 getCenter() { return _center; }
	void setCenter(glm::vec2 center) { _center = center; }

	int getScrollCounter() { return _zoomCnt; }
	int getAndIncrementScrollCounter() { return ++_zoomCnt; }
	int getAndDecrementScrollCounter();
	
	float getStartingW() { return _startingW; }

	/// <summary>Function: 1/x^n. It is particullarly useful in zooming mandelbrot. Forward your counter with how much did you zoom currently.
	/// As you go deeper, this function returns smaller values. Those values are used in camera translation or increment of your current zoom
	/// 
	/// steep parameter is in this case "x". As x get larger, function gets steeper, faster to zero, which means faster zooming.
	/// Tweak these parameters carefully. For each functionality, you have to tweek them accordingly. Until better solution is found.
	/// </summary>
	long double ExponentialMultiplicativeInverse(float startingY, float steep, int zoomLevel = -1);
private:
	/// <summary>Limit value for number of iterations to find iteration where complex number diverged out of mandelbrot set (radius = 2)</summary>
	int _limit;
	/// <summary>Cooridnate planes needs to be aligned with screen. Uvmin and UvMax helps with that and center is place where camera is watching</summary>
	glm::vec2 _uvMin, _uvMax, _center;
	/// <summary>Zoom property which is used in calcualting uv min and max cooridnate plane.</summary>
	float _w, _startingW;
	float _SH, _SW, _odmakOdRuba;
	int _zoomCnt;
};

