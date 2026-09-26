/*
 * API_cmdparser.h
 *
 *  Created on: 26 sept 2026
 *      Author: ianle
 */

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_

#define CMD_MAX_LINE 64 // incluye el '\0'

typedef enum {
	CMD_OK = 0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOWN,
	CMD_ERR_ARG
} cmd_status_t;

void cmdParserInit(void);
void cmdPoll(void);
void cmdPrintHelp(void);

#endif /* API_INC_API_CMDPARSER_H_ */
