//
//  utage.h
//  SoundGame
//
//  Created by mojito on 2020/08/07.
//  Copyright © 2020 mojito. All rights reserved.
//

#ifndef utage_h
#define utage_h

/*
 * magnification
 */
#define GAME_BLOCK_SIZE_BY_DOT	(20)
#define GAME_MAGNIFICATION		(2)

/*
 * numbers
 */
#define GAME_NUM_OF_LANES		(4)
#define MIDI_FIRST_NOTE_NUMBER	(72)

/*
 * positions
 */
#define GAME_LANE_TOP_BY_BLOCK		(1)
#define GAME_LANE_LEFT_BY_BLOCK		(1)
#define GAME_LANE_BOTTOM_BY_BLOCK	(20)
#define GAME_LANE_RIGHT_BY_BLOCK	(8)

#define GAME_LANE_TOP_BY_DOT		(GAME_LANE_TOP_BY_BLOCK    * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_LANE_LEFT_BY_DOT		(GAME_LANE_LEFT_BY_BLOCK   * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_LANE_BOTTOM_BY_DOT		(GAME_LANE_BOTTOM_BY_BLOCK * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_LANE_RIGHT_BY_DOT		(GAME_LANE_RIGHT_BY_BLOCK  * GAME_BLOCK_SIZE_BY_DOT)

#define GAME_HIT_POSITION_FROM_BOTTOM_BY_BLOCK	(3)
#define GAME_HIT_POSITION_FROM_BOTTOM_BY_DOT	(GAME_HIT_POSITION_FROM_BOTTOM_BY_BLOCK * GAME_BLOCK_SIZE_BY_DOT)

/*
 * sizes
 */
// game screen
#define GAME_WIDTH_BY_BLOCK		(10)
#define GAME_HEIGHT_BY_BLOCK	(20)
#define GAME_WIDTH_BY_DOT		(GAME_WIDTH_BY_BLOCK  * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_HEIGHT_BY_DOT		(GAME_HEIGHT_BY_BLOCK * GAME_BLOCK_SIZE_BY_DOT)

// notes
#define GAME_NOTE_WIDTH_BY_BLOCK	(2)
#define GAME_NOTE_HEIGHT_BY_BLOCK	(1)
#define GAME_NOTE_WIDTH_BY_DOT		(GAME_NOTE_WIDTH_BY_BLOCK  * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_NOTE_HEIGHT_BY_DOT		(GAME_NOTE_HEIGHT_BY_BLOCK * GAME_BLOCK_SIZE_BY_DOT)

// lane
#define GAME_LANE_WIDTH_BY_BLOCK	(2)
#define GAME_LANE_HEIGHT_BY_BLOCK	(20)
#define GAME_LANE_WIDTH_BY_DOT		(GAME_LANE_WIDTH_BY_BLOCK  * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_LANE_HEIGHT_BY_DOT		(GAME_LANE_HEIGHT_BY_BLOCK * GAME_BLOCK_SIZE_BY_DOT)
#define GAME_LANE_EDGE_WIDTH		(6)


// timings
// *** following num of measers in a lane decide note velocity ***
#define TIMING_MEASURES_IN_LANE				(1.2)		// num of measures in lane height
//
#define TIMING_FRAME_TIME					(10.)		// milli sec
#define TIMING_STANDARD_TEMPO				(120.)		// odoru ponpokorin's
#define TIMING_LANE_HEIGHT_TIME_IN_MILLI_SEC	(60./TIMING_STANDARD_TEMPO*1000*4*TIMING_MEASURES_IN_LANE)

#if 0
	// following velocity is that a note moves GAME_LANE_HEIGHT_BY_DOT in 1000 milli sec
	#define NOTE_VELOCITY			(GAME_LANE_HEIGHT_BY_DOT / 1000.)	// dot / milli second
	/*
	 * counter_of_note_draw = 0;
	 *	:
	 * loop()
	 * {
	 *	counter_of_note_draw++;
	 * 	if (counter_of_note_draw == NOTE_DRAW_CYCLE)
	 * 	{
	 *		draw_note();
	 *		counter_of_note_draw = 0;
	 * 	}
	 * }
	 */
	#define NOTE_DRAW_CYCLE			(NOTE_VELOCITY / FRAME_TIME)		// frames a draw
#endif

#endif /* utage_h */
