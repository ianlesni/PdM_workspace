/*
 * patchPreset.h
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#ifndef INC_API_PATCHPRESET_H_
#define INC_API_PATCHPRESET_H_

#include <stdint.h>

#define MAX_PARAMENTERS		PARAM_COUNT
#define MAX_PRESETS			10

typedef enum {
    PARAM_PORTAMENTO = 0,
    PARAM_EXPRESSION,
    PARAM_VOICE,
    PARAM_OCTAVE,
    PARAM_DETUNE,
    PARAM_VCO_EG_INT,
    PARAM_CUTOFF,
    PARAM_VCF_EG_INT,
    PARAM_LFO_RATE,
    PARAM_LFO_PITCH_INT,
    PARAM_LFO_CUTOFF_INT,
    PARAM_EG_ATTACK,
    PARAM_EG_DEC_REL,
    PARAM_EG_SUSTAIN,
    PARAM_DELAY_TIME,
    PARAM_DELAY_FEEDBACK,

    PARAM_COUNT
} patchParameter_t;

#define CTRL_CHG_NUM_PORTAMENTO 		5
#define CTRL_CHG_NUM_EXPRESSION			11
#define CTRL_CHG_NUM_VOICE				40
#define CTRL_CHG_NUM_OCTAVE				41
#define CTRL_CHG_NUM_DETUNE				42
#define CTRL_CHG_NUM_VCO_EG_INT			43
#define CTRL_CHG_NUM_CUTOFF				44
#define CTRL_CHG_NUM_VCF_EG_IN			45
#define CTRL_CHG_NUM_LFO_RATE			46
#define CTRL_CHG_NUM_LFO_PITCH_INT		47
#define CTRL_CHG_NUM_LFO_CUTOFF_INT		48
#define CTRL_CHG_NUM_EG_ATTACK			49
#define CTRL_CHG_NUM_EG_DEC_REL			50
#define CTRL_CHG_NUM_EG_SUSTAIN			51
#define CTRL_CHG_NUM_DELAY_TIME			52
#define CTRL_CHG_NUM_DELAY_FEEDBACK		53

typedef struct {
	uint8_t ctrlNum;
	uint8_t value;
}midiCtrlChange_t;

typedef struct {
	const char *name;
	midiCtrlChange_t param[MAX_PARAMENTERS];
}midiPatch_t;



void patchPreset_init(void);
midiPatch_t* patchPreset_getPresets(void);




#endif /* INC_API_PATCHPRESET_H_ */
