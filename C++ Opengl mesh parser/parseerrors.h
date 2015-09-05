/*
 * parseerrors.h
 *
 *  Created on: 17 mai 2015
 *      Author: thejohncrafter
 */

#ifndef PARSER_PARSEERRORS_H_
#define PARSER_PARSEERRORS_H_

#include <exception>
#include <string>

using namespace std;

namespace parser {

/**
 * Thrown when a file isn't found.
 */
class NoSuchFileException: exception {
public:
	/**
	 * Constructs the exception.
	 * @param file The name of the file that can't be found.
	 */
	NoSuchFileException(const string file);
	/**
	 * Returns a C-string describing the exception.
	 * @return A string like this : "Can't find file <file name>.".
	 */
	const char* what();
private:
	/**
	 * Stores the name of the file that can't be found.
	 */
	string file;
};

/**
 * Thrown if an error occurs while parsing.
 */
class ParseException: exception {
public:
	/**
	 * Constructs the exception.
	 * @param line The line where the exception occured.
	 * @param explain A string describing the exception.
	 */
	ParseException(const int line, const string file, const string explain);
	/**
	 * Returns a C-string describing the exception.
	 * @return A string like "Parse exception at line <line> : <description>".
	 */
	const char* what();
private:
	/**
	 * The line where the exception occured.
	 */
	int line;
	string file;
	/**
	 * Describes the exception.
	 */
	string explain;
};

} /* namespace nodes */

#endif /* PARSER_PARSEERRORS_H_ */
