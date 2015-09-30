#include "Node.h"

const std::string Node::labelArray ="abcdefghijklmnopqrstuvwxyz";
const uint Node::ioArray[4] = {1, 8, 16, 32};
std::vector<Node*> Node::NodeDataBase;
std::vector<Node*> Node::IpTypeSortedNodes[4];

Node::Node()
{

}

Node::Node(const std::string label1 ,const std::string type, uint input = 0, uint output = 0, uint indeg = 0, uint outdeg = 0)
: label(label1),nodeType(type)  ,inputType(input) , outputType(output), inDegree(indeg),
outDegree(outdeg), inDegreeMAX(MAX_POSSIBLE_NODES), outDegreeMAX(MAX_POSSIBLE_NODES) // Just for a high integer
{
}

Node::Node(Node* n)
{

    *this = n;

}

Node& Node::operator=(const Node& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


Node::~Node()
{

    //dtor
}


/************** GET and SET METHODS ***************/
/*************************************************/

/* To get the label */
/* Called from the node object */
std::string Node::getLabel()
{
    return label;
}

/* Get Node Type*/
std::string Node::getNodeType()
{
    return nodeType;
}
/*To get Input Type */

uint Node::getInputType()
{
    return inputType;
}


/*TO get Output Type */

uint Node::getOutputType()
{
    return outputType;
}
/* Get Indegree */
int Node::getInDegree()
{
    return inDegree;
}
/* Get Outdegree */
int Node::getOutDegree()
{
    return outDegree;
}


int Node::getInDegreeMax()
{
    return inDegreeMAX;
}
int Node::getOutDegreeMax()
{
    return outDegreeMAX;
}
void Node::setInDegreeMax(int value)
{
    inDegreeMAX = value;
}
void Node::setOutDegreeMax(int value)
{
    outDegreeMAX = value;
}


int Node::getInputMatch(uint num)
{
    int ret;
    switch(num)
    {
        case 1: ret = 0; break;
        case 8: ret = 1; break;
        case 16: ret = 2; break;
        case 32: ret = 3; break;
        default: ret = -1;
    }

    return ret;
}

/*Increment or Decrements the INDegree of Node */
void Node::modifyInDegree(Modify mode)
{
    if(mode == Node::increase)
        inDegree++;
    else
        inDegree--;
    return;
}
/*Increment or Decrements  the OutDegree of Node */
void Node::modifyOutDegree(Modify mode)
{
    if(mode == Node::increase)
        outDegree++;
    else
        outDegree--;
}

/************************** PRINT METHODS ******************/
/***********************************************************/

/* Prints the node */
/* Called from the node object */
void Node::printNode(PrintOp::PrintZone printType, std::ofstream* obj)
{
    //  a0 [ label="a0" ];
    std::stringstream ss;
    ss << this->getLabel() << " [ label= \"" << this->getLabel() <<  "\" ];" << std::endl;


    if(printType == PrintOp::Console)
        std::cout << ss.str();
    else
        {
            *obj << ss.str();
        }


}

/******************* NODE DATABASE METHODS ********************/
/***************************************************************/

/* Builds the entire database of Nodes */
bool Node::buildDataBase(uint nodes_number = MAX_POSSIBLE_NODES)
{
    for(uint i = 0; i < nodes_number/16; i++)
    {
        for(uint j = 0; j < 4; j++)
        for(uint k = 0; k < 4; k++)
        {
            std::stringstream ss;
            ss << Node::labelArray.substr(i, 1) << "_"  << Node::ioArray[j] << "_" << Node::ioArray[k] ;


            Node n(ss.str(), labelArray.substr(i,1) ,Node::ioArray[j], Node::ioArray[k]);
            Node::NodeDataBase.push_back(new Node(n));
            // Input type Sorted
            Node::IpTypeSortedNodes[j].push_back(new Node(n));
        }
    }

    return true;
}


/* Reference Funtion to print out the entire node database */
void Node::printNodesinDataBase(std::vector<Node*>* NodeList)
{
    uint i = 1;
    for(std::vector<Node*>::iterator it = NodeList->begin(); it!= NodeList->end(); it++)
    {

        std::stringstream ss;
        ss << " Node " << i++ << " : " << (*it)->getLabel()  << " ip : " << (*it)->getInputType()
        << "   op : " << (*it)->getOutputType();
        std::cout << ss.str() << std::endl;
    }
}

void Node::printDataBase()
{

    Node::printNodesinDataBase(&Node::NodeDataBase);
    return;
}


