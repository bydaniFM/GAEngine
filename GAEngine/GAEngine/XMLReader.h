#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class XMLReader {
private:
	xml_document<> doc;
	xml_node<> *node;
public:
	XMLReader();
	char* Load(string name);
};