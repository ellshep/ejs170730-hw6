#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>

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
  BinaryFileHeader *myRecord = new BinaryFileHeader();

  ifstream binInfile; 
  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myRecord, sizeof(myRecord));
  cout << "MAGIC: " << std::hex << std::uppercase <<  myRecord->magicNumber << endl;
  cout << "Version: " << std::dec << myRecord->versionNumber << endl; 
  cout << "NumRecords: " << std::dec << myRecord->numRecords << endl; 

  binInfile.close(); 
  return 0;
}
