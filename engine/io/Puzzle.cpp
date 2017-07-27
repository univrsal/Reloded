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
	std::ifstream fs(path.c_str(), std::ios::binary);

	if (fs.good())
	{
		fs.seekg(LEVEL_COUNT_OFFSET);
		m_level_count = read_byte(&fs);
		int offset = 0;
		m_level_offsets.emplace_back(LEVEL_FIRST_HEADER);

		for (int i = 0; i < m_level_count; i++)
		{
			if (!fs.good())
				break;
			offset = m_level_offsets[i];
			printf("READING LEVEL %i at %i\n", i, offset);
			read_level(&fs, &offset);
		}
	}
	else
	{
		printf("Couldn't open puzzle %s! File not found or corrupt.\n", path.c_str());
	}

	fs.close();
}

BYTE Puzzle::read_byte(std::ifstream* file)
{
	if (m_file_is_ok || file == NULL)
		return -1;
	return file->get();
}

void Puzzle::read_level(std::ifstream * file, int* header_offset)
{
	// First read in the level name 
	// It's 11 Bytes after the header
	file->seekg(*header_offset + LEVEL_NAME);
	std::string temp;
	std::getline(*file, temp);
	printf("LEVELNAME %s\n", temp.c_str());

	// Then go back to the header to read in the other values
	file->seekg(*header_offset);

	// Now read in the level size
	BYTE a = read_byte(file);
	BYTE b = read_byte(file);
	int level_size = a | b << 8;
	m_level_sizes.emplace_back(level_size);

	int level_offset = *header_offset + level_size + LEVEL_HEADER_SPACE;
	m_level_offsets.emplace_back(level_offset);
}


