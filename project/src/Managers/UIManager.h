#pragma once

class Player;

class UIManager {
private:
	inline static UIManager* mInstance;

	Player* mPlayerRef;

	UIManager();

public:

	void Init(Player* playerRef, GLFWwindow* windowRef);
	void Update();
	void Stop();

	static UIManager* GetInstance();

	UIManager(UIManager& other) = delete;
	void operator=(const UIManager&) = delete;
};