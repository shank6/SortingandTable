#include "DataAnalytics.h"

int DataAnalytics::functionCount = 0;
int DataAnalytics::compositionCount = 0;

std::vector<Node*> DataAnalytics::FunctionList;
std::vector<Edge*> DataAnalytics::CompositionList;

std::map<Node*, int> DataAnalytics::FunctionMap;
std::map<Edge*, int> DataAnalytics::CompositionMap;

std::list<std::pair<Edge*, int>* > DataAnalytics::WeightedList;

/** OPERATIONS **/

bool DataAnalytics::linearWeightedSelection() throw()
{
    bool debug = false;
    for(auto  it : CompositionMap)
    {
        int fromFreq = FunctionMap.find(it.first->getSource())->second;
        int toFreq = FunctionMap.find(it.first->getDestination())->second;

        int totalWeight = (fromFreq + toFreq) * it.second;

        WeightedList.push_back(new std::pair<Edge*, int> (it.first, totalWeight));
    }


    WeightedList.sort(sortmylist);
    if(debug)
    {
        for(auto it : WeightedList )
        {
            std::cout << it->first->getLabel() << " : " << it->second << std::endl;
        }
    }

    return true;
}


/** Methods to add Data to Database**/

/* Add Nodes to the database
*  @param - String - Node type
*  @param - frequency - freqency of the node
*  @param - input / output - input and output bus Type
*  @return - success or failure
*/

bool DataAnalytics::addFunction(std::string nodeType, uint freqency = 0,
        uint inputType = 0, uint outputType = 0) throw ()
{

    std::stringstream ss;
    ss << nodeType << "_" << inputType << "_" << outputType;
    try
    {
        Node n(ss.str(), nodeType, inputType, outputType, 0, 0);

    //    std::cout << "DataAnalytics :: " << n.getLabel() << std::endl;

        FunctionList.push_back(new Node(n));

        FunctionMap.insert(std::pair<Node*, int> (FunctionList.at(DataAnalytics::functionCount), freqency));

       // std::cout << "Inserting Function : " << FunctionList.at(DataAnalytics::functionCount)->getLabel() <<std::endl;

    }
    catch(...)
    {
        throw std::logic_error("DataAnalytics:: Unable to add Node to Map");
    }
    DataAnalytics::functionCount++;
    return true;
}


/* Add Composition to Database
*  @param - String - source Node type
*  @param - String - destination Node type
*  @param - frequency - freqency of the node
*  @param - input  -  bus Type
*  @return - success or failure
*/
bool DataAnalytics::addComposition(std::string fromType,std::string toType,
        uint frequency = 0, uint busType = 0) throw()
{
    std::stringstream ss;
    ss << fromType << "->" << toType ;

   // std::cout << "Comp : " << ss.str() << std::endl;

    try
    {
        int pos1 = findNode(fromType, FunctionList);
        int pos2 = findNode(toType, FunctionList);

        if((pos1 != -1 && pos2 != -1) )
        {

            Edge e(ss.str(), fromType, toType, FunctionList.at(pos1), FunctionList.at(pos2));

            CompositionList.push_back(new Edge(e));

            CompositionMap.insert(std::pair<Edge*, int>(CompositionList.at(compositionCount), frequency));


        }
        else
        std::cerr << " Function not in list " << std::endl;


    }
    catch(std::domain_error& e)
    {
       std::cerr << " ERROR :: " << e.what() << std::endl;
    }
    catch(...)
    {
        throw std::logic_error ("DataAnalytics:: Unable to add Composition to Map");
    }

    compositionCount++;

    return true;
}


/** SUPPORT Methods **/

/* Searches for a node and returns the iterator position
*  @param - vector<Node*> - list of nodes
*  @param - string - node label - to be found
*  @return - int - position of the node; -1 if not found
*/

int DataAnalytics::findNode(std::string node, std::vector<Node*> List = FunctionList ) throw()
{

    std::vector<Node*>::iterator it;
    int position;
    try
    {
       std::stringstream ss;
       ss << node << "_0_0";  // NOTE : THIS IS ON ASSUMTION - BUS TYPE IS IGNORED
       for(Node* listNodes : FunctionList)
       {
            if(!node.compare(listNodes->getNodeType()))
            {

                break;
            }
            position++;

       }

    }

    catch(...)
    {
        throw std::runtime_error("Unable to Access Vector");

    }

    if(position == (int)List.size())
        position = -1;

    return position;

}


bool DataAnalytics::sortmylist(const std::pair<Edge*, int>* fst ,const std::pair<Edge*, int>* snd )
{

    if(fst->second < snd->second) return false;
    else return true;

}

/* REPORT FUNCTIONS */

void DataAnalytics::report(int max_num) throw()
{
    int count = 0;
    for( auto it : DataAnalytics::WeightedList)
    {
        std::cout << it->first->getLabel() << " with weight of " << it->second << std::endl;
        if(count++ == max_num)
        {
            return;
        }
    }
}

/** DEBUG METHODS **/

/* prints the function map */
void DataAnalytics::printFunctionMap()
{
   /*
    for(std::map<Node*, int>::iterator it = FunctionMap.begin(); it!= FunctionMap.end(); it++)
    {
        std::cout << "Data Analytics :: Map<Function> :: " << it->first->getLabel()
            << " Freq :: " << it->second << std::endl;
    }

    */

    for(auto it : FunctionMap)
    {
         std::cout << "Data Analytics :: Map<Function> :: " << it.first->getLabel()
            << " Freq :: " << it.second << std::endl;

    }


    for(auto it : FunctionList)
    {
        std::cout << "Data Analytics :: Vector<Function> :: " << it->getLabel() << std::endl;
    }
    return;
}


/* prints the comp map */

void DataAnalytics::printCompMap()
{

    /*
    for(auto it : CompositionMap)
    {

        std::cout << " Data Analytics :: Map<Composition> :: " << it.first->getLabel()
            << "Freq :: " << it.second << std::endl;
    }
    */

     for(std::map<Edge*, int>::iterator it = CompositionMap.begin(); it!= CompositionMap.end(); it++)
    {
        std::cout << "Data Analytics :: Map<Composition> :: " << it->first->getLabel()
            << " Freq :: " << it->second << std::endl;
    }

    return;
}

void DataAnalytics::testFind()
{
    std::string node = "n";

    int pos = findNode(node, FunctionList);

    std::cout << "Found node @ " << pos << std::endl;


}

size_t DataAnalytics::getCompMapCapacity()
{
    return CompositionMap.size();
}

size_t DataAnalytics::getFuncMapCapacity()
{
    return FunctionMap.size();
}
