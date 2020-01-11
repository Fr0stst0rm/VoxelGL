
#ifndef KD_TREE_H
#define KD_TREE_H

#include <stdint.h>
#include "Point.h"

namespace kd {
	class Node {
	public:
		Node();
		Node();
		~Node();

		void insertNode(Point p);

	private:
		Point m_point;
		uint8_t m_dimension = 3;
		Node* m_nodes;
	};

	class Tree {
	public:
		Tree(Point root);
		~Tree();

		void insertNode(Point p);
	private:
		Node* m_root;
	};
}

#endif // !KD_TREE_H
