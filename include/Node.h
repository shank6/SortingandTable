/***
****** Author : Shankar Kartik Jawahar
        Embedded Systems Lab,
        Northeastern University
******
    Random Graph Generator v0.1
    Node Program
    Connected Classes - Edge, Graph
    Node - label
*****

    v0.2

    Node format - label , inputType, outputType
    InEdge, OutEdge, degree
*** Modifications **************
    Node() - constructor
    Node Database - Contains all Node Types (From "a_1_1 to z_32_32")

***
        NoTE: the maximum edge capacity of the Nodes have been set to 26*16


***/



#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>


#define MAX_POSSIBLE_NODES  (26*16)

namespace PrintOp
{
    enum PrintZone { File, Console };
};

class Node
{

    public:

        enum Modify { increase, decrease };

        Node();
        Node(const std::string label1, const std::string type ,uint input, uint output, uint indegree, uint outdegree );
        Node(Node *);   // Copy a node pointer
        virtual ~Node();


        void printNode(PrintOp::PrintZone Type, std::ofstream* obj);   // Prints a node

        /** Methods to Access Data **/
        std::string getLabel();
        uint getInputType();
        uint getOutputType();
        int getInDegree();
        int getOutDegree();

        std::string getNodeType();

        int getInDegreeMax();
        int getOutDegreeMax();
        void setInDegreeMax(int maxVal);
        void setOutDegreeMax(int maxVal);

        /*Increment or Decrements the INDegree of Node */
        void modifyInDegree(Modify Mode);
        /*Increment or Decrements  the OutDegree of Node */
        void modifyOutDegree(Modify Mode);




// Use implicit copy construtor for now
/*
        Node(const Node& other);
*/
        Node& operator=(const Node& other);


/* STatic Database for the pool of Nodes
* And the tools to build it
*/
        static std::vector<Node*> NodeDataBase;
        static std::vector<Node*> IpTypeSortedNodes[4];
        static bool buildDataBase(uint nodes_num );
        static void printDataBase();
        static void printNodesinDataBase(std::vector<Node*>* NodeList);
               /* A Misc Function to get the vector list number */
        static int getInputMatch(uint num);

    protected:
        std::string label;

    private:
        uint inputType;
        uint outputType;
        int degree;
        int inDegree;
        int outDegree;

        int inDegreeMAX;
        int outDegreeMAX;

        std::string nodeType;

        static const std::string labelArray;
        static const uint ioArray[4];


};

#endif // NODE_H
