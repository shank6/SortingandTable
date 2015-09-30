/**  DataAnalytics - Analysis on the available nodes and composition list
*    Type: Class
*    v1.0
*       - Bus size is invalid - all defaulted to zero
*    Author : Shankar Kartik Jawahar
*    Dependencies : Node, Edge
*
*/

#ifndef DATAANALYTICS_H
#define DATAANALYTICS_H

#include "Node.h"
#include "Edge.h"

#include <exception>
#include <stdexcept>
#include <map>
#include <list>


class DataAnalytics
{
    public:

        /* Add Node to the Analytics database */
        bool addFunction(std::string nType, uint freq, uint ip, uint op) throw ();
        /* Add Compostion to Analytics database */
        bool addComposition(std::string fromType, std::string toType , uint freq, uint busSize) throw();


        /* OPERATIONS */

        /* Calculates the linear weighted algorthm on composition and prints the result in sorting order */
        bool linearWeightedSelection() throw();


        /* Prints the Analysis Report */
        void report(int number) throw();

        /* DEBUG FUNCTIONS */
        void printFunctionMap();
        void printCompMap();
        size_t getCompMapCapacity();
        size_t getFuncMapCapacity();
        void testFind();
    protected:
    private:

    /* SUPPORT METHODS */

        /* Methods to access data */
     int findNode( std::string node, std::vector<Node*>  ) throw();

     /* sorting for the result list */
    static  bool sortmylist ( const std::pair<Edge*, int>* f, const std::pair<Edge*, int>* s);



    /* Variables - Data Structures */

    static std::map<Node*, int> FunctionMap;
    static std::map<Edge*, int> CompositionMap;

    static int functionCount;
    static int compositionCount;

    static std::vector<Edge*> CompositionList;

    static std::vector<Node*> FunctionList;

    static std::list<std::pair<Edge*, int>* > WeightedList;

};

#endif // DATAANALYTICS_H
