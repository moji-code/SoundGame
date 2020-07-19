//
//  main.cpp
//  SoundGame
//
//  Created by mojito on 2020/06/22.
//  Copyright © 2020 mojito. All rights reserved.
//

#include <vector>
#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

#include "SDLFile.hpp"
#include "MIDIFile.hpp"
#include "MIDIHeader.hpp"
#include "MIDITrack.hpp"
#include "MIDIData.hpp"

#include "UtageNoteArray.hpp"

//#define MIDIFILENAME	"midi_notes_sample.mid"
#define MIDIFILENAME	"midi_notes_sample_chord.mid"

int main(int argc, const char * argv[])
{
	/*
	 * read midi file
	 */
	MIDIFile midi_file;
	// if failed to open the file
	if (midi_file.open(MIDIFILENAME) == false)
	{
		// show the error message and return
		cout << "could not open: " << MIDIFILENAME << endl;
		return -1;
	}
	MIDIData midi_data;
	midi_data.read(&midi_file);
	midi_data.show();
	
	/*
	 * reconstruct midi notes for utage
	 */
	UtageNoteArray notes;
	notes.create(&midi_data);
	notes.show();

	return 0;
}
