#pragma once
#include "Layer.h"

namespace Rise
{

	class RISE_API LayerStack
	{
	public:
		LayerStack() = default;

		LayerStack(const LayerStack&) = delete;
		LayerStack& operator= (const LayerStack&) = delete;

		LayerStack(LayerStack&&) = delete;
		LayerStack& operator=(LayerStack&&) = delete;

		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}
