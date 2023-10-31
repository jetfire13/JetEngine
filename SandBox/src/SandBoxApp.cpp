#include "JetEngine.h"

#include "imgui/imgui.h"


class ExampleLayer : public JetEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(JetEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};


		std::shared_ptr<JetEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(JetEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		JetEngine::BufferLayout layout = {
			{ JetEngine::ShaderDataType::Float3, "a_Position" },
			{JetEngine::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<JetEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(JetEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(JetEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f, 0.5f, 0.0f,
			 -0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<JetEngine::VertexBuffer> squareVB;
		squareVB.reset(JetEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		JetEngine::BufferLayout squareVBlayout = {
			{ JetEngine::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<JetEngine::IndexBuffer> squareIB;
		squareIB.reset(JetEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}		
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}		
		)";

		m_Shader.reset(new JetEngine::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	

			out vec3 v_Position;

			uniform mat4 u_ViewProjectionMatrix;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}		
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}		
		)";

		m_BlueShader.reset(new JetEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
		
	}

	void OnUpdate(JetEngine::Timestep ts) override
	{
		if (JetEngine::Input::IsKeyPressed(JE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (JetEngine::Input::IsKeyPressed(JE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (JetEngine::Input::IsKeyPressed(JE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (JetEngine::Input::IsKeyPressed(JE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (JetEngine::Input::IsKeyPressed(JE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (JetEngine::Input::IsKeyPressed(JE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		JetEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		JetEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		JetEngine::Renderer::BeginScene(m_Camera);

		JetEngine::Renderer::Submit(m_BlueShader, m_SquareVA);

		JetEngine::Renderer::Submit(m_Shader, m_VertexArray);

		JetEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(JetEngine::Event& event) override
	{
		JetEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<JetEngine::KeyPressedEvent>(JE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	//Example
	bool OnKeyPressedEvent(JetEngine::KeyPressedEvent& event)
	{
		return false;
	}
	
private:
	std::shared_ptr<JetEngine::Shader> m_Shader;
	std::shared_ptr<JetEngine::VertexArray> m_VertexArray;

	std::shared_ptr<JetEngine::Shader> m_BlueShader;
	std::shared_ptr<JetEngine::VertexArray> m_SquareVA;

	JetEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;
};
class SandBox : public JetEngine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{
			
	}
};

JetEngine::Application* JetEngine::CreateApplication()
{
	return new SandBox();
}