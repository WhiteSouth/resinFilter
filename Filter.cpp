#include "Filter.h"
using namespace std;
using namespace cv;

resinFilter::resinFilter()
{

}



vector<string>resinFilter::pathGet(string filepath, string postFix)
{
	_finddata_t fileDir;
	intptr_t lfDir; //long lfDir±¨´í
	vector<string> testpath;
	char filename[128];
	postFix = "\\*." + postFix;
	strcpy_s(filename, filepath.c_str());
	strcat_s(filename, postFix.c_str());
	if ((lfDir = _findfirst(filename, &fileDir)) == -1l)
		printf("No file is found\n");
	else {
		do {
			char name[256];
			strcpy_s(name, filepath.c_str());
			strcat_s(name, "\\");
			strcat_s(name, fileDir.name);
			testpath.push_back(name);
		} while (_findnext(lfDir, &fileDir) == 0);
	}
	_findclose(lfDir);
	return testpath;
}

resinFilter::~resinFilter()
{
}