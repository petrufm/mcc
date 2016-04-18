// FilesParser.cpp: implementation of the FilesParser class.
//
//////////////////////////////////////////////////////////////////////

#include "FilesParser.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FilesParser::FilesParser()	{}

FilesParser::~FilesParser()	{}

ATCollection* FilesParser::doParse(std::string* directory, std::string* config) {

	char *file_name;
	int error = 0;
	TListS file_list,ordered_file_list;
	C_ConfP configuration = NULL;
	CIO_InputP conf_file_pointer, parsed_fileP;
	VTP_TreeP file_tree;
	C_DependencyGraphP graph;
	ATCollection *collection = new ATCollection();
	AbstractTree *tree;
	int tfiles = 0, ifiles = 0;

	Exception_Begin();
	if(Exception_Catch()) {
		std::cerr << "Exception raised:" << Exception_GetString();
		error = 1;
	} else {

		//Initialisation of the library
		VTP_Init();
		C_Init();

		*directory = Path_Fullname((char*)directory->c_str());
		C_ParserSetApplicationDirectory((char*)directory->c_str());

		//Getting the files
		TList_Init(&file_list);
		Audit_FilterFiles(&file_list,(char *)directory->c_str(),"*.{c,h,C,H,cc,hh,CC,HH,cxx,hxx,CXX,HXX,cpp,hpp,CPP,HPP}");

		std::cout << std::endl << "Finding dependencies" << std::endl;

		//Getting the dependencies
		graph = C_Get_DependencyGraph(&file_list,dependency_callback);
		TList_Init(&ordered_file_list);
		C_DependencyOrder(graph,&ordered_file_list);

		std::cout << std::endl << "Parsing the files" << std::endl;
		
		//Configuring the parser grammar
		if(config == NULL) {
			C_SetCurrentConf(C_GetPredefConf(C_CONF_PREDEF_Cxx));
		} else {
			conf_file_pointer = TextFileInput_Open((char *)config->c_str());
			configuration = C_CreateConf();
			C_ConfRead(configuration, conf_file_pointer);
			C_SetCurrentConf(configuration);
			CIO_InputDestroy(conf_file_pointer);
		}

		//Preapare the parser
		C_ParserSetTypeTableUseLevel(1);
		Cxx_SetErrorHandler(parser_error_callback);
		TLIST_MAP(&ordered_file_list, char*, file_name);
			tfiles++;
			std::cout << "Parsing " << file_name << std::endl;
			parsed_fileP = TextFileInput_Open(Path_Append((char*)directory->c_str(),file_name));
			C_ParserSetModuleName(file_name);
			parser_buildCoord = 1;
			file_tree = doParsing(parsed_fileP);
			CIO_InputDestroy(parsed_fileP);
			if(file_tree == NULL) {
				std::cout << "Ignoring " << file_name << std::endl;
				ifiles++;
			} else {
				tree = new AbstractTree();
				tree->file = file_name;
				tree->tree = file_tree;
				tree->directory = directory->c_str();
				collection->push_back(*tree);
			}
		TLIST_END_MAP();
	}
	Exception_End();

	std::cout << "All files: " << tfiles << std::endl;
	std::cout << "Ignored files: " << ifiles << std::endl;
	//Free the memory
	C_Free_DependencyGraph(graph);
	if(!C_ConfIsPredef(configuration)) {
		C_ConfDestroy(configuration);
	}
	if(error) {
		return NULL;
	} else {
		return collection;
	}
}

VTP_TreeP FilesParser::doParsing(CIO_InputP parsed_fileP) {
	//TODO:Can this be made compiler independent?
	VTP_TreeP tree;
	//__try {
		tree = Cxx_Parse(parsed_fileP,NULL);
		return tree;
	//} __except(EXCEPTION_EXECUTE_HANDLER) {
	//	return NULL;
	//}
}

void FilesParser::parser_error_callback(int code, CIO_PositionP pos) {
	std::cerr << '\t' << "Error found at line " << pos->line << " column " << pos->col << std::endl;
}

int FilesParser::dependency_callback(char * file) {
	std::cout << "Dependency processing: " << file << std::endl;
	return 1;
}
