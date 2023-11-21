#include "JEpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace JetEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case JetEngine::ShaderDataType::Float:		return GL_FLOAT;
			case JetEngine::ShaderDataType::Float2:		return GL_FLOAT;
			case JetEngine::ShaderDataType::Float3:		return GL_FLOAT;
			case JetEngine::ShaderDataType::Float4:		return GL_FLOAT;
			case JetEngine::ShaderDataType::Mat3:		return 3 * 3;
			case JetEngine::ShaderDataType::Mat4:		return 4 * 4;
			case JetEngine::ShaderDataType::Int:		return GL_INT;
			case JetEngine::ShaderDataType::Int2:		return GL_INT;
			case JetEngine::ShaderDataType::Int3:		return GL_INT;
			case JetEngine::ShaderDataType::Int4:		return GL_INT;
			case JetEngine::ShaderDataType::Bool:		return GL_BOOL;
		}

		JE_CORE_ASSERT(false, "Unknoiwn ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		JE_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		JE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		JE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		JE_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		JE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		JE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		JE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}