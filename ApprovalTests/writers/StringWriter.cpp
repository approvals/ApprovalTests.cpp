#include "ApprovalTests/writers/StringWriter.h"

#include <utility>
#include <fstream>

namespace ApprovalTests
{
    StringWriter::StringWriter(std::string contents, std::string fileExtensionWithDot)
        : s(std::move(contents)), ext(std::move(fileExtensionWithDot))
    {
    }

    std::string StringWriter::getFileExtensionWithDot() const
    {
        return ext;
    }

    void StringWriter::write(std::string path) const
    {
        std::ofstream out(path.c_str(), std::ofstream::out);
        if (!out)
        {
            throw std::runtime_error("Unable to write file: " + path);
        }
        this->Write(out);
        out.close();
    }

    void StringWriter::Write(std::ostream& out) const
    {
        out << s << "\n";
    }

    void StringWriter::cleanUpReceived(std::string receivedPath) const
    {
        remove(receivedPath.c_str());
    }
}
