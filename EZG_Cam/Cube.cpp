#include <GL/glew.h>
#include "Cube.h"

Cube::Cube()
{
	//Reset all render sides to true
	memset(&m_settings, 0xff, sizeof(m_settings));
	m_settings.glow = false;
	m_settings.transparent = false;

	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	// front face
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	// left face
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// right face
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	// bottom face
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	// top face
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	m_Vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
}

Cube::~Cube()
{
}

void Cube::createMesh() {
	createCubeMesh();
}

bool Cube::isTopRendered() {
	return m_settings.top;
}

bool Cube::isBottomRendered() {
	return m_settings.bottom;
}

bool Cube::isLeftRendered() {
	return m_settings.left;
}

bool Cube::isRightRendered() {
	return m_settings.right;
}

bool Cube::isFrontRendered() {
	return m_settings.front;
}

bool Cube::isBackRendered() {
	return m_settings.back;
}

void Cube::setTopRendered(bool b) {
	m_settings.top = b;
}
void Cube::setBottomRendered(bool b) {
	m_settings.bottom = b;
}

void Cube::setLeftRendered(bool b) {
	m_settings.left = b;
}

void Cube::setRightRendered(bool b) {
	m_settings.right = b;
}

void Cube::setFrontRendered(bool b) {
	m_settings.front = b;
}

void Cube::setBackRendered(bool b) {
	m_settings.back = b;
}

void Cube::createCubeMesh()
{
	glScalef(0.9999, 0.9999, 0.9999);
	
	// initialize (if necessary)
	if (objVAO == 0)
	{
		float vertices[] = {
			// back face
			m_Vertices[0].x, m_Vertices[0].y, m_Vertices[0].z,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			m_Vertices[1].x, m_Vertices[1].y, m_Vertices[1].z,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			m_Vertices[2].x, m_Vertices[2].y, m_Vertices[2].z,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			m_Vertices[3].x, m_Vertices[3].y, m_Vertices[3].z,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			m_Vertices[4].x, m_Vertices[4].y, m_Vertices[4].z,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			m_Vertices[5].x, m_Vertices[5].y, m_Vertices[5].z,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			m_Vertices[6].x, m_Vertices[6].y, m_Vertices[6].z,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			m_Vertices[7].x, m_Vertices[7].y, m_Vertices[7].z,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			m_Vertices[8].x, m_Vertices[8].y, m_Vertices[8].z,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			m_Vertices[9].x, m_Vertices[9].y, m_Vertices[9].z,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			m_Vertices[10].x, m_Vertices[10].y, m_Vertices[10].z,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			m_Vertices[11].x, m_Vertices[11].y, m_Vertices[11].z,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			m_Vertices[12].x, m_Vertices[12].y, m_Vertices[12].z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			m_Vertices[13].x, m_Vertices[13].y, m_Vertices[13].z, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			m_Vertices[14].x, m_Vertices[14].y, m_Vertices[14].z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			m_Vertices[15].x, m_Vertices[15].y, m_Vertices[15].z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			m_Vertices[16].x, m_Vertices[16].y, m_Vertices[16].z, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			m_Vertices[17].x, m_Vertices[17].y, m_Vertices[17].z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			m_Vertices[18].x, m_Vertices[18].y, m_Vertices[18].z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			m_Vertices[19].x, m_Vertices[19].y, m_Vertices[19].z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			m_Vertices[20].x, m_Vertices[20].y, m_Vertices[20].z,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
			m_Vertices[21].x, m_Vertices[21].y, m_Vertices[21].z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			m_Vertices[22].x, m_Vertices[22].y, m_Vertices[22].z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			m_Vertices[23].x, m_Vertices[23].y, m_Vertices[23].z,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
			// bottom face
			m_Vertices[24].x, m_Vertices[24].y, m_Vertices[24].z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			m_Vertices[25].x, m_Vertices[25].y, m_Vertices[25].z,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			m_Vertices[26].x, m_Vertices[26].y, m_Vertices[26].z,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			m_Vertices[27].x, m_Vertices[27].y, m_Vertices[27].z,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			m_Vertices[28].x, m_Vertices[28].y, m_Vertices[28].z,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			m_Vertices[29].x, m_Vertices[29].y, m_Vertices[29].z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			m_Vertices[30].x, m_Vertices[30].y, m_Vertices[30].z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			m_Vertices[31].x, m_Vertices[31].y, m_Vertices[31].z,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			m_Vertices[32].x, m_Vertices[32].y, m_Vertices[32].z,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
			m_Vertices[33].x, m_Vertices[33].y, m_Vertices[33].z,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			m_Vertices[34].x, m_Vertices[34].y, m_Vertices[34].z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			m_Vertices[35].x, m_Vertices[35].y, m_Vertices[35].z,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
		};

		glGenVertexArrays(1, &objVAO);
		glGenBuffers(1, &objVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, objVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(objVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// render Cube
	glBindVertexArray(objVAO);
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
	glBindVertexArray(0);
	
	/* TODO
	if (isFrontRendered()) {
		
	}
	
	if (isBackRendered()) {
		
	}

	if (isTopRendered()) {
		
	}

	if (isBottomRendered()) {
		
	}

	if (isLeftRendered()) {
		
	}

	if (isRightRendered()) {
		
	}
	*/
}

bool Cube::isTransparent()
{
	return m_settings.transparent;
}

bool Cube::isGlowing()
{
	return m_settings.glow;
}

std::vector<Vertex> Cube::GetVertices(GLuint id, glm::mat4 model)
{
	std::vector<Vertex> verts = std::vector<Vertex>();

		for (int i = 0; i < m_Vertices.size(); i++) {

			Vertex vertex;
			vertex.x = m_Vertices[i].x;
			vertex.y = m_Vertices[i].y;
			vertex.z = m_Vertices[i].z;
			
			glm::vec4 pos = glm::vec4(vertex.x, vertex.y, vertex.z, 1);
			//std::cout << "x: " << pos.x << "\n";
			//std::cout << "y: " << pos.y << "\n";
			//std::cout << "z: " << pos.z << "\n";
			//std::cout << "w: " << pos.w << "\n";

			glm::vec3 vert3 = model * pos;

			//std::cout << "x: " << vert3.x << "\n";
			//std::cout << "y: " << vert3.y << "\n";
			//std::cout << "z: " << vert3.z << "\n";

			Vertex v;
			v.x = vert3.x;
			v.y = vert3.y;
			v.z = vert3.z;


			v.objID = id;

			verts.push_back(v);
		}


	return verts;
}
