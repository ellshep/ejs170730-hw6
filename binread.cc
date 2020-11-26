/*
 *Filename    binread.cc
 *Date        11/25/2020
 *Author      Ellington Shephard
 *Email       ejs170730@utdallas.edu
 *Course      CS 3377.001 Fall 2020
 *Version     1.0
 *Copyright   2020, All Rights Reserved
 *
 *Description
 *
 *    Reads binary file for project6
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include "binread.h"

using namespace std;

BinaryFileHeader* myRecord = new BinaryFileHeader();

void binRead()
{

  ifstream binInfile; 
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myRecord, sizeof(BinaryFileHeader));
  cout << "MAGIC: " << std::hex << std::uppercase <<  myRecord->magicNumber << endl;
  cout << "Version: " << std::dec << myRecord->versionNumber << endl; 
  cout << "NumRecords: " << std::hex << myRecord->numRecords << endl; 

  binInfile.close(); 
}
