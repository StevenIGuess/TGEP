#include "pch.h"
#include "CameraController.h"
#include "Input.h"
#include "Events/KeyCodes.h"

namespace TGEP
{
	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom), m_Rotation(rotation)
	{

	}
	void OrthoCameraController::OnUpdate(DeltaTime dt)
	{
		if (Input::IsKeyPressed(TGEP_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * dt;
		} else if (Input::IsKeyPressed(TGEP_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * dt;
		}

		if (Input::IsKeyPressed(TGEP_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * dt;
		}else if (Input::IsKeyPressed(TGEP_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * dt;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(TGEP_KEY_Q))
			{
				m_CameraRotation += m_CameraMoveSpeed * dt;
			}
			if (Input::IsKeyPressed(TGEP_KEY_E))
			{
				m_CameraRotation -= m_CameraMoveSpeed * dt;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		
	}
	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(TGEP::OrthoCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNC(TGEP::OrthoCameraController::OnWindowResized));
	}
	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}
	bool OrthoCameraController::OnWindowResized(WindowResizedEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}
}
