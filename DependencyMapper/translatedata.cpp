#include "translatedata.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

string identifyFormatting(string s)
{
    string xml = "<";
    string space = " ";
    string comma = ",";

    if (s.find(xml) != string::npos)
        return xml;
    else if (s.find(space) != string::npos)
        return space;
    else
        return comma;
}

string removeFormatting(string curr, string type)
{
    if (type == "space")
    {
        int spaceIndex = curr.find(" ");
        string one = curr.substr(0, spaceIndex);
        string two = curr.substr(spaceIndex);
        return one + "->" + two;
    }

    else if (type == "comma")
    {
        int commaIndex = curr.find(",");
        string one = curr.substr(0, commaIndex);
        string two = curr.substr(commaIndex);
        return one + "->" + two;
    }

    else
    {

    }
}

int translate(string filename)
{
    ifstream file_(filename);
    string line;
    vector<string> data;

    if (file_.is_open())
    {
        while(getline(file_, line))
        {
            string id = identifyFormatting(line);
            string complete = removeFormatting(line, id);
            data.push_back(complete);
        }
        file_.close();
    }

    return 0;
}
