/**
 * Created by universallp on 26.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "Puzzle.h"

Puzzle::Puzzle(std::string path)
{
	m_file_path = path;
}

Puzzle::~Puzzle()
{
	m_file_path.clear();
}


