//
//  MIDIFile.cpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#include "MIDIFile.hpp"

/*
 * read sequential bytes like the length number in header section of MIDI file
 */
unsigned long MIDIFile::read_fixed_length_data(int num_of_bytes)
{
	unsigned char byte;
	unsigned long value = 0;
	
	for (int current_index = 0; current_index < num_of_bytes; current_index++)
	{
		byte = get_a_byte();
		value = value << 8;
		value = value | byte;
	}
	
	return value;
}

/*
 * read variable length data like delta time
 */
unsigned long MIDIFile::read_variable_length_data()
{
	unsigned char byte;
	unsigned long value = 0;
	
	do
	{
		byte = get_a_byte();

		value = value << 7;
		value = value | (byte & 0x7f);
		
	} while ((byte & 0x80) != 0);
	
	return value;
}

/*
 * check ID of headers like midi file header or tracks
 */
bool MIDIFile::check_header_ID(string id)
{
	// while itr is in the string of id
	for (auto itr = id.begin(); itr != id.end(); itr++)
	{
		// if id was not identical after comparing one from file and one that itr is pointing
		if (get_a_byte() != (*itr))
		{
			// return false
			return false;
		}
	}
	
	// if passed above loop, return true
	return true;
}
