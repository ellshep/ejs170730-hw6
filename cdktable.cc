/*
 * Filename:            cdktable.cc
 * Date:                11/25/2020
 * Author:              Ellington Shephard
 * Email:               ejs170730@utdallas.edu
 * Class:               CS 3377.001
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *      Build and display a CDK GUI that reads from binary file
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include "cdk.h"
//#include "binread.h"

/*
 * For grins and giggles, we will define values using the C
 * Preprocessor instead of C or C++ data types.  These symbols (and
 * their values) get inserted into the Preprocessor's symbol table.
 * The names are replaced by their values when seen later in the code.
 */

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

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


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // CDK uses offset 1 and C/C++ use offset 0.  Therefore, we create one more 
  // slot than necessary and ignore the value at location 0.
  const char 		*rowTitles[MATRIX_ROWS+1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_COLS+1] = {"IGNORE", "a", "b", "c"};
  int		colWidths[MATRIX_COLS+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_COLS+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  //read binary file header
  BinaryFileHeader* myHeader = new BinaryFileHeader();

  ifstream binInfile;
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  
  //set table titles
  stringstream magNum; 
  magNum << hex << uppercase << myHeader->magicNumber;
  string magNumStr = "Magic: 0x" + magNum.str();   
  setCDKMatrixCell(myMatrix, 1, 1, magNumStr.c_str());

  stringstream vers; 
  vers << dec << myHeader->versionNumber; 
  string versStr = "Version: " + vers.str(); 
  setCDKMatrixCell(myMatrix, 1, 2, versStr.c_str()); 

  stringstream rec; 
  rec << dec << myHeader->numRecords; 
  string recStr = "NumRecords: " + rec.str(); 
  setCDKMatrixCell(myMatrix, 1, 3, recStr.c_str());

  //read binary file records
  const int numRecs = stoi(rec.str()); 
  BinaryFileRecord myRecords[numRecs];

  int row = 2; 
  for(int i=0; i < numRecs; i++)
  {
    binInfile.read((char *) &myRecords[i], sizeof(BinaryFileRecord));
    stringstream strLen;
    strLen << hex << myRecords[i].strLength;
    string strLenStr = "strlen: " + strLen.str();
    setCDKMatrixCell(myMatrix, row, 1, strLenStr.c_str());

    stringstream text; 
    test << hex << myRecords[i].stringBuffer[maxRecordStringLength];

    row++; 
  }
  binInfile.close(); 

  drawCDKMatrix(myMatrix, true);    /* required  */

  binInfile.close(); 

  /* so we can see results */
  sleep (5);


  // Cleanup screen
  endCDK();
}
