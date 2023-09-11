#pragma once

class Component {
private:
public:
	Component();
	~Component();

	virtual void Update(float deltaTime);
};