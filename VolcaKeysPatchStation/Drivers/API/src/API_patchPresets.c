/*
 * API_patchPresets.c
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */
#include "API_patchPreset.h"

static midiPatch_t preLoadedPset[MAX_PRESETS];


/**
 * Presets tomados de
 * https://www.volcashare.com/keys/patches
 */

void patchPreset_init(void) {

	preLoadedPset[0].name = "Dark Massive";

	preLoadedPset[0].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[0].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[0].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[0].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[0].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[0].param[PARAM_VOICE].value = 70;
	preLoadedPset[0].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[0].param[PARAM_OCTAVE].value = 2;
	preLoadedPset[0].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[0].param[PARAM_DETUNE].value = 19;
	preLoadedPset[0].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[0].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[0].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[0].param[PARAM_CUTOFF].value = 127;
	preLoadedPset[0].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[0].param[PARAM_VCF_EG_INT].value = 98;
	preLoadedPset[0].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[0].param[PARAM_LFO_RATE].value = 127;
	preLoadedPset[0].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[0].param[PARAM_LFO_PITCH_INT].value = 76;
	preLoadedPset[0].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[0].param[PARAM_LFO_CUTOFF_INT].value = 72;
	preLoadedPset[0].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[0].param[PARAM_EG_ATTACK].value = 19;
	preLoadedPset[0].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[0].param[PARAM_EG_DEC_REL].value = 79;
	preLoadedPset[0].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[0].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[0].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[0].param[PARAM_DELAY_TIME].value = 127;
	preLoadedPset[0].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[0].param[PARAM_DELAY_FEEDBACK].value = 127;

	/************************************************************/

	preLoadedPset[1].name = "Poly_Patch_1";

	preLoadedPset[1].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[1].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[1].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[1].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[1].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[1].param[PARAM_VOICE].value = 10;
	preLoadedPset[1].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[1].param[PARAM_OCTAVE].value = 70;
	preLoadedPset[1].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[1].param[PARAM_DETUNE].value = 0;
	preLoadedPset[1].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[1].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[1].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[1].param[PARAM_CUTOFF].value = 127;
	preLoadedPset[1].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[1].param[PARAM_VCF_EG_INT].value = 0;
	preLoadedPset[1].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[1].param[PARAM_LFO_RATE].value = 0;
	preLoadedPset[1].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[1].param[PARAM_LFO_PITCH_INT].value = 0;
	preLoadedPset[1].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[1].param[PARAM_LFO_CUTOFF_INT].value = 0;
	preLoadedPset[1].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[1].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[1].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[1].param[PARAM_EG_DEC_REL].value = 0;
	preLoadedPset[1].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[1].param[PARAM_EG_SUSTAIN].value = 69;
	preLoadedPset[1].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[1].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[1].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[1].param[PARAM_DELAY_FEEDBACK].value = 0;

	/************************************************************/

	preLoadedPset[2].name = "Bobin";

	preLoadedPset[2].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[2].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[2].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[2].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[2].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[2].param[PARAM_VOICE].value = 10;
	preLoadedPset[2].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[2].param[PARAM_OCTAVE].value = 40;
	preLoadedPset[2].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[2].param[PARAM_DETUNE].value = 0;
	preLoadedPset[2].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[2].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[2].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[2].param[PARAM_CUTOFF].value = 63;
	preLoadedPset[2].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[2].param[PARAM_VCF_EG_INT].value = 38;
	preLoadedPset[2].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[2].param[PARAM_LFO_RATE].value = 0;
	preLoadedPset[2].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[2].param[PARAM_LFO_PITCH_INT].value = 0;
	preLoadedPset[2].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[2].param[PARAM_LFO_CUTOFF_INT].value = 0;
	preLoadedPset[2].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[2].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[2].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[2].param[PARAM_EG_DEC_REL].value = 0;
	preLoadedPset[2].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[2].param[PARAM_EG_SUSTAIN].value = 48;
	preLoadedPset[2].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[2].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[2].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[2].param[PARAM_DELAY_FEEDBACK].value = 0;

/************************************************************/

	preLoadedPset[3].name = "Soviet ghost";

	preLoadedPset[3].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[3].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[3].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[3].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[3].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[3].param[PARAM_VOICE].value = 10;
	preLoadedPset[3].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[3].param[PARAM_OCTAVE].value = 70;
	preLoadedPset[3].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[3].param[PARAM_DETUNE].value = 23;
	preLoadedPset[3].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[3].param[PARAM_VCO_EG_INT].value = 14;
	preLoadedPset[3].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[3].param[PARAM_CUTOFF].value = 46;
	preLoadedPset[3].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[3].param[PARAM_VCF_EG_INT].value = 102;
	preLoadedPset[3].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[3].param[PARAM_LFO_RATE].value = 68;
	preLoadedPset[3].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[3].param[PARAM_LFO_PITCH_INT].value = 23;
	preLoadedPset[3].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[3].param[PARAM_LFO_CUTOFF_INT].value = 0;
	preLoadedPset[3].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[3].param[PARAM_EG_ATTACK].value = 76;
	preLoadedPset[3].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[3].param[PARAM_EG_DEC_REL].value = 117;
	preLoadedPset[3].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[3].param[PARAM_EG_SUSTAIN].value = 46;
	preLoadedPset[3].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[3].param[PARAM_DELAY_TIME].value = 127;
	preLoadedPset[3].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[3].param[PARAM_DELAY_FEEDBACK].value = 127;

/************************************************************/

	preLoadedPset[4].name = "Hungry Cat5";

	preLoadedPset[4].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[4].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[4].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[4].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[4].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[4].param[PARAM_VOICE].value = 30;
	preLoadedPset[4].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[4].param[PARAM_OCTAVE].value = 90;
	preLoadedPset[4].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[4].param[PARAM_DETUNE].value = 0;
	preLoadedPset[4].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[4].param[PARAM_VCO_EG_INT].value = 75;
	preLoadedPset[4].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[4].param[PARAM_CUTOFF].value = 38;
	preLoadedPset[4].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[4].param[PARAM_VCF_EG_INT].value = 103;
	preLoadedPset[4].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[4].param[PARAM_LFO_RATE].value = 15;
	preLoadedPset[4].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[4].param[PARAM_LFO_PITCH_INT].value = 36;
	preLoadedPset[4].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[4].param[PARAM_LFO_CUTOFF_INT].value = 23;
	preLoadedPset[4].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[4].param[PARAM_EG_ATTACK].value = 80;
	preLoadedPset[4].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[4].param[PARAM_EG_DEC_REL].value = 127;
	preLoadedPset[4].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[4].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[4].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[4].param[PARAM_DELAY_TIME].value = 101;
	preLoadedPset[4].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[4].param[PARAM_DELAY_FEEDBACK].value = 98;

/************************************************************/

	preLoadedPset[5].name = "Pumpy BASS";

	preLoadedPset[5].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[5].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[5].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[5].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[5].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[5].param[PARAM_VOICE].value = 30;
	preLoadedPset[5].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[5].param[PARAM_OCTAVE].value = 30;
	preLoadedPset[5].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[5].param[PARAM_DETUNE].value = 29;
	preLoadedPset[5].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[5].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[5].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[5].param[PARAM_CUTOFF].value = 53;
	preLoadedPset[5].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[5].param[PARAM_VCF_EG_INT].value = 0;
	preLoadedPset[5].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[5].param[PARAM_LFO_RATE].value = 76;
	preLoadedPset[5].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[5].param[PARAM_LFO_PITCH_INT].value = 0;
	preLoadedPset[5].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[5].param[PARAM_LFO_CUTOFF_INT].value = 0;
	preLoadedPset[5].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[5].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[5].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[5].param[PARAM_EG_DEC_REL].value = 48;
	preLoadedPset[5].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[5].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[5].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[5].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[5].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[5].param[PARAM_DELAY_FEEDBACK].value = 127;

/************************************************************/

	preLoadedPset[6].name = "Alien keys";

	preLoadedPset[6].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[6].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[6].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[6].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[6].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[6].param[PARAM_VOICE].value = 50;
	preLoadedPset[6].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[6].param[PARAM_OCTAVE].value = 70;
	preLoadedPset[6].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[6].param[PARAM_DETUNE].value = 30;
	preLoadedPset[6].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[6].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[6].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[6].param[PARAM_CUTOFF].value = 31;
	preLoadedPset[6].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[6].param[PARAM_VCF_EG_INT].value = 63;
	preLoadedPset[6].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[6].param[PARAM_LFO_RATE].value = 0;
	preLoadedPset[6].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[6].param[PARAM_LFO_PITCH_INT].value = 0;
	preLoadedPset[6].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[6].param[PARAM_LFO_CUTOFF_INT].value = 0;
	preLoadedPset[6].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[6].param[PARAM_EG_ATTACK].value = 127;
	preLoadedPset[6].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[6].param[PARAM_EG_DEC_REL].value = 127;
	preLoadedPset[6].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[6].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[6].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[6].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[6].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[6].param[PARAM_DELAY_FEEDBACK].value = 53;

/************************************************************/

	preLoadedPset[7].name = "Spaceship Hover";

	preLoadedPset[7].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[7].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[7].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[7].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[7].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[7].param[PARAM_VOICE].value = 120;
	preLoadedPset[7].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[7].param[PARAM_OCTAVE].value = 50;
	preLoadedPset[7].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[7].param[PARAM_DETUNE].value = 0;
	preLoadedPset[7].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[7].param[PARAM_VCO_EG_INT].value = 0;
	preLoadedPset[7].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[7].param[PARAM_CUTOFF].value = 82;
	preLoadedPset[7].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[7].param[PARAM_VCF_EG_INT].value = 0;
	preLoadedPset[7].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[7].param[PARAM_LFO_RATE].value = 102;
	preLoadedPset[7].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[7].param[PARAM_LFO_PITCH_INT].value = 82;
	preLoadedPset[7].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[7].param[PARAM_LFO_CUTOFF_INT].value = 72;
	preLoadedPset[7].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[7].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[7].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[7].param[PARAM_EG_DEC_REL].value = 63;
	preLoadedPset[7].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[7].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[7].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[7].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[7].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[7].param[PARAM_DELAY_FEEDBACK].value = 0;

/************************************************************/

	preLoadedPset[8].name = "AcidAdjacentLead";

	preLoadedPset[8].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[8].param[PARAM_PORTAMENTO].value = 39;
	preLoadedPset[8].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[8].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[8].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[8].param[PARAM_VOICE].value = 70;
	preLoadedPset[8].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[8].param[PARAM_OCTAVE].value = 50;
	preLoadedPset[8].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[8].param[PARAM_DETUNE].value = 30;
	preLoadedPset[8].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[8].param[PARAM_VCO_EG_INT].value = 34;
	preLoadedPset[8].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[8].param[PARAM_CUTOFF].value = 24;
	preLoadedPset[8].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[8].param[PARAM_VCF_EG_INT].value = 94;
	preLoadedPset[8].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[8].param[PARAM_LFO_RATE].value = 97;
	preLoadedPset[8].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[8].param[PARAM_LFO_PITCH_INT].value = 127;
	preLoadedPset[8].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[8].param[PARAM_LFO_CUTOFF_INT].value = 104;
	preLoadedPset[8].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[8].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[8].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[8].param[PARAM_EG_DEC_REL].value = 0;
	preLoadedPset[8].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[8].param[PARAM_EG_SUSTAIN].value = 127;
	preLoadedPset[8].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[8].param[PARAM_DELAY_TIME].value = 0;
	preLoadedPset[8].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[8].param[PARAM_DELAY_FEEDBACK].value = 20;

/************************************************************/

	preLoadedPset[9].name = "Polyring(arp)";

	preLoadedPset[9].param[PARAM_PORTAMENTO].ctrlNum = CTRL_CHG_NUM_PORTAMENTO;
	preLoadedPset[9].param[PARAM_PORTAMENTO].value = 0;
	preLoadedPset[9].param[PARAM_EXPRESSION].ctrlNum = CTRL_CHG_NUM_EXPRESSION;
	preLoadedPset[9].param[PARAM_EXPRESSION].value = 127;
	preLoadedPset[9].param[PARAM_VOICE].ctrlNum = CTRL_CHG_NUM_VOICE;
	preLoadedPset[9].param[PARAM_VOICE].value = 120;
	preLoadedPset[9].param[PARAM_OCTAVE].ctrlNum = CTRL_CHG_NUM_OCTAVE;
	preLoadedPset[9].param[PARAM_OCTAVE].value = 70;
	preLoadedPset[9].param[PARAM_DETUNE].ctrlNum = CTRL_CHG_NUM_DETUNE;
	preLoadedPset[9].param[PARAM_DETUNE].value = 20;
	preLoadedPset[9].param[PARAM_VCO_EG_INT].ctrlNum = CTRL_CHG_NUM_VCO_EG_INT;
	preLoadedPset[9].param[PARAM_VCO_EG_INT].value = 15;
	preLoadedPset[9].param[PARAM_CUTOFF].ctrlNum = CTRL_CHG_NUM_CUTOFF;
	preLoadedPset[9].param[PARAM_CUTOFF].value = 0;
	preLoadedPset[9].param[PARAM_VCF_EG_INT].ctrlNum = CTRL_CHG_NUM_VCF_EG_IN;
	preLoadedPset[9].param[PARAM_VCF_EG_INT].value = 127;
	preLoadedPset[9].param[PARAM_LFO_RATE].ctrlNum = CTRL_CHG_NUM_LFO_RATE;
	preLoadedPset[9].param[PARAM_LFO_RATE].value = 20;
	preLoadedPset[9].param[PARAM_LFO_PITCH_INT].ctrlNum = CTRL_CHG_NUM_LFO_PITCH_INT;
	preLoadedPset[9].param[PARAM_LFO_PITCH_INT].value = 34;
	preLoadedPset[9].param[PARAM_LFO_CUTOFF_INT].ctrlNum = CTRL_CHG_NUM_LFO_CUTOFF_INT;
	preLoadedPset[9].param[PARAM_LFO_CUTOFF_INT].value = 64;
	preLoadedPset[9].param[PARAM_EG_ATTACK].ctrlNum = CTRL_CHG_NUM_EG_ATTACK;
	preLoadedPset[9].param[PARAM_EG_ATTACK].value = 0;
	preLoadedPset[9].param[PARAM_EG_DEC_REL].ctrlNum = CTRL_CHG_NUM_EG_DEC_REL;
	preLoadedPset[9].param[PARAM_EG_DEC_REL].value = 92;
	preLoadedPset[9].param[PARAM_EG_SUSTAIN].ctrlNum = CTRL_CHG_NUM_EG_SUSTAIN;
	preLoadedPset[9].param[PARAM_EG_SUSTAIN].value = 93;
	preLoadedPset[9].param[PARAM_DELAY_TIME].ctrlNum = CTRL_CHG_NUM_DELAY_TIME;
	preLoadedPset[9].param[PARAM_DELAY_TIME].value = 127;
	preLoadedPset[9].param[PARAM_DELAY_FEEDBACK].ctrlNum = CTRL_CHG_NUM_DELAY_FEEDBACK;
	preLoadedPset[9].param[PARAM_DELAY_FEEDBACK].value = 127;
}

midiPatch_t* patchPreset_getPresets(void) {
	return preLoadedPset;
}

