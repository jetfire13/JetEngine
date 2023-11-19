#pragma once

#include "JetEngine/Core/Layer.h"

#include "JetEngine/Events/KeyEvent.h"
#include "JetEngine/Events/MouseEvent.h"
#include "JetEngine/Events/ApplicationEvent.h"

namespace JetEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}