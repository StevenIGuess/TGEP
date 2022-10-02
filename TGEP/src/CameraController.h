#pragma once
#include "Renderer/Camera.h"
#include "DeltaTime.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace TGEP
{
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);

		float m_AspectRatio;
		float m_Zoom = 1.0f;
		OrthoCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotSpeed = 1.0f;
	};
}