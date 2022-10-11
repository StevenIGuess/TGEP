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
		OrthoCameraController(float aspectRatio, bool movement = false, bool rotation = false);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		void ResizeBounds(float width, float heigth);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }

		float GetZoom() const { return m_Zoom; }
		void SetZoom(float zoom) { m_Zoom = zoom; UpdateView(); }

		float GetMoveSpeed() const { return m_CameraMoveSpeed; }
		void SetMoveSpeed(float moveSpeed) { m_CameraMoveSpeed = moveSpeed; }

		glm::vec3 GetPosition() const { return m_CameraPosition; }
		void SetPosition(glm::vec3 pos) { m_CameraPosition = pos; }

	private:
		void UpdateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);

		float m_AspectRatio;
		float m_Zoom = 1.0f;
		OrthoCamera m_Camera;

		bool m_Rotation;
		bool m_Movement;

		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotSpeed = 1.0f;
	};
}