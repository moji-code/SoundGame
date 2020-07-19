//
//  SDLFile.hpp
//  readSMF
//
//  Created by mojito on 2020/06/08.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef SDLFile_hpp
#define SDLFile_hpp

#include <string>
#include "sdl.h"

using namespace std;

class SDLFile
{
protected:
	SDL_RWops* m_file_pointer;

public:
	SDLFile();
	~SDLFile();
	virtual bool open(string filepath);
	virtual void close();
	virtual bool eof();
	virtual unsigned char get_a_byte();
	virtual size_t read(void *pbuffer, size_t data_size);
};

#endif /* SDLFile_hpp */
