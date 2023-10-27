#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "UIManager.h"
#include "Player.h"

#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

UIManager::UIManager() 
	: mPlayerRef(nullptr) {}

void UIManager::Init(Player* playerRef, GLFWwindow* windowRef) {
	mPlayerRef = playerRef;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(windowRef, true);
	ImGui_ImplOpenGL3_Init();
}

void UIManager::Update() {
	// ImGui create new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGui window settings
	ImGui::Begin("Character Settings");
	ImGui::Text("Hello user!\nMovement values are represented in game units (1 unit = 100 pixels)\nTimers are in seconds.");
	ImGui::Spacing();

	ImGui::Text("- Vertical Movement -");
	ImGui::SliderFloat("Max Jump Height", &mPlayerRef->maxJumpHeight, 0.f, 10.f);
	ImGui::SliderFloat("Max Fall Velocity", &mPlayerRef->maxFall, -25.f, -1.f);
	ImGui::SliderFloat("Variable Jump Multiplier", &mPlayerRef->variableJumpMult, 0.f, 1.f);
	ImGui::Spacing();
	ImGui::SliderFloat("Jump Duration", &mPlayerRef->jumpDuration, 0.f, 5.f);
	ImGui::SliderFloat("Coyote Time", &mPlayerRef->coyoteTime, 0.f, 5.f);
	ImGui::SliderFloat("Jump Buffer Time", &mPlayerRef->jumpBufferTime, 0.f, 5.f);

	ImGui::Text("- Horizontal Movement -");
	ImGui::SliderFloat("Move Speed", &mPlayerRef->moveSpeed, 0.f, 100.0f);
	ImGui::SliderFloat("Max Movement Velocity", &mPlayerRef->maxMoveVelocity, 0.f, 15.f);
	ImGui::Spacing();
	ImGui::SliderFloat("Friction", &mPlayerRef->friction, 0.f, 100.f);
	ImGui::SliderFloat("Air Friction", &mPlayerRef->airFriction, 0.f, 100.f);
	ImGui::SliderFloat("Air Control Multiplier", &mPlayerRef->airControlMult, 0.f, 1.f);

	ImGui::End();

	// ImGui rendering things
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	mPlayerRef->CalcGravityAndJumpPower();
}

void UIManager::Stop() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

UIManager* UIManager::GetInstance() {
	if (!mInstance)
		mInstance = new UIManager();
	return mInstance;
}