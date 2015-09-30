/**
*   Process String- Nodes and Compositional List and Frequency -> CSV format
*   v1.0
*   Author : Shankar Kartik Jawahar
*   Type : Junk
**********************************************
*   Process String - Nodes and Compositional List and Freqency -> CSV foramt and DataBase update
*   v2.0
*   Author : Shankar Kartik Jawahar
*   Type : Semi-Refined
*   Dependencies : Node, Edge, DataAnalytics
*
*/


#include "DataAnalytics.h"
#include <algorithm>
#include <cstdlib>

#define compositionType 1
#define functionType 2

using namespace std;

bool debug = false;
string current_type = "";
static int line_count;
static int compLine;
//static int sortList[26] = {0};
static int freqArray[26 * 17] = {0}; // Make it N * N array.
// Modified with v2.0
static int compMAT[26 * 26 ] = {0};    // Make a matrix for the Composition - 26 * 26 types with 4 different bus size(size doesnt matter)

const int busSize[4] = {1, 8 , 16, 32};

int* maxFreqCompo;

multimap <pair<string, string>, int> compMap;
map <string, int> funcMap;

/** Get the list from Input and Store it in output
*   @param - input file stream reference
*   @param - output file stream reference
*   @param - FIle Data Type - Composition or Functional
*   @return - Success or Failure
*   v2.0 Update
*   @param - DataAnalytics Object Pointer
*/
bool getThelist(ifstream &, ofstream &,int , DataAnalytics* Obj);
/** Process the input string - Functional Data/ Nodes
*   @param - string - current line
*   @param - Output file stream reference
*   @return - success or Failure
*   v2.0 Update --> Process ip and op types and store in Database
*   @param - DataAnalytics Object pointer
*/
bool processStringFunctional(string str, ofstream &, DataAnalytics* obj);
/** Process the input string - Compositional Data/ Edges
*   @param - string - current line
*   @param - output file stream reference
*   @return - Success or Failure
*   v2.0 Update --> Process ip and op types and store in Database
*   @param - DataAnalytics Object Pointer
*/
bool processStringCompositional(string str, ofstream &, DataAnalytics* obj);
/** Calculate the sum of the elements of Array - 0 to N-2
*   @param - Pointer to the 1st element of array
*   @return - integer sum
*/
int sumFreq(int*);


/** Prints the array to the file and adds to DB
*   @param - ofsream obj
*   @param - DataAnalytics Obj pointer
*   @return - success or failure
*/

bool dumpFunction( ofstream &, DataAnalytics*);

int main(int argc, char**argv)
{
/*
    if(argc > 4 || argc <= 1)
    {
        cerr << "Invalid Inputs!!" << endl;
        exit(1);
    }

    string fns = argv[1];
    string cns = argv[2];
*/

    DataAnalytics* Analysis = new DataAnalytics();
    string fns = "../../apriori/recode_reformat/FunctionalOP" ;
    string cns = "../../apriori/recode_reformat/CompositionOP";

	ifstream input_fns(fns.c_str(), ifstream::in);
	ifstream input_cns(cns.c_str(), ifstream::in);
	ofstream output_fns;
	ofstream output_cns;

	if(!input_fns || !input_cns)
	{
		cerr << "Input File not found !!!" << endl;
		exit(1);
	}
	output_fns.open("../../apriori/recode_reformat/Functional_list.csv", ofstream::out);
	output_cns.open("../../apriori/recode_reformat/Composational_list.csv", ofstream::out);

    //Print Header
    output_fns << "Frequency, Node Type , 1_1, 1_8, 1_16, 1_32, 8_1, 8_8, 8_16, 8_32, 16_1, 16_8, 16_16, 16_32, 32_1, 32_8, 32_16, 32_32" << endl;
    output_cns << "From Node Type , a , b, c, d, e, f, g, h, i, j, k , l, m , n, o , p , q, r, s, t, u, v, w, x, y, z" << endl;

    if(!getThelist(input_fns, output_fns, functionType, Analysis))
    {
        cerr << "Could not get the Functional List " << endl;
        exit(1);
    }
    if(!getThelist(input_cns, output_cns, compositionType, Analysis))
    {
        cerr << "Could not get the Compostional List " << endl;
        exit(1);
    }

    // Map to Array

    // FLush array - A bug modifies the values somewhere - so flush all
    for(int i = 0; i < 26*26; i++)
        compMAT[i] = 0;

   // cout << "Array MAP" << endl;
    for(multimap<pair<string, string>, int>::iterator it = compMap.begin(); it!= compMap.end(); it++)
    {
        compLine++;
        stringstream ss;
       if(debug)
         {
            ss << it->first.first << ", " << it->first.second << " , " << it->second << endl;
            cout << ss.str();
         }

        // get char value
        const char* fromType = it->first.first.c_str();
        const char* toType = it->first.second.c_str();

        if(debug)
            cout << "Before assign : " << compMAT[((int(fromType[0])-97) * 26)  + ((int(toType[0])-97))] << endl;

        compMAT[((int(fromType[0])-97) * 26)  + ((int(toType[0])-97))] += it->second;

        if(debug)
        {
            cout << compMAT[((int(fromType[0])-97) * 26)  + ((int(toType[0])-97))] << " @ " << int(fromType[0] - 97) << fromType[0]
            << "    " <<  int(toType[0]-97) << toType[0]
            << " while types " << it->second << endl;
        }

    }

    //Map all to Composition List - DataAnalytics
    for(int i = 0; i < 26; i++)
    {
        for(int  j = 0; j < 26; j++)
        {
            if(compMAT[i*26 + j]!= 0)
            {
                char from = i+97;
                char to = j+97;

                stringstream s1, s2;
                s1 << from;
                s2 << to;

                if(debug)
                {
                    cout << s1.str() << " : " << s2.str() << endl;
                }

                Analysis->addComposition(s1.str(), s2.str(), compMAT[i*26 + j], 0);
            }
        }
    }



  //  cout << "Array Map end" << endl;

    // Print COmp list in csv
    for(int i = 0; i < 26; i++)
    {
        stringstream ss;
        ss << char(i+97);
        for(int j = 0; j < 26; j++)
        {
            ss << "," << compMAT[(i*26) + (j)] ;
        }

        ss << endl;
    //    cout << ss.str();
        output_cns << ss.str();
    }

	input_fns.close();
	input_cns.close();
	output_fns.close();
	output_cns.close();


   // Analysis->printFunctionMap() ;

    cout << "------------------------------" << endl;

   // Analysis->printCompMap();

    /*
	int number_of_compo = 0;
	cout << " \n ---------------------------------------------------------------\n" ;
	cout << " Max_Freq Compositions :  ";
	cout << endl << "Enter the number of compostions : " ; cin  >> number_of_compo;
    */

    Analysis->linearWeightedSelection();

    cout << " Total size :: Functions - Compositions :: " << Analysis->getFuncMapCapacity() << " - " << Analysis->getCompMapCapacity();
    int num_of_C;
    cout << " Number of Function Compositions?? : " ;
    cin >> num_of_C;


    Analysis->report(num_of_C);

	return 0;
}

bool getThelist(ifstream &in, ofstream &out, int type , DataAnalytics* AnalysisObj)
{

    //string node;
    string line;



    getline(in, line);
    do
    {

      //  std::cout << "line :: " <<  line << std::endl;

        if(type == functionType)
        {
            processStringFunctional(line, out, AnalysisObj);
        }
        else
        {
            processStringCompositional(line, out, AnalysisObj);

        }
        getline(in, line);

    }while((line.compare("Frequent 2-itemsets:")) && line.compare("\n") && line.compare("Association rules:") && line.compare(""));

    // DUMP the last function type into file - missed in loop
    if(type == functionType)
        dumpFunction(out, AnalysisObj);
    return true;
}


bool processStringCompositional(string str, ofstream &out, DataAnalytics* Analysis)
{
    string fulledge, fromFunctionType, toFunctionType, channelType ,freq;

    if(str.compare(""))
    {

        size_t freq_pos = str.find(" ");

        fulledge = str.substr(0, freq_pos);
        size_t fromType = fulledge.find("_");
        fromFunctionType = fulledge.substr(0, fromType);
        string temp = fulledge.substr(fromType+1);
        size_t toType = temp.find("_");
        toFunctionType = temp.substr(0, toType);
        channelType = temp.substr(toType+1);
        size_t endpos = str.find(")");
        freq = str.substr(freq_pos+2, endpos - (freq_pos+2));


        int frequency =  atoi(freq.c_str());

      //  cout << freq << " : " << frequency << " Channel Type: " << channelType << endl;

        compMap.insert(pair<pair<string, string>, int>(pair <string, string> (fromFunctionType, toFunctionType), frequency));



        // v2.0 - Additions


        return true;
    }
    return false;
}

bool processStringFunctional(string str, ofstream &out , DataAnalytics* Analysis)
{
    string fullNode, node, ip, op, freq;



    size_t freq_pos = str.find(" ");
    size_t end_pos = str.find(")");


    fullNode = str.substr(0, freq_pos);

    size_t ip_pos = fullNode.find("_");
    string temp = fullNode.substr(ip_pos+1);
    size_t out_pos = temp.find("_");
    node = fullNode.substr(0, ip_pos);
    ip = temp.substr(0,out_pos);
    op = temp.substr(out_pos+1);
    freq = str.substr(freq_pos+2, end_pos - (freq_pos+2));

    int frequency = atoi(freq.c_str());
    int input_typ = atoi(ip.c_str());
    int output_typ = atoi(op.c_str());

    const char* n_char = node.c_str();

    for(int i = 0; i < 4 ;i++)
    {
        int flag = 0;
        for(int j = 0; j < 4;j++)
        {
            if(input_typ == busSize[i] && output_typ == busSize[j])
            {
                freqArray[(n_char[0] - 97)*26 + (i*4 + j)] = frequency;
                flag = 1;
                if(debug)
                {
                    std::cout << "freq @  " << line_count*26 + (i*4) + j << " or " << (n_char[0] - 97)*26 + (i*4) + j << " is "  << frequency << endl;
                }
                break;
            }
        }
        if(flag)
            break;
    }



    // Assign a current Type
    if(node.compare(current_type))
    {
      //  cout << " Entry " << endl;
       if(current_type.compare(""))    // if not the 1st entry
        {

            dumpFunction(out, Analysis);

        }
        // set current node
        current_type.assign(node);

        //cout << "DEGUG :: OUTER " << current_type << endl;

    }


    //v2.0 additionals
    // Not yet implemented - Along with bus type

    return true;
}


int sumFreq(int* arrayVal)
{
    int sum_ret = 0;

    const char* ch = current_type.c_str();

    for(int i = 0; i < 16; i++)
    {
        sum_ret += arrayVal[(ch[0]-97)*26 + i];
    }
  //  cout << "SUM val : " << sum_ret << endl;
    return sum_ret;
}



bool dumpFunction(ofstream &out, DataAnalytics* Analysis)
{

        const char* ctype_char = current_type.c_str();
        line_count++;

        freqArray[(ctype_char[0]-97)*26 + 16] = sumFreq(freqArray);

        stringstream ss;
        ss << freqArray[(ctype_char[0]-97)*26 + 16] << ",";
        ss << current_type.c_str() << ",";

        for(int i = 0; i< 16; i++)
            ss << freqArray[(ctype_char[0]-97)*26 + i] << ",";

        out << ss.str() << endl;


        //v2.0 additionals


        // ADD function to database
     //   cout << "Adding Node to DB : " << current_type << endl;

        Analysis->addFunction(ctype_char, freqArray[(ctype_char[0]-97)*26 + 16], 0, 0);

        return true;

}
