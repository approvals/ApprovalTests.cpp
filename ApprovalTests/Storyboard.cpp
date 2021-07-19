
#include "Storyboard.h"
namespace ApprovalTests
{
    StoryBoard& StoryBoard::addDescription(const std::string& description)
    {
        output_ << description << "\n";
        addNewLineBeforeNextFrame_ = true;
        return *this;
    }
    
    StoryBoard& StoryBoard::addDescriptionWithData(const std::string& description,
                                                   const std::string& data)
    {
        output_ << description << ": " << data << "\n";
        addNewLineBeforeNextFrame_ = true;
        return *this;
    }

    StoryBoard& StoryBoard::addFrame(const std::string& frame)
    {
        if (frameCount_ == 0)
        {
            return addFrame("Initial Frame", frame);
        }
        else
        {
            return addFrame("Frame #" + std::to_string(frameCount_), frame);
        }
    }

    StoryBoard& StoryBoard::addFrame(const std::string& title, const std::string& frame)
    {
        if (addNewLineBeforeNextFrame_)
        {
            output_ << '\n';
            addNewLineBeforeNextFrame_ = false;
        }
        output_ << title << ":\n";
        output_ << frame << "\n\n";
        frameCount_ += 1;
        return *this;
    }

    StoryBoard& StoryBoard::addFrames(int numberOfFrames,
                                      const std::function<std::string(int)>& function)
    {
        for (int frame = 1; frame <= numberOfFrames; ++frame)
        {
            addFrame(function(frame));
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const StoryBoard& board)
    {
        os << board.output_.str();
        return os;
    }
}