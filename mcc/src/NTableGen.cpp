#include <time.h>
#include <iostream>
#include "LOOSEExtractor.h"

int main(int argc,char *argv[]) {

	time_t stime,ftime;
	time( &stime );

	std::cout << "Mc'C. Model capture tool for C++" << std::endl;
	std::cout << "Version 1.6" << std::endl << std::endl;

	//Parameters
	LOOSEExtractor *extractor;
	std::string source_directory,dest_directory,*conf_file = NULL;

	if(argc < 3) {
		std::cerr << "Error: Parameters are missing." << std::endl;
		std::cerr << "Mcc Param1:source_directory Param2:destination_directory [Param3:configuration_file]" << std::endl;
		return 1;
	}

	if(Path_FileType(argv[1]) != S_IFDIR) {
		std::cerr << "Error: Cannot access source directory: " << argv[1] << std::endl;
		return 1;
	}

	if(Path_FileType(argv[2]) != S_IFDIR) {
		std::cerr << "Error: Cannot access destination directory: " << argv[2] << std::endl;
		return 1;
	}

	source_directory	= argv[1];
	dest_directory		= argv[2];
	if(argc > 3) {
		conf_file = new std::string();
		*conf_file = argv[3];
	};

	//Start building the model
	extractor = new LOOSEExtractor(&source_directory,&dest_directory,conf_file);

	if(!extractor->extract()) {

		std::cerr << std::endl << "Meta-model building terminated with fatal errors." << std::endl;

	};

	delete extractor;

	time( &ftime );

	std::cout << "Total time : " << difftime(ftime,stime) / 60 << " min." << std::endl;

	return 0;
}
