/**
 * Created by universallp on 26.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

/**
 * This class reads *.PZL files and converts them into an object used
 * by this engine. Read "pzl format.txt" for detailed documentation
 * on the file format
 */
#ifndef PUZZLE_H
#define PUZZLE_H

#include "PZLConstants.h"
#include <stdio.h>
#include <fstream>

typedef unsigned char BYTE;

class Puzzle
{
public:
	Puzzle();
	~Puzzle();

	int get_level_count(void);

	void read_from_file(std::string path);

private:
	bool m_file_is_ok;
	int m_level_count;
};

#endif
