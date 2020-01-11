#include "kdTree.h"

kd::Node::Node() : m_dimension()
{
	//x y z
	m_nodes = new Node[m_dimension];
}

kd::Node::~Node()
{
	delete[] m_nodes;
}

void kd::Node::insertNode(Point p)
{
	// x
	if () {

	// y
	} else if () {

	// z
	} else if () {

	}
}

kd::Tree::Tree(Point root)
{
	m_root = new Node(root);
}

kd::Tree::~Tree()
{
	delete m_root;
}

void kd::Tree::insertNode(Point p)
{
	m_root->insertNode(p);
}
