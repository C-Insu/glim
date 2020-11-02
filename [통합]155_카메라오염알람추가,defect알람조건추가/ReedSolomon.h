#ifndef __REEDSOLOMON_H__
#define __REEDSOLOMON_H__

#define DATAMATRIX	0
#define QRCODE		1

void InitLogTables();
int CorrectErrs(unsigned char *code,int data_size,int check_size,int inter_size,int symbol_type);

#endif



