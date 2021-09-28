#pragma once
#include "Core/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Renderer/OrthographicCamera.h"

namespace Rise
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool bRotation = false);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		[[nodiscard]] const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(const MouseScrolledEvent& e);
		bool OnWindowResized(const WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition{0.0f};
		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 100.0f;
	};
}
