#pragma once

#include <iosfwd>
#include <sstream>
#include <functional>

namespace ApprovalTests
{
    class Storyboard
    {
    private:
        std::stringstream output_;
        int frameCount_ = 0;
        bool addNewLineBeforeNextFrame_ = false;

    public:
        Storyboard& addDescription(const std::string& description);

        Storyboard& addDescriptionWithData(const std::string& description,
                                           const std::string& data);

        Storyboard& addFrame(const std::string& frame);

        Storyboard& addFrame(const std::string& title, const std::string& frame);

        Storyboard& addFrames(int numberOfFrames,
                              const std::function<std::string(int)>& function);

        friend std::ostream& operator<<(std::ostream& os, const Storyboard& board);
    };
}
