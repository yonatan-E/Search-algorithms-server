#include "InputToGraphParser.hpp"
#include "StatusException.hpp"

#include <cstdint>
#include <algorithm>
#include <utility>

namespace parser
{

    searcher::Graph InputToGraphParser::parse(const std::string &input) const
    {
        // getting the first line
        std::string firstLine(&input[0], &input[input.find("\r\n", 0)]);
        firstLine.erase(std::remove(firstLine.begin(), firstLine.end(), ' '), firstLine.end());
        // getting the number of the rows and the columns of the matrix
        uint32_t numRows;
        uint32_t numColumns;
        try
        {
            numRows = std::stoi(std::string(&firstLine[0], &firstLine[firstLine.find(',', 0)]));
            numColumns = std::stoi(std::string(&firstLine[firstLine.find(',', 0) + 1], &firstLine[firstLine.size()]));
        }
        catch (...)
        {
            // throwing a file format exception in case that the stoi function hasn't succeeded
            throw status_exception::StatusException("Invalid graph format", 4);
        }

        // throwing an exception in a case that the matrix height or width is 0
        if (numRows == 0 || numColumns == 0)
        {
            throw status_exception::StatusException("Invalid graph format", 4);
        }

        // creating a new matrix with sizes numRows * numColumns
        matrix::Matrix matrix(numRows, numColumns);
        // reading from the file and filling the matrix
        size_t it = input.find("\r\n", 0) + 2;
        for (uint32_t i = 0; i < numRows; ++i)
        {
            std::string line(&input[it], &input[input.find("\r\n", it)]);
            // removing the spaces from the line string
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            // j will run on the string line, colIndex will run on the matrix columns
            uint32_t j = 0, colIndex = 0;
            // iterating over the line string and initializing the matrix
            while (j < line.size())
            {
                size_t k = line.find(',', j);
                // if k == npos, it means that there aren't more ',' in the line, so the current number
                // is the last number in the line
                if (k == std::string::npos)
                {
                    k = line.size();
                }
                // getting the specified value
                double val;
                if (line.substr(j, k - j) == "b")
                {
                    val = 0;
                }
                else
                {
                    try
                    {
                        val = std::stoi(line.substr(j, k - j));
                    }
                    catch (...)
                    {
                        // throwing a file format exception in case that the stoi function hasn't succeeded
                        throw status_exception::StatusException("Invalid graph format", 4);
                    }
                    // throwing an exception in case that the specified value in the matrix is smaller than 1
                    if (val < 1)
                    {
                        throw status_exception::StatusException("Invalid graph format", 4);
                    }
                }
                // finally setting the value in the matrix
                try
                {
                    matrix.setAt(i, colIndex, val);
                }
                catch (...)
                {
                    // throwing an exception in case that the value set in the matrix is in an invalid place
                    throw status_exception::StatusException("Invalid graph format", 4);
                }

                // promoting the iterators
                j = k + 1;
                colIndex++;
            }

            it = input.find("\r\n", it) + 2;
        }

        // getting the current line
        std::string currentLine(&input[it], &input[input.find("\r\n", it)]);
        currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
        // getting the start position
        std::pair<uint32_t, uint32_t> startPos;
        try
        {
            startPos.first = std::stoi(std::string(&currentLine[0], &currentLine[currentLine.find(',', 0)]));
            startPos.second = std::stoi(std::string(&currentLine[currentLine.find(',', 0) + 1], &currentLine[currentLine.size()]));
        }
        catch (...)
        {
            // throwing a file format exception in case that the stoi function hasn't succeeded
            throw status_exception::StatusException("Invalid graph format", 4);
        }
        it = input.find("\r\n", it) + 2;

        // getting the current line
        currentLine = std::string(&input[it], &input[input.size()]);
        currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
        // getting the start position
        std::pair<uint32_t, uint32_t> endPos;
        try
        {
            endPos.first = std::stoi(std::string(&currentLine[0], &currentLine[currentLine.find(',', 0)]));
            endPos.second = std::stoi(std::string(&currentLine[currentLine.find(',', 0) + 1], &currentLine[currentLine.size()]));
        }
        catch (...)
        {
            // throwing a file format exception in case that the stoi function hasn't succeeded
            throw status_exception::StatusException("Invalid graph format", 4);
        }

        return searcher::Graph(matrix, startPos, endPos);
    }
}