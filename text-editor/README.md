# Text Editor

Early text editors were nothing like the sophisticated graphical applications that we see today. Programs such as [ed](https://en.wikipedia.org/wiki/Ed_(text_editor)) and [edlin](https://en.wikipedia.org/wiki/Edlin) provided only a few basic commands to insert and delete text, or search and replace it.

In this assigment, you are to implement a text editor class that provides features similar to these early tools. It should offer the following commands:

* insert text at a given position
* delete text in a given range
* reverse text in a given range
* undo the last command
* redo any commands that were "undone"

In addition, the text editor should offer a command buffer that stores these commands and does not modify the text until the buffer is committed.

A command-line interface to the class is provided for you, where i=insert, d=delete, v=reverse, c=commit, u=undo, r=redo. Here is an example session:

    > i 0 foo
    > i 3 bar
    > v 0 3
    > d 3 3
    > c
    oof
    > u
    oofbar
    > r
    oof
    > u
    oofbar
    > u
    foobar

Note that the command line interface is very primitive and does not support whitespace.

To complete the assignment, start with the provided `TextEditor` class and implement its public methods. You should also implement a class hierarchy of commands starting with the provided `Command` class as the base class. For example, you should implement the "insert text" command as:

    class InsertCommand : public Command {
    public:
        InsertCommand(int position, const std::string& text);
        void perform(std::string& str);
        void undo(std::string& str);
    };

You may add any private member variables and helper functions that you like.

In this assignment, you may use stack or queue ADTs but no arrays, vectors, or linked lists. You may write your own stack and queue ADTs or you can use the ones provided by the STL.

Be sure to verify your code by running the provided unit tests.
