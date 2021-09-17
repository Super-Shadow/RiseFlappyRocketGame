#pragma once

#include "Rise/Layer.h"

#include "Rise/Events/MouseEvent.h"
#include "Rise/Events/ApplicationEvent.h"
#include "Rise/Events/KeyEvent.h"

namespace Rise
{
	class RISE_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:

		float m_Time = 0.0f;
	};
}
