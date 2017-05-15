#pragma once
#include "Stdafx.h"


namespace RigelCore
{
	struct cFileData_t
	{
		unsigned attrib;
		time_t time_create;
		time_t time_access;
		time_t time_write;
		_fsize_t size;
		char name[_MAX_FNAME];
	};

	void _DFSfolder(std::string folderPath);
}
