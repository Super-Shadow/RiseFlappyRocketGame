#pragma once

#include "Rise/Core/Layer.h"

namespace Rise
{
	class RISE_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();
	};
}
