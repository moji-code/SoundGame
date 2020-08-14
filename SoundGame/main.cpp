/*

 */

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

#include "SDLEnvironment.hpp"

#include "SDLFile.hpp"
#include "MIDIFile.hpp"
#include "MIDIHeader.hpp"
#include "MIDITrack.hpp"
#include "MIDIData.hpp"

#include "UtageNoteArray.hpp"
#include "UtageNotesShow.hpp"

#define MIDIFILENAME	"honey rush(utage notes).mid"
//#define MIDIFILENAME	"midi_notes_sample.mid"
#define AUDIOFILENAME	"honey rush.mp3"

int main(int argc, const char * argv[])
{
	/*
	 * read MIDI data
	 */
	MIDIData midi_data;
	midi_data.read(MIDIFILENAME);
	midi_data.show();

	/*
	 * reconstruct midi notes for utage
	 */
	UtageNoteArray notes;
	notes.create(&midi_data);
	notes.show();

	/*
	 * show notes!
	 */
	UtageNotesShow show;
	show.set_notes(&notes);
	show.load_audio(AUDIOFILENAME);
	show.run();

	return 0;
}
