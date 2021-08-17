#pragma once

#include <iostream>
#include <ostream>
#include <utility>
#include <set>
#include "ApprovalTests.hpp"
#include "GameOfLife.h"

struct Point
{
    Point(int x, int y) : x_(x), y_(y)
    {
    }

    bool operator==(const Point& rhs) const
    {
        return x_ == rhs.x_ && y_ == rhs.y_;
    }

    bool operator!=(const Point& rhs) const
    {
        return !(rhs == *this);
    }

    bool operator<(const Point& rhs) const
    {
        if (x_ < rhs.x_)
            return true;
        if (rhs.x_ < x_)
            return false;
        return y_ < rhs.y_;
    }
    bool operator>(const Point& rhs) const
    {
        return rhs < *this;
    }
    bool operator<=(const Point& rhs) const
    {
        return !(rhs < *this);
    }
    bool operator>=(const Point& rhs) const
    {
        return !(*this < rhs);
    }
    int x_;
    int y_;
};

class GameOfLife
{
    std::vector<Point> aliveCells;
    std::string aliveCharacter = "X";
    std::string deadCharacter = ".";

public:
    explicit GameOfLife(int width,
                        int height,
                        const std::function<int(int, int)>& function)
    {
        std::vector<Point> points;
        for (int x = 0; x <= width; ++x)
        {
            for (int y = 0; y <= height; ++y)
            {
                const Point point = Point(x, y);
                points.push_back(point);
            }
        }
        *this = GameOfLife(function, points);
    }

    GameOfLife(const std::function<int(int, int)>& function, std::vector<Point>& points)
    {
        for (const auto& point : points)
        {
            if (function(point.x_, point.y_))
            {
                aliveCells.push_back(point);
            }
        }
    }

    explicit GameOfLife(std::vector<Point>& alivePoints) : aliveCells(alivePoints)
    {
    }

    explicit GameOfLife(const std::string& cells)
    {
        int x = 0;
        int y = 0;
        for (const auto& item : cells)
        {
            if (item == ' ')
            {
                continue;
            }
            if (item == '\n')
            {
                if (!(x == 0 && y == 0))
                {
                    x = 0;
                    y += 1;
                }
                continue;
            }
            if (item == 'X')
            {
                aliveCells.push_back(Point(x, y));
            }
            x += 1;
        }
    }

    bool isAlive(int x, int y) const
    {
        return (std::find(aliveCells.begin(), aliveCells.end(), Point(x, y)) !=
                aliveCells.end());
    }

    std::string printCell(int x, int y) const
    {
        return isAlive(x, y) ? aliveCharacter : deadCharacter;
    }

    std::string print(int width, int height) const
    {
        return ApprovalTests::Grid::print(
            width, height, [&](int x, int y, std::ostream& s) {
                s << printCell(x, y) << " ";
            });
    }

    std::vector<Point> getRelevantPoints() const
    {
        std::set<Point> points;
        for (const auto& item : aliveCells)
        {
            points.insert(Point(item.x_ - 1, item.y_ - 1));
            points.insert(Point(item.x_ - 1, item.y_ - 0));
            points.insert(Point(item.x_ - 1, item.y_ + 1));
            points.insert(Point(item.x_ - 0, item.y_ - 1));
            points.insert(Point(item.x_ - 0, item.y_ - 0));
            points.insert(Point(item.x_ - 0, item.y_ + 1));
            points.insert(Point(item.x_ + 1, item.y_ - 1));
            points.insert(Point(item.x_ + 1, item.y_ - 0));
            points.insert(Point(item.x_ + 1, item.y_ + 1));
        }
        return std::vector<Point>(points.begin(), points.end());
    }

    GameOfLife advance() const
    {
        std::function<int(int, int)> function2 = [this](int x, int y) {
            // clang-format off
            int count =
                this->isAlive(x - 1, y - 1) +
                this->isAlive(x - 1, y - 0) +
                this->isAlive(x - 1, y + 1) +

                this->isAlive(x - 0, y - 1) +
//                this->isAlive(x - 0, y - 0) +
                this->isAlive(x - 0, y + 1) +

                this->isAlive(x + 1, y - 1) +
                this->isAlive(x + 1, y - 0) +
                this->isAlive(x + 1, y + 1);
            // clang-format on
            return count == 3 || (count == 2 && this->isAlive(x, y));
        };
        auto points = getRelevantPoints();
        auto newGame = GameOfLife(function2, points);
        newGame.setAliveCell(aliveCharacter);
        newGame.setDeadCell(deadCharacter);
        return newGame;
    }

    // begin-snippet: storyboard_return_values
    std::string setAliveCell(std::string alive)
    {
        aliveCharacter = std::move(alive);
        return aliveCharacter;
    }
    // end-snippet

    std::string setDeadCell(std::string dead)
    {
        deadCharacter = std::move(dead);
        return deadCharacter;
    }
    std::string toString()
    {
        return print(5, 5);
    }
};
