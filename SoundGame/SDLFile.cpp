//
//  SDLFile.cpp
//  readSMF
//
//  Created by mojito on 2020/06/08.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <cassert>
#include "SDLFile.hpp"

/*
 * constructer
 */
SDLFile::SDLFile()
{
	m_file_pointer = NULL;
}
/*
 * destructer
 */
SDLFile::~SDLFile()
{
	if (m_file_pointer != NULL)
	{
		close();
	}
}

/*
 * returns true if secceeded
 */
bool SDLFile::open(string filepath)
{
	// if a file has already opened, stop forcibly
	assert(m_file_pointer == NULL);

	// try to open the file
	m_file_pointer = SDL_RWFromFile(filepath.c_str(), "rb");
	
	// if failed to open
	if (m_file_pointer == NULL)
	{
		// return false
		return false;
	}

	// turn the flag to represents that we can read the file
	return true;
}

/*
 * close forcibly
 */
void SDLFile::close()
{
	SDL_RWclose(m_file_pointer);
}

/*
 * returns true if the pointer has reached to the end of the file
 */
bool SDLFile::eof()
{
	char dummy[1];
	size_t read_size;

	// try to read a byte from the file
	read_size = SDL_RWread(m_file_pointer, (void*)dummy, 1, 1);

	// if no data was read, the pointer may be at the end of file
	if (read_size == 0)
	{
		// then return true that means we have reached the end of file
		return true;
	}

	// otherwise, there may be some data left to be read..

	// resume the pointer back
	SDL_RWseek(m_file_pointer, -1, RW_SEEK_CUR);

	// then return false
	return false;
}

/*
 * returns a byte read from the file
 * when eof() is true, return value is invalid
 */
unsigned char SDLFile::get_a_byte()
{
	// the file must be opened before calling this
	assert(m_file_pointer != NULL);

	unsigned char byte;
	size_t read_size;
	read_size = SDL_RWread(m_file_pointer, &byte, 1, 1);

	return byte;
}

/*
 * read a block of data
 */
size_t SDLFile::read(void *pbuffer, size_t data_size)
{
	// the file must be opened before calling this
	assert(m_file_pointer != NULL);

	return SDL_RWread(m_file_pointer, pbuffer, 1, data_size);
}

