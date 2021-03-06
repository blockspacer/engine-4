#pragma once

#include <ifsys/imodule.h>

class imapeditor : public imodule {
public:
	virtual const char * name() const override = 0;
	virtual void init() = 0;
	virtual bool shutdown() override = 0;
	virtual bool is_shutdown() = 0;

	virtual void add_object(const char* szFilename) = 0;
};
