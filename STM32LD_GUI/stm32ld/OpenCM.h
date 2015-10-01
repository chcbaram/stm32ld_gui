// Portable types

#ifndef __OPENCM_MAIN_H_
#define __OPENCM_MAIN_H_


#include "type.h"

int OpenCM_main( int argc, const char **argv );

int OpenCM_Cmd_Init( const char *portname, u32 baud );
int OpenCM_Cmd_SendCommand( char *CmdStr );
int OpenCM_Cmd_ReadResponse( char *CmdStr, int TimeOut );
int OpenCM_Cmd_SendCmdRecvResponse( char *CmdStr, char *RecvStr, int TimeOut );

int  OpenCM_WriteFlash( p_read_data read_data_func, p_progress progress_func );
void OpenCM_Wait_ms( int WaitTime );

u32 OpenCM_writeh_read_data( u8 *dst, u32 len );


#endif

