#Scons buildfile for Todoc.
# Written by Ben Davenport-Ray.

# Set up the environment that we are using.
dbgenv = Environment(CPPPATH="include", CFLAGS=["-g"])

todolib = dbgenv.Library("todotxt", ["src/task.c", 'src/tasklist.c'])
mainprogram = dbgenv.Program("todoc", 'src/todo.c', LIBS=[todolib]) 
testprogram = dbgenv.Program("todoc_test", ["tests/seatest.c", "tests/todo_test.c", "tests/task_test.c", "tests/tasklist_test.c"], LIBS=[todolib])


