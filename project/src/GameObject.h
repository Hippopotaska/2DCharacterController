#pragma once

#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject {
private:
	std::vector<Component*> mComponents{};

public:
	Transform* transform;

	virtual void Update(float deltaTime) {
		for (auto& component : mComponents) {
			if (component)
				component->Update(deltaTime);
		}
	}

	template<typename T>
	inline void AddComponent(T* newComp) {
		mComponents.push_back(newComp);
	}

	template<typename T>
	inline T* GetComponent() {
		for (auto& component : mComponents) {
			T* tempComp = dynamic_cast<T*>(component);
			if (tempComp != nullptr)
				return tempComp;
		}
		return nullptr;
	}
};