/*
 * Parser.h
 *
 *  Created on: 17 mai 2015
 *      Author: thejohncrafter
 */

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <fstream>
#include <iostream>
#include <list>
#include "parseerrors.h"

using namespace std;

namespace parser {

/**
 * Symblizes all the member types.
 */
enum member_types{
	head,    //!< Symbolizes "head" member.
	vertices,//!< Symbolizes "vertices" member.
	triangles//!< Symbolizes "triangles" member.
};

/**
 * Used to parse a model file.
 */
class Parser {
public:
	/**
	 * Sets up the parser.
	 * @param file The file to parse.
	 * @throw NoSuchFileException If the given file isn't found.
	 */
	Parser(const string file) throw (NoSuchFileException);
	/**
	 * Parses the file.
	 */
	void parse() throw (ParseException);
	/**
	 * Retutns the amount of vertices in the parsed file.
	 * @return The amount of vertices.
	 */
	inline const size_t vertex_array_size() const{
		return triangle_count * 9;
	}
	/**
	 * Returns the array containing all the vertices.
	 * @return The array containing all the vertices.
	 */
	inline float* getVertices() const{
		return final_array;
	}
	/**
	 * Destroys the parser.
	 */
	virtual ~Parser();
	/**
	 * Represents the parser's version.
	 */
	const unsigned int version = 1;
private:
	/**
	 * Used to read file.
	 */
	ifstream* in;
	/**
	 * The input file's name.
	 */
	string file;
	/**
	 * Represents the current member.
	 */
	member_types curr_member;
	/**
	 * Stores all the created vertices.
	 */
	float* vertex_array;
	/**
	 * Stores the final array that will be returned.
	 */
	float* final_array;
	/**
	 * Stores the current line in the file.
	 */
	size_t current_line;
	/**
	 * Stores the amount of vertices.
	 */
	size_t vertex_count;
	/**
	 * Stores the amount of triangles.
	 */
	size_t triangle_count;
	/**
	 * Used to throw an exception.
	 * @param what A description of the exception that happened.
	 */
	void exception(const string what) const throw (ParseException);
};

} /* namespace nodes */

#endif /* PARSER_PARSER_H_ */
