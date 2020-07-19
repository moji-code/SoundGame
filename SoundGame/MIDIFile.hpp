//
//  MIDIFile.hpp
//  readSMF2
//
//  Created by mojito on 2020/06/16.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef MIDIFile_hpp
#define MIDIFile_hpp

#include "sdl.h"
#include "SDLFile.hpp"

class MIDIFile : public SDLFile
{
public:
	unsigned long read_sequential_data(int num_of_bytes);
	unsigned long read_variable_length_data();
	bool check_header_ID(string id);
};

#endif /* MIDIFile_hpp */
