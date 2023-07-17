#pragma once

#include "JetEngine/Renderer/Buffer.h"

namespace JetEngine {

	////////////////////////////////////////////////////////////////////////////
	//////////////////////////////VertexBuffer//////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const;
		virtual void Unbind() const;
	private:
		uint32_t m_RendererID;
	};


	////////////////////////////////////////////////////////////////////////////
	//////////////////////////////IndexBuffer///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}