#Scons buildfile for Todoc.

env = Environment(CPPPATH="include")

todolib = env.Library("todotxt", ["src/task.c", 'src/tasklist.c'])
program = env.Program("todoc", 'src/todo.c', LIBS=[todolib]) 
