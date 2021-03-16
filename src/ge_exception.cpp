#include "ge_exception.h"
#include <sstream>

eCException::eCException(GEInt line, const char* file) noexcept : line(line), file(file)
{

}

const char* eCException::what() const noexcept
{
	std::ostringstream oss;

	oss << GetType() << std::endl << GetOriginString();

	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* eCException::GetType() const noexcept
{
	return "Genome Exception";
}

GEInt eCException::GetLine() const noexcept
{
	return line;
}

const std::string& eCException::GetFile() const noexcept
{
	return file;
}

std::string eCException::GetOriginString() const noexcept
{
	std::ostringstream oss;

	oss << "[FILE] " << file << std::endl << "[LINE] " << line;

	return oss.str();
}