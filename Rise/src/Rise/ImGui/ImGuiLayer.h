#pragma once

#include "Rise/Core/Layer.h"

#include "Rise/Events/MouseEvent.h"
#include "Rise/Events/ApplicationEvent.h"
#include "Rise/Events/KeyEvent.h"

namespace Rise
{
	class RISE_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};
}
