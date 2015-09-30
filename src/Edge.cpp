#include "Edge.h"
#include <string>

Edge::Edge(std::string label , std::string taillabel, std::string headlabel, Node* n1 , Node* n2)
:
label(label),
taillabel(taillabel),
headlabel(headlabel),
source(n1),
destination(n2)
{

}


Edge::~Edge()
{
    //dtor
}

/* Prints the edge in the required format */
/* Called from the edge object */

void Edge::printEdge(PrintOp::PrintZone PType, std::ofstream* obj)
{
    //a1 -> a0 [ label="ch0", taillabel="1", headlabel="1" ];
    Edge e1 = *this;

    std::stringstream ss;

   ss << std::endl << e1.source->getLabel() << " -> " << e1.destination->getLabel() << " [ label=\"" << e1.getLabel()
   <<  "\", taillabel=\"" << e1.getTail() << "\", headlabel=\"" << e1.getHead() << "\" ];" ;

    if(PType == PrintOp::Console)
        std::cout << ss.str();
    else if(PType == PrintOp::File)
    {
       *obj << ss.str();
    }
}



/** Get Functions **/

std::string Edge::getLabel()
{
    return label;
}

std::string Edge::getHead()
{
    return headlabel;
}
std::string Edge::getTail()
{
    return taillabel;

}

std::pair<Node*, Node*> Edge::getSourceAndDest()
{
    std::pair<Node*, Node*> node_pair = std::make_pair(source, destination);
    return node_pair;
}

Node* Edge::getDestination()
{
    return destination;
}

Node* Edge::getSource()
{
    return source;
}


/*

Edge::Edge(const Edge& other)
{
    //copy ctor

}



 //assignment operator
Edge& Edge::operator=(const Edge& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

   // Edge e(this->label, this->taillabel, this->headlabel, this->source, this->destination);



    //return e;
}
*/
