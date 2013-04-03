/******************************************************************************
 * Autonomous.h - Autonomous helpers
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * In this mode, we shoot our 3 starting frisbees then stop.
 *
 ******************************************************************************/

#define CURRENT_TIME GetClock() - startTime

#define ADVANCE_TO_NEXT_STEP \
    step++; \
    startTime = GetClock()
