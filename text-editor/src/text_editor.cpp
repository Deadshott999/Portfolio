#include "text_editor.h"

using namespace std;

const string& TextEditor::getText()
{
    return text;
}

void TextEditor::prepare(const shared_ptr<Command>& command)
{
    commandBuffer.push(command);
}

void TextEditor::commit()
{
    if (commandBuffer.empty()) {
        throw runtime_error("Nothing to commit");
    }

    while (!commandBuffer.empty()) {
        undoStack.push(commandBuffer.front());
        commandBuffer.front()->perform(text);
        commandBuffer.pop();
    }

    redoStack = std::stack<std::shared_ptr<Command>>();
}

void TextEditor::undo()
{
    if (undoStack.empty()) {
        throw runtime_error("Nothing to undo");
    }
    redoStack.push(undoStack.top());
    undoStack.top()->undo(text);
    undoStack.pop();
}

void TextEditor::redo()
{
    if (redoStack.empty()) {
        throw runtime_error("Nothing to redo");
    }

    undoStack.push(redoStack.top());
    redoStack.top()->perform(text);
    redoStack.pop();
}
