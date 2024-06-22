#pragma once

#include <string>

// A text editor command, such as inserting or deleting text.
class Command {
public:
    // Applies the command to the given text.
    virtual void perform(std::string& str) = 0;
    // Applies the opposite of the command to the given text.
    virtual void undo(std::string& str) = 0;
    virtual ~Command() = default;
};

class InsertCommand : public Command {
public:
    InsertCommand(int position, const std::string& text);
    void perform(std::string& str);
    void undo(std::string& str);
private:
    int position;
    std::string text;
};

class DeleteCommand : public Command {
public:
    DeleteCommand(int position, int length);
    void perform(std::string& str);
    void undo(std::string& str);
private:
    int position;
    int length;
    std::string deletedText;
};

class ReverseCommand : public Command {
public:
    ReverseCommand(int position, int length);
    void perform(std::string& str);
    void undo(std::string& str);
private:
    int position;
    int length;
};
