
#ifndef KD_TREE_H
#define KD_TREE_H

#include <stdint.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "Defines.h"

#include "MathDefines.h"
#include "Shader.h"

class KDTree {
public:
	KDTree();
	KDTree(std::vector<Vertex>& points);
	~KDTree();

	KDTree(const KDTree& rhs);
	KDTree& operator=(const KDTree& rhs);

	void insertNode(Vertex p);

	//bool intersect(const Ray& ray);
	//bool intersect(const Ray& ray, Intersection& is);

	std::size_t size() const;
	bool empty() const;

	bool contains(const Vertex& pt) const;

	void insert(const Vertex& pt);

	Vertex& operator[](const Vertex& pt);
	Vertex& at(const Vertex& pt);
	const Vertex& at(const Vertex& pt) const;
	//Vertex kNNValue(const Vertex& key, std::size_t k) const;


	std::size_t dimension() const;

	void drawWireframe(const Shader * shader);
private:

	struct Node {
		Vertex m_point;
		uint8_t m_axis;
		float m_cutingEdge;
		Node* m_left = nullptr;
		Node* m_right = nullptr;
		int m_level;  // level of the node in the tree, starts at 0 for the root
		Node(const Vertex& pt, int level) : m_point(pt), m_left(NULL), m_right(NULL), m_level(level){

		}
	};

	Node* m_root;
	std::size_t m_size;

	glm::vec3 m_minBound;
	glm::vec3 m_maxBound;

	int m_maxLevel = 0;

	const uint8_t m_dimension = 3;
	std::vector<glm::vec3> * m_TreeWires;
	
	Node* buildTree(typename std::vector<Vertex>::iterator start, typename std::vector<Vertex>::iterator end, int currLevel);
	Node* findNode(Node* currNode, const Vertex& pt) const;
	Node* deepcopyTree(Node* root);
	void freeResource(Node* currNode);

	void drawWireframeRecursive(const Shader * shader, glm::vec3 minBound, glm::vec3 maxBound, Node * root, int currLevel);

};


#endif // !KD_TREE_H
