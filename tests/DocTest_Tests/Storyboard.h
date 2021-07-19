#include <vector>
#include <ostream>
#include <sstream>

class StoryBoard
{
private:
    std::stringstream output_;
    int frameCount_ = 0;
    bool addNewLineBeforeNextFrame_ = false;

public:
    StoryBoard& addDescription(const std::string& description)
    {
        output_ << description << "\n";
        addNewLineBeforeNextFrame_ = true;
        return *this;
    }

    StoryBoard& addDescriptionWithData(const std::string& description,
                                       const std::string& data)
    {
        output_ << description << ": " << data << "\n";
        addNewLineBeforeNextFrame_ = true;
        return *this;
    }

    StoryBoard& addFrame(const std::string& frame)
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

    StoryBoard& addFrame(const std::string& title, const std::string& frame)
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

    StoryBoard& addFrames(int numberOfFrames,
                          const std::function<std::string(int)>& function)
    {
        for (int frame = 1; frame <= numberOfFrames; ++frame)
        {
            addFrame(function(frame));
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const StoryBoard& board)
    {
        os << board.output_.str();
        return os;
    }
};
