/*
 * Parser.cpp
 *
 *  Created on: 17 mai 2015
 *      Author: thejohncrafter
 */

#include "Parser.h"
#include <sstream>

#include <string>

using namespace std;

namespace parser {

Parser::Parser(const string file) throw (NoSuchFileException) {
	this->file = file;
	this->in = new ifstream(file, ios::in);

	if(!in)
		throw NoSuchFileException(file);

	curr_member = head;
	current_line = 1;
	vertex_count = 0;
	triangle_count = 0;
	// Null initialization (will become an array).
	vertex_array = 0;
	final_array = 0;
}

void Parser::parse() throw (ParseException) {

	//======== VARIABLES ========//
	string line;
	unsigned int vertex = 0, triangle = 0;

	//======== PARSING ========//
	cout << "Reading " << file << endl;

	while (getline(*in, line)) {

		if (line.length() == 0)
			continue;

		istringstream iss(line);

		switch (line[0]) {
		case '@': {
			//---- Head ----//
			if (curr_member != head)
				exception("Header outside of head !");

			string name;

			if (!(iss >> name))
				exception("Can't read first word !");

			if (name == "@version") {

				unsigned int fversion;

				if (!(iss >> fversion))
					exception("Can't convert to unsigned int !");
				else if (fversion != version)
					exception(
							"Invalid version : parser version = "
									+ to_string(version) + ", file version = "
									+ to_string(fversion));

			} else if (name == "@vertices") {
				if (!(iss >> vertex_count))
					exception("Can't convert to unsigned int !");
			} else if (name == "@triangles") {
				if (!(iss >> triangle_count))
					exception("Can't convert to unsigned int !");
			} else {
				exception("Invalid property name : " + name);
			}
			break;
		}
		case ':': {
			//---- Member ----//
			string name = line.substr(1, line.find(' ') - 1);
			if (name == "vertices") {
				if (curr_member != head)
					exception(
							"Vertices declaration isn't after head and before triangles !");
				curr_member = vertices;
				//TODO : handle out of memory
				vertex_array = new float[3 * vertex_count];
			} else if (name == "triangles") {
				if (curr_member != vertices)
					exception("Triangles declaration isn't after vertices !");
				curr_member = triangles;
				final_array = new float[9 * triangle_count];
			}
			break;
		}
		case '/':
			// Commentary
			break;
		default: {
			if (curr_member == vertices) {

				if (vertex == vertex_count * 3)
					exception("Too much vertixes !");

				float x, y, z;

				if (!(iss >> x)) {
					exception("Can't read x coordinate !");
				} else if (!(iss >> y)) {
					exception("Can't read y coordinate !");
				} else if (!(iss >> z)) {
					exception("Can't read z coordinate !");
				}

				vertex_array[vertex] = x;
				vertex++;
				vertex_array[vertex] = y;
				vertex++;
				vertex_array[vertex] = z;
				vertex++;

			} else if (curr_member == triangles) {

				if (triangle == triangle_count * 9)
					exception("Too much triangles !");

				int v1, v2, v3;

				if (!(iss >> v1)) {
					exception("Can't read first vertice's id.");
				} else if (!(iss >> v2)) {
					exception("Can't read second vertice's id.");
				} else if (!(iss >> v3)) {
					exception("Can't read third vertice's id.");
				}

				v1 *= 3;
				v2 *= 3;
				v3 *= 3;

				// Vertex #1
				final_array[triangle] = vertex_array[v1];
				final_array[triangle + 1] = vertex_array[v1 + 1];
				final_array[triangle + 2] = vertex_array[v1 + 2];
				// Vertex #2
				final_array[triangle + 3] = vertex_array[v2];
				final_array[triangle + 4] = vertex_array[v2 + 1];
				final_array[triangle + 5] = vertex_array[v2 + 2];
				// Vertex #3
				final_array[triangle + 6] = vertex_array[v3];
				final_array[triangle + 7] = vertex_array[v3 + 1];
				final_array[triangle + 8] = vertex_array[v3 + 2];

				triangle += 9;

			} else
				exception("Not in a member !");
			break;
		}
		}

		current_line++;

	}

	cout << "Done." << endl;
	in->close();

}

void Parser::exception(const string what) const throw (ParseException) {
	throw ParseException(current_line, file, what);
}

Parser::~Parser() {
	delete in;
	delete[] vertex_array;
}

} /* namespace parser */
