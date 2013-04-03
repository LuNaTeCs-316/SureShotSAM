/******************************************************************************
 * Autonomous.h - Autonomous helpers
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * Contains code common to all of the autonomous routines
 *
 ******************************************************************************/

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

#define CURRENT_TIME GetClock() - startTime

#define ADVANCE_TO_NEXT_STEP \
    step++; \
    startTime = GetClock()

#endif