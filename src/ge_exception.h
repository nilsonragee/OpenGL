#pragma once
#include "ge_types.h"
#include <exception>
#include <string>

class eCException : public std::exception
{
public:
	eCException(GEInt line, const char* file) noexcept;
	const char* what() const noexcept override;

	virtual const char* GetType() const noexcept;
	GEInt GetLine() const noexcept;

	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	GEInt line;
	std::string file;

protected:
	mutable std::string whatBuffer;
};