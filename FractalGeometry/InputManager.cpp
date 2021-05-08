#include "InputManager.h"

InputManager::InputManager() {
	_mouseCoords.x = 0;
	_mouseCoords.y = 0;
}
InputManager::~InputManager() {

}
void InputManager::update() {

	for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
		_previouskeyMap[it->first] = it->second;
	}
}
void InputManager::keyPressed(unsigned int keyID) {
	_keyMap[keyID] = true;
}
void InputManager::keyRelease(unsigned int keyID) {
	_keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int  keyID) {

	auto it = _keyMap.find(keyID);
	if (it == _keyMap.end()) {
		return false;
	}
	else {
		return it->second;
	}
}
bool InputManager::isKeyPressed(unsigned int  keyID) {

	if (isKeyDown(keyID) && wasKeyDown(keyID) == false) {
		return true;
	}
	return false;

}
bool InputManager::wasKeyDown(unsigned int  keyID) {

	auto it = _previouskeyMap.find(keyID);
	if (it == _previouskeyMap.end()) {
		return false;
	}
	else {
		return it->second;
	}
}
void InputManager::setMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}
glm::vec2 InputManager::getMouseCoords() {
	return _mouseCoords;
}