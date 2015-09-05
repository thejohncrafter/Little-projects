/*
 * parseerrors.cpp
 *
 *  Created on: 17 mai 2015
 *      Author: thejohncrafter
 */

#include "parseerrors.h"

#include <string>

using namespace std;

namespace parser {

NoSuchFileException::NoSuchFileException(const string file) {
	this->file = file;
}

const char* NoSuchFileException::what() {
	string s = "Can't find file " + file + ".";
	return s.c_str();
}

ParseException::ParseException(const int line, const string file,
		const string explain) {
	this->line = line;
	this->explain = explain;
	this->file = file;
}

const char* ParseException::what() {
	string s = "Parse exception at line " + to_string(line) + " in " + file
			+ " : " + explain;
	return s.c_str();
}

} /* namespace nodes */
