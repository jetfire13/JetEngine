#include <JetEngine.h>
#include <JetEngine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"


class ExampleLayer : public JetEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = JetEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};


		JetEngine::Ref<JetEngine::VertexBuffer> vertexBuffer;
		vertexBuffer = JetEngine::VertexBuffer::Create(vertices, sizeof(vertices));

		JetEngine::BufferLayout layout = {
			{ JetEngine::ShaderDataType::Float3, "a_Position" },
			{JetEngine::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		JetEngine::Ref<JetEngine::IndexBuffer> indexBuffer;
		indexBuffer = JetEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = JetEngine::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		JetEngine::Ref<JetEngine::VertexBuffer> squareVB;
		squareVB = JetEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		JetEngine::BufferLayout squareVBlayout = {
			{ JetEngine::ShaderDataType::Float3, "a_Position" },
			{ JetEngine::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		JetEngine::Ref<JetEngine::IndexBuffer> squareIB;
		squareIB = JetEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = JetEngine::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	

			out vec3 v_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}		
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}		
		)";

		m_FlatColorShader = JetEngine::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = JetEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureLogo = JetEngine::Texture2D::Create("assets/textures/SomeLogo.png");

		std::dynamic_pointer_cast<JetEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<JetEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(JetEngine::Timestep ts) override
	{		
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		JetEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		JetEngine::RenderCommand::Clear();

		JetEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		std::dynamic_pointer_cast<JetEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<JetEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				JetEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		JetEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TextureLogo->Bind();
		JetEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// JetEngine::Renderer::Submit(m_Shader, m_VertexArray);
 
		JetEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(JetEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	//Example
	bool OnKeyPressedEvent(JetEngine::KeyPressedEvent& event)
	{
		return false;
	}
	
private:
	JetEngine::ShaderLibrary m_ShaderLibrary;
	JetEngine::Ref<JetEngine::Shader> m_Shader;
	JetEngine::Ref<JetEngine::VertexArray> m_VertexArray;

	JetEngine::Ref<JetEngine::Shader> m_FlatColorShader;
	JetEngine::Ref<JetEngine::VertexArray> m_SquareVA;

	JetEngine::Ref<JetEngine::Texture2D> m_Texture, m_TextureLogo;

	JetEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class SandBox : public JetEngine::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~SandBox()
	{
			
	}
};

JetEngine::Application* JetEngine::CreateApplication()
{
	return new SandBox();
}