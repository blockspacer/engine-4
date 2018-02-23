#include "stdafx.h"
#include "shader_program.h"
#include "shader.h"
#include "qc_parser.h"

#include "glad/glad.h"
#include <assert_opengl.h>

shader_program::shader_program(const char * szFilename) :
	m_pShaderVert(NULL),
	m_pShaderFrag(NULL)
{
	RESTRICT_THREAD_RENDERING;
	mdlc::qc_parser parser(szFilename);
	
	
	if (parser.is_cmd("vertexshader") && parser.is_cmd("fragmentshader"))
	{
		PRINT_DBG("vertex and frag shader defined");
	}
	else
	{
		PRINT_ERR("Vertex and/or fragment shader missing from shader program!");
		return;
	}

	if (parser.is_cmd("name"))
	{
		strncpy(m_szName, parser.get_string("name").c_str(), 64);
	}
	else
	{
		PRINT_ERR("Shader has undefined name!");
		return;
	}
	if (parser.is_cmd("description"))
	{
		strncpy(m_szDescription, parser.get_string("description").c_str(), 128);
	}

	m_iID = glCreateProgram(); ASSERT_OPENGL();

	auto vert = parser.get_string("vertexshader");
	auto frag = parser.get_string("fragmentshader");

	m_pShaderVert = new shader(vert.c_str(), SHADER_T_VERTEX);
	ASSERT(m_pShaderVert);
	m_pShaderFrag = new shader(frag.c_str(), SHADER_T_FRAGMENT);
	ASSERT(m_pShaderFrag);

	glAttachShader(m_iID, m_pShaderVert->get_id());
	glAttachShader(m_iID, m_pShaderFrag->get_id());

	if (!link())
		return;

	if (parser.is_cmd("uniformtrans"))
	{
		m_iUniformMatTrans = glGetUniformLocation(m_iID, parser.get_string("uniformtrans").c_str());
		ASSERT(m_iUniformMatTrans != -1);
	}
	else
	{
		PRINT_ERR("uniformtrans undefined for shader " << m_szName);
		return;
	}

	if (parser.is_cmd("uniformview"))
	{
		auto lofasz = parser.get_string("uniformview");
		PRINT_DBG("uniform viewvar: " << lofasz);
		m_iUniformMatView = glGetUniformLocation(m_iID, lofasz.c_str());
		ASSERT(m_iUniformMatView != -1);
	}
	else
	{
		PRINT_ERR("uniformview undefined for shader " << m_szName);
		return;
	}

	if (parser.is_cmd("uniformproj"))
	{
		auto lofasz = parser.get_string("uniformproj");
		PRINT_DBG("uniform proj var: " << lofasz);
		m_iUniformMatProj = glGetUniformLocation(m_iID, lofasz.c_str());
		ASSERT(m_iUniformMatProj != -1);
	}
	else
	{
		PRINT_ERR("uniformproj undefined for shader " << m_szName);
		return;
	}
}

shader_program::~shader_program()
{
	RESTRICT_THREAD_RENDERING;
	if (m_pShaderVert)
	{
		glDetachShader(m_iID, m_pShaderVert->get_id());
		delete m_pShaderVert;
	}
	if (m_pShaderFrag)
	{
		glDetachShader(m_iID, m_pShaderFrag->get_id());
		delete m_pShaderFrag;
	}
}

bool shader_program::link()
{
	RESTRICT_THREAD_RENDERING;
	int iSuccess;
	glLinkProgram(m_iID); ASSERT_OPENGL();
	glGetProgramiv(m_iID, GL_LINK_STATUS, &iSuccess);
	if (!iSuccess)
	{
		print_err();
		return false;
	}
	validate();

	return true;
}

void shader_program::use()
{
	RESTRICT_THREAD_RENDERING;
	
	glUseProgram(m_iID); ASSERT_OPENGL();
}

void shader_program::validate()
{
	RESTRICT_THREAD_RENDERING;
	char szMsg[512];
	int iSuccess;
	glValidateProgram(m_iID);
	ASSERT_OPENGL();

	glGetProgramiv(m_iID, GL_VALIDATE_STATUS, &iSuccess);
	ASSERT_OPENGL();

	if (!iSuccess)
	{
		glGetProgramInfoLog(m_iID, 512, NULL, szMsg);
		PRINT_ERR("Shader program validation failed: " << szMsg);
		ASSERT(0);
	}
}

void shader_program::print_err()
{
	RESTRICT_THREAD_RENDERING;
	char szMsg[512];
	glGetProgramInfoLog(m_iID, 512, NULL, szMsg);
	PRINT_ERR("Shader program link failed: " << szMsg);
}

void shader_program::set_mat_trans(void * pMat)
{
	RESTRICT_THREAD_RENDERING;
	glUseProgram(m_iID); ASSERT_OPENGL();
	glUniformMatrix4fv(m_iUniformMatTrans, 1, GL_FALSE, (const GLfloat*)pMat);
	ASSERT_OPENGL();
}

void shader_program::set_mat_view(void * pMat)
{
	RESTRICT_THREAD_RENDERING;
	glUseProgram(m_iID); ASSERT_OPENGL();
	glUniformMatrix4fv(m_iUniformMatView, 1, GL_FALSE, (const GLfloat*)pMat);
	ASSERT_OPENGL();
}

void shader_program::set_mat_proj(void * pMat)
{
	RESTRICT_THREAD_RENDERING;
	glUseProgram(m_iID); ASSERT_OPENGL();
	glUniformMatrix4fv(m_iUniformMatProj, 1, GL_FALSE, (const GLfloat*)pMat);
	PRINT_DBG("set_mat_proj: " << m_iUniformMatProj);
	ASSERT_OPENGL();
}