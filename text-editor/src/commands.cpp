#include "commands.h"

#include <algorithm>

InsertCommand::InsertCommand(int position, const std::string& text)
{
    this->position = position;
    this->text = text;
}

void InsertCommand::perform(std::string& str)
{
    str.insert(position, text);
}

void InsertCommand::undo(std::string& str)
{
    str.erase(position, text.length());
}

DeleteCommand::DeleteCommand(int position, int length)
{
    this->position = position;
    this->length = length;
}

void DeleteCommand::perform(std::string& str)
{
    deletedText = str.substr(position, length);
    str.erase(position, length);
}

void DeleteCommand::undo(std::string& str)
{
    str.insert(position, deletedText);
}

ReverseCommand::ReverseCommand(int position, int length)
{
    this->position = position;
    this->length = length;
}

void ReverseCommand::perform(std::string& str)
{
    reverse(str.begin() + position, str.begin() + position + length);
}

void ReverseCommand::undo(std::string& str)
{
    reverse(str.begin() + position, str.begin() + position + length);
}
