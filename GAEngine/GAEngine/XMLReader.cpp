#include "XMLReader.h"

XMLReader::XMLReader() {
	FILE *pFile = fopen("resources.xml", "rt");
	if (pFile != NULL) {
		fseek(pFile, 0, SEEK_END);	// Seeks the reading pos inside a file; in this case we are pointing the reading pos to the start
		long nSize = ftell(pFile);	// See how long is the file
		fseek(pFile, 0, SEEK_SET);

		char *pBuffer = new char[nSize];	// = malloc(nSize)
		memset(pBuffer, 0, nSize);	// set all the array to 0

		fread(pBuffer, nSize, 1, pFile);
		fclose(pFile);

		doc.parse<0>(pBuffer);
		node = doc.first_node();
	}
}

char* XMLReader::Load(string name) {
	//xml_node<> *child = node->first_node();
	//xml_attribute<> *attr; // = node->first_attribute();
	////char* route = "";
	////for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
	//do {
	//	do {
	//		if (child->first_attribute() != NULL) {
	//			attr = child->first_attribute();
	//			if (attr->value() == name) {
	//				return child->value();
	//			}
	//			child = child->next_sibling();
	//		}
	//		child = child->first_node();
	//	} while (child->next_sibling() != NULL);
	//	child = child->first_node();
	//} while (node->next_sibling() != NULL);

	//xml_attribute<> *attr;
	for (xml_node<> *parent = node; parent != NULL; parent = parent->next_sibling()) {
		for (xml_node<> *child = parent->first_node(); child != NULL; child = child->next_sibling()) {
			xml_attribute<> *attr = child->first_attribute();
			if (attr->value() == name) {
				return child->value();
			}
		}

	}
	
	return NULL;
}