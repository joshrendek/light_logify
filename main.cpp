/* 
 Copyright Josh Rendek 2009
 http://bluescripts.net/
 Not liable for anything
 1m6sec to process a 1.8GB File
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator> 

using namespace std;

class Log {
	string fileName;
	ifstream logFile; 
	string logLine;
	vector<string> ipList, ipListUnique;
	
	/* prototypes */
	void openFile();
	string findIP(string);
	double FileSize(const char*);
public:
	/* Prototypes & Constructor */
	Log(string); // constructor
	~Log(){ cout << "Logify deconstructed" << endl; }; // deconstructor
	void showFileName(void); // show the filename
	void go(void); // do it!
	
};
// Constructor
Log::Log(string file){
	fileName = file;
}
// output the fileName
void Log::showFileName()  {
	cout << fileName << endl;
}
// open the file, stop if error
void Log::openFile(){
	logFile.open(fileName.c_str());
	if(logFile.fail()){
		cout << "File not found " << endl; 
		exit(-1); // stop
	}
}
// parse the IP from the line
string Log::findIP(string line){
	string::size_type size = line.length();
	string tmp;
	for(string::size_type x = 0; x<size; x++){
		/* IPs end after the last integer and a space */
		if(isnumber(line[x]) || line[x] == '.'){
			tmp += line[x];
		}
		if(isspace(line[x])) break;
	}
	
	return tmp;
}
// size of the log file
double Log::FileSize(const char* sFileName)
{
	std::ifstream f;
	f.open(sFileName, std::ios_base::binary | std::ios_base::in);
	if (!f.good() || f.eof() || !f.is_open()) { return 0; }
	f.seekg(0, std::ios_base::beg);
	std::ifstream::pos_type begin_pos = f.tellg();
	f.seekg(0, std::ios_base::end);
	return static_cast<double>( (f.tellg() - begin_pos))/1024/1024/1024;
}
// where the action happens
void Log::go(){
	cout << "Opening " << fileName << " to be analyzed. " << endl;
	this->openFile();
	while (!logFile.eof()) {
			getline(logFile, logLine);
			ipList.push_back(this->findIP(logLine)); // add to vector
	}
	
	// get unique IPs out of the array
	unique_copy( ipList.begin(), ipList.end(), back_inserter( ipListUnique ) );
	cout << "----------------------------------------" << endl;
	cout << "File size: " << this->FileSize(fileName.c_str()) << "GB" << endl; 
	cout << "Unique IPs: " << ipListUnique.size() << endl;
	cout << "----------------------------------------" << endl;	
}

int main (int argc, char * const argv[]) {
	for (int x = 1; x < argc; x++) {
		Log Logify(argv[x]);
		Logify.go();
	}
	return 0;
}