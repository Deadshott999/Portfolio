#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include "text_editor.h"

using namespace std;

TEST_CASE("Insert")
{
    TextEditor editor;
    editor.prepare(make_shared<InsertCommand>(0, "foobar"));
    editor.prepare(make_shared<InsertCommand>(6, "baz"));
    editor.prepare(make_shared<InsertCommand>(3, "buzz"));
    editor.commit();
    REQUIRE(editor.getText() == "foobuzzbarbaz");
}

TEST_CASE("Delete")
{
    TextEditor editor;
    editor.prepare(make_shared<InsertCommand>(0, "foobarbaz"));
    editor.prepare(make_shared<DeleteCommand>(3, 3));
    editor.prepare(make_shared<DeleteCommand>(0, 3));
    editor.commit();
    REQUIRE(editor.getText() == "baz");
}

TEST_CASE("Reverse")
{
    TextEditor editor;
    editor.prepare(make_shared<InsertCommand>(0, "foobarbaz"));
    editor.prepare(make_shared<ReverseCommand>(3, 3));
    editor.commit();
    REQUIRE(editor.getText() == "foorabbaz");
}

TEST_CASE("Undo and redo")
{
    TextEditor editor;
    editor.prepare(make_shared<InsertCommand>(0, "foobar"));
    editor.commit();
    REQUIRE(editor.getText() == "foobar");
    editor.undo();
    REQUIRE(editor.getText() == "");
    editor.redo();
    REQUIRE(editor.getText() == "foobar");
    editor.prepare(make_shared<InsertCommand>(3, "buzz"));
    editor.prepare(make_shared<ReverseCommand>(0, 3));
    editor.prepare(make_shared<InsertCommand>(10, "boz"));
    editor.prepare(make_shared<DeleteCommand>(3, 4));
    editor.commit();
    REQUIRE(editor.getText() == "oofbarboz");
    editor.undo();
    REQUIRE(editor.getText() == "oofbuzzbarboz");
    editor.undo();
    REQUIRE(editor.getText() == "oofbuzzbar");
    editor.redo();
    REQUIRE(editor.getText() == "oofbuzzbarboz");
    editor.undo();
    REQUIRE(editor.getText() == "oofbuzzbar");
    editor.undo();
    REQUIRE(editor.getText() == "foobuzzbar");
    editor.undo();
    REQUIRE(editor.getText() == "foobar");
    editor.redo();
    editor.redo();
    editor.redo();
    editor.redo();
    REQUIRE(editor.getText() == "oofbarboz");
}

TEST_CASE("Undo and redo should throw an exception if nothing to undo or redo")
{
    TextEditor editor;
    REQUIRE_THROWS(editor.undo());
    REQUIRE_THROWS(editor.redo());
    editor.prepare(make_shared<InsertCommand>(0, "foobar"));
    editor.commit();
    REQUIRE_NOTHROW(editor.undo());
    REQUIRE_THROWS(editor.undo());
    REQUIRE_NOTHROW(editor.redo());
    REQUIRE_THROWS(editor.redo());
}

TEST_CASE("Committing a command should clear the redo state")
{
    TextEditor editor;
    editor.prepare(make_shared<InsertCommand>(0, "foobar"));
    editor.prepare(make_shared<InsertCommand>(6, "baz"));
    editor.prepare(make_shared<InsertCommand>(3, "buzz"));
    editor.commit();
    REQUIRE(editor.getText() == "foobuzzbarbaz");
    editor.undo();
    editor.undo();
    editor.prepare(make_shared<InsertCommand>(0, "boz"));
    editor.commit();
    REQUIRE_THROWS(editor.redo());
}
