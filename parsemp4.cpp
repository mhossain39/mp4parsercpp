#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "curl_download.hpp"

using namespace std;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

bool read32( ifstream& f, uint32_t& n) {
    f.read((char*)&n, sizeof n);
    n = n >> 24 | n << 24 | (n >> 8 & 0xff00) | (n << 8 & 0xff0000);
    return bool(f);
}

string print_chars(uint32_t n) {    // assumes little-endian
  char bytes[4];
  bytes[0] = (char)(n >> 24);  
  bytes[1] = (char)(n >> 16 & 0xff);
  bytes[2] = (char)(n >>  8 & 0xff);  
  bytes[3] = (char)(n       & 0xff);
  
  string str(bytes);
  return str;
}

int main() {
	
	string str;
	bool downlod_result;
	char * memblock;

	downlod_result = download("https://demo.castlabs.com/tmp/text0.mp4", "text0.mp4");
	if(!downlod_result)
		{  cerr << currentDateTime()<< " Failed to download file https://demo.castlabs.com/tmp/text0.mp4 \n"; return 1; }
	else{
		
		cout << currentDateTime()<< " Successfully loaded file https://demo.castlabs.com/tmp/text0.mp4 \n";
	}
 
     ifstream f("text0.mp4", f.in|f.binary);
    if (!f) {  cerr << currentDateTime()<< " Cannot open file.\n"; return 1; }
 
    for (uint32_t size; read32(f, size); ) {
        uint32_t type;
        read32(f, type);
        str = print_chars(type);
       cout << currentDateTime()<< " Found box of type "<< str << " and size " << size << '\n';
		if (str.compare("moof")==0 || str.compare("traf")==0)
			continue;
		else if (str.compare("mdat")==0){
				memblock = new char [size];
				f.read(memblock, size);
				cout << currentDateTime()<< " Content of mdat box is: "<< memblock << '\n';
		}
		else
        f.ignore(size - 8);
    }
	f.close();
	const int result = remove( "text0.mp4" );

	return 0;

}
