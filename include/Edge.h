/***
****** Author : Shankar Kartik Jawahar
        Embedded Systems Lab,
        Northeastern University
******
    Random Graph Generator v0.1
    Edge -
    label : string
    taillabel : string
    headlabel : string
    source : Node*
    destination : Node*

*****

***/




#ifndef EDGE_H
#define EDGE_H
#include "Node.h"
#include <utility>



class Edge
{
    public:
        Edge(std::string label1 , std::string tail, std::string head, Node* n1, Node* n2);
        virtual ~Edge();

        /* Printer Functions */
        void printEdge(PrintOp::PrintZone pType, std::ofstream* Obj);

        /** Get Functions**/
        std::string getLabel();
        std::string getTail();
        std::string getHead();
        std::pair<Node*, Node*> getSourceAndDest();

        Node* getSource();
        Node* getDestination();

    //  Edge(const Edge& other);  // Use Implicit copy constructor for now
    //  Edge& operator=(const Edge& other);
    protected:
    private:
    std::string label;
    std::string taillabel;
    std::string headlabel;
    Node* source;
    Node*  destination;






};

#endif // EDGE_H
