#include "utils.hpp"

bool isFound(size_t position)
{
    return position != std::string::npos;
}

//finds the first elem of a string
size_t findFirstElem(const std::string& str, char ch, size_t start)
{
    for (size_t i = start; i < str.size(); i++)
    {
        if (str[i] == ch)
        {
            return i;
        }
    }
    return std::string::npos;
}

void parseDeclaration(const std::string& str, Tag& tag)
{
    std::vector<std::string> parameters  = splitQuote(str, ' ');
    std::string nameTag = parameters[0];

    for (size_t i = 1; i < parameters.size(); i++)
    {
        const std::string& params = parameters[i];
        size_t equal_position = params.find('=');
        std::string parameter_name = params.substr(0, equal_position);
        std::string parameter_value = params.substr(equal_position+1);
        tag._params[parameter_name] = parameter_value;
    }

    if (nameTag.front() == SLASH)
    {
        tag._type = CLOSE;
        nameTag  = nameTag.substr(1);
    }
    else if (str.back() == SLASH)
    {
        tag._type = AUTO_CLOSED;
    }
    else if (nameTag.compare(HEADER) == 0)
    {
        tag._type = SPECIAL;
    }
    else if (nameTag.compare("!--") == 0)
    {
        tag._type = COMMENTED;
    }
    else
    {
        tag._type = OPEN;
    }
    tag._name = nameTag;
}

Tag getNextTag(std::string& str, size_t start)
{
    Tag tag;

    size_t position1 = findFirstElem(str, START_TAG, start);
    size_t position2 = findFirstElem(str, END_TAG  , position1);
    if (isFound(position1) && isFound(position2))
    {
        size_t length = position2-position1-1;
        std::string tag_declaration = str.substr(position1+1, length);

        parseDeclaration(tag_declaration, tag);

        if (tag._type == CLOSE)
        {
            tag._data = str.substr(start, position1-start);
        }
        else if (tag._type == COMMENTED)
        {
            position2 = str.find("-->") + 2;
        }

        tag._isValid = true;
        tag._position = position2;
    }
    else
    {
        tag._isValid = false;
    }
    return tag;
}

std::vector<std::string> split(const std::string& str, std::string separation)
{
    std::vector<std::string> result;

    std::string strcopy = str;

    size_t position_of_separation = strcopy.find(separation);
    while (position_of_separation != std::string::npos)
    {
        std::string cut = strcopy.substr(0, position_of_separation);
        if (!cut.empty())
        {
            result.push_back(cut);
        }
        strcopy = strcopy.substr(position_of_separation+separation.size());
        position_of_separation = strcopy.find(separation);
    }

    if (!strcopy.empty())
    {
        result.push_back(strcopy);
    }
    
    return result;
}

std::vector<std::string> splitQuote(const std::string& str, char separation)
{
    std::vector<std::string> result;
    std::string strcopy = str + ' ';

    bool isQuoted = false;
    size_t lastCut = -1;
    for (size_t i = 0; i < strcopy.size(); i++)
    {
        if (strcopy[i] == separation && !isQuoted)
        {
            if (i - lastCut > 1)
            {
                result.push_back(strcopy.substr(lastCut+1, i-lastCut-1));
            }
            lastCut = i;
        }
        else if (strcopy[i] == '"')
        {
            isQuoted = !isQuoted;
        }
    }

    return result;
}
