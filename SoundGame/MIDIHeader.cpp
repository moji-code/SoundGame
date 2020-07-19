//
//  MIDIHeader.cpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <iostream>
using namespace std;

#include <string.h>

#include "MIDIHeader.hpp"

/*
 * constructer
 */
MIDIHeader::MIDIHeader()
{
	m_header_length = 0;
	m_format = 0;
	m_num_of_tracks = 0;
	m_time_base = 0;
}

/*
 * read header information
 */
bool MIDIHeader::read(MIDIFile *pfile)
{
	// if header ID was wrong
	if (pfile->check_header_ID("MThd") == false)
	{
		// return false
		return false;
	}

	// read following parameters from MIDI header
	m_header_length = pfile->read_sequential_data(4);	// header length
	m_format = pfile->read_sequential_data(2);			// format
	m_num_of_tracks = pfile->read_sequential_data(2);	// number of tracks
	m_time_base = pfile->read_sequential_data(2);		// time base

	return true;
}

/*
 * show header information
 */
void MIDIHeader::show()
{
	cout << "MThd" << endl;
	cout << "length: " << m_header_length << endl;
	cout << "format: " << m_format << endl;
	cout << "num of tracks: " << m_num_of_tracks << endl;
	cout << "time base: " << m_time_base << endl;
}
