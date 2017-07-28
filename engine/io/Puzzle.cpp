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
	close();
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
			//printf("READING LEVEL %i at %i\n", i, offset);
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
	
	m_level_names.push_back(read_run_length_string(file));

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

std::string* Puzzle::get_level_name(int id)
{
	if (id >= 0 && id < m_level_names.size())
		return &m_level_names[id];
	return NULL;
}

void Puzzle::close(void)
{
	m_file_is_ok = false;
	m_level_count = 0;
	m_level_names.clear();
	m_level_offsets.clear();
	m_level_sizes.clear();
}

/**
 * For whatever reason the Loderun devs thought it would be a good idea
 * to save the level name with the run-length encoding. Maybe this was
 * a standard back in the day. Basically if there's the same letter at
 * least twice in a row it'll be compressed.
 * AAAAAAH would turn into 06AH (Since 'A' is chained 6 times in a row)
 * This entire function is a mess but I think there's no standard way
 * to do this.
 */
std::string Puzzle::read_run_length_string(std::ifstream * file)
{
	BYTE b;
	BYTE c;
	char e;
	std::string out = "";

	for (int i = 0; i < 255; i++)
	{
		b = file->get();
		
		if (b == 0xff) // 0xff starts an uncompressed part
		{
			c = read_byte(file);

			for (int j = 0; j < c; j++)
			{
				e = read_byte(file);
				out += e;
			}

			c = read_byte(file); // How often to repeat the character that is
			e = read_byte(file); // read into e

			for (int j = 0; j < c; j++)
			{
				out += e;
			}
		}
		else
		{
			e = read_byte(file);
			for (int j = 0; j < b; j++)
			{
				out += e;
			}
		}

		if (!file->good() || out.length() >= 255)
			break;
	}

	return out;
}


