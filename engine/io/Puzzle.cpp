/**
 * Created by universallp on 26.07.2017.
 * This file is part of reloded which is licenced
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/reloded
 */

#include "Puzzle.h"


Puzzle::Puzzle()
{
	m_file_is_ok = false;
}

Puzzle::~Puzzle()
{

}

int Puzzle::get_level_count(void)
{
	return m_level_count;
}

void Puzzle::read_from_file(std::string path)
{
	std::ifstream m_file_stream(path.c_str(), std::ios::binary);
	BYTE b;

	if (m_file_stream.good())
	{
		m_file_stream.seekg(LEVEL_COUNT_OFFSET);
		b = m_file_stream.get();
		m_level_count = b;
	}
	else
	{
		printf("Couldn't open puzzle %s! File not found or corrupt.\n", path.c_str());
	}

	m_file_stream.close();
}


