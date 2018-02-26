

class Node
{
	//Node();
	virtual ~Node() = 0;
	virtual Calculate() = 0;
}

inline Node::~Node(){}

template <class T>
class OperatorNode: public Node
{
	OperatorNode()
	//virtual ~OperatorNode();
	virtual Calculate();
}

