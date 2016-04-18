// FilesParser.h: interface for the FilesParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESPARSER_H__9A67AEFE_938E_4F19_ACD1_396F3EC9E8E2__INCLUDED_)
#define AFX_FILESPARSER_H__9A67AEFE_938E_4F19_ACD1_396F3EC9E8E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include "fast_include.h"

typedef struct _AbstractTree {
	std::string file;
	std::string directory;
	VTP_TreeP tree;
} AbstractTree;

typedef std::vector<AbstractTree> ATCollection;

class FilesParser
{
public:
	FilesParser();
	virtual ~FilesParser();
	ATCollection* doParse(std::string*,std::string*);

private:    

	static void parser_error_callback(int code, CIO_PositionP pos);
	static int dependency_callback(char *);
	static VTP_TreeP doParsing(CIO_InputP parsed_fileP);

	/** @link dependency */
	/*# _AbstractTree lnk_AbstractTree; */
};

#endif // !defined(AFX_FILESPARSER_H__9A67AEFE_938E_4F19_ACD1_396F3EC9E8E2__INCLUDED_)
