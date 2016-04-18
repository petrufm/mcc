#include "LOOSEExtractor.h"
#include <time.h>
#include <fstream>
#include <iostream>

LOOSEExtractor::LOOSEExtractor(std::string* source_dir, std::string* dest_dir, std::string* conf_file) {

	this->source_dir = new std::string(*source_dir);
	this->dest_dir = new std::string(*dest_dir);
	if(conf_file != NULL) {
		this->conf_file = new std::string(*conf_file);
	} else {
		this->conf_file = NULL;
	}

	packages = NULL;
	namespaces = NULL;
	types = NULL;
	chains = NULL;
	t2t = NULL;
	funcs = NULL;
	body = NULL;
	vars = NULL;
	inh = NULL;
	accesses = NULL;
	calls = NULL;
}

LOOSEExtractor::~LOOSEExtractor() {
	delete source_dir;
	delete dest_dir;
	if(conf_file != NULL) {
		delete conf_file;
	}
	if(packages != NULL) {
		delete packages;
	}
	if(namespaces != NULL) {
		delete namespaces;
	}
	if(types != NULL) {
		delete types;
	}
	if(t2t != NULL) {
		delete t2t;
	}
	if(chains != NULL) {
		delete chains;
	}
	if(body != NULL) {
		delete body;
	}
	if(funcs != NULL) {
		delete funcs;
	}
	if(vars != NULL) {
		delete vars;
	}
	if(inh != NULL) {
		delete inh;
	}
	if(accesses != NULL) {
		delete accesses;
	}
	if(calls != NULL) {
		delete calls;
	}

}

void LOOSEExtractor::createTables() {

	if(packages != NULL) delete packages;
	if(namespaces != NULL) delete namespaces;
	if(types != NULL) delete types;
	if(t2t != NULL) delete t2t;
	if(chains != NULL) delete chains;
	if(body != NULL) delete body;
	if(funcs != NULL) delete funcs;
	if(vars != NULL) delete vars;
	if(inh != NULL) delete inh;
	if(accesses != NULL) delete accesses;
	if(calls != NULL) delete calls;
	packages = new PackagesTable("packages");
	namespaces = new NamespaceTable("namespaces");
	body = new BodyTable("body",packages);
	types = new TypesTable("types",packages,namespaces,body);
	t2t = new TemplateParTypesRelation("tp2t",types);
	chains = new TemplateInstanceChainsTable("chains",types,t2t);
	funcs = new FuncsTable("functions",namespaces,types,body);
	vars = new VariablesTable("variables",packages,namespaces,types,body);
	inh = new InheritanceTable("inheritance",types);
	accesses = new AccessTable("access",body,vars,funcs,types,inh,namespaces,t2t);
	calls = new CallTable("call",body,funcs,vars,types,inh,namespaces,t2t);
	packages->init();
	namespaces->init();
	types->init();
	t2t->init();
	chains->init();
	body->init();
	funcs->init();
	vars->init();
	inh->init();
	accesses->init();
	calls->init();
}

bool LOOSEExtractor::extract() {

	FilesParser *fparser = new FilesParser();
	ATCollection *aTrees;

	aTrees = fparser->doParse(source_dir,conf_file);

	if(aTrees == NULL) {
		return false;
	}

	delete fparser;

	time_t stime,ftime;

	createTables();

	time( &stime );
	std::cout << "Extracting packages..." << std::endl;
	packages->extract(*aTrees);
	print(packages,"\\packages.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting namespaces..." << std::endl;
	namespaces->extract(*aTrees);
	print(namespaces,"\\namespaces.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting body..." << std::endl;
	body->extract(*aTrees);
	print(body,"\\body.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting types..." << std::endl;
	types->extract(*aTrees);
	print(types,"\\types.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting t2t relations..." << std::endl;
	t2t->extract(*aTrees);
	print(t2t,"\\tp2t.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting chains..." << std::endl;
	chains->extract(*aTrees);
	print(chains,"\\chains.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting functions..." << std::endl;
	funcs->extract(*aTrees);
	print(funcs,"\\funcs.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting variables..." << std::endl;
	vars->extract(*aTrees);
	print(vars,"\\vars.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting inheritance..." << std::endl;
	inh->extract(*aTrees);
	print(inh,"\\inh.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;

	time( &stime );
	std::cout << "Extracting accesses..." << std::endl;
	accesses->extract(*aTrees);
	print(accesses,"\\access.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;
	delete accesses;
	accesses = NULL;

	time( &stime );
	std::cout << "Extracting calls..." << std::endl;
	calls->extract(*aTrees);
	print(calls,"\\call.dat");
	time( &ftime );
	std::cout << "Done in " << difftime(ftime,stime) / 60 << " min." << std::endl;
	
	return true;
}

void LOOSEExtractor::print(Table *table,const char *filename) {

	std::string path(*dest_dir);
	path.append(filename);

	std::ofstream stream(path.c_str(),std::ios::out | std::ios::trunc);
	stream.setf(std::ios::left);
	table->print(stream);
	stream.close();

}
