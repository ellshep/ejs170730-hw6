/* Filename   binread.h
 * Date       11/25/2020
 * Author     Ellington Shephard
 * Email      ejs170730@utdallas.edu
 * Course     CS 3377.001 Fall 2020
 * Version    1.0
 * Copyright  2020, All Rights Reserved 
 *
 * Description 
 *
 *    Header file for project6 binread.cc that reads from a binary file
 */

#ifndef binread
#define binread

#include <stdint.h> 

class BinaryFileHeader
{
 public:
  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

extern BinaryFileHeader* myRecord; 
void binRead(); 

#endif
