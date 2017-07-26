/**
 * Created by universallp on 26.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>

class Puzzle
{
public:
	Puzzle(std::string path);
	~Puzzle();

private:
	std::string m_file_path;
};

#endif
