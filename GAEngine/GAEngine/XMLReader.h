#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

// Manages xml document.
class XMLReader {
private:
	// The document that is being used in this class.
	xml_document<> doc;
	// Pointer to the reading position in the document.
	xml_node<> *node;
public:
	// Constructor that opens the document, parses it and closes it.
	XMLReader();
	// Receives a string with the name of the item to find in the xml and returns its content.
	char* Load(string name);
};