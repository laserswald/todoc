env = Environment(CPPPATH = ['core', 'cskel'], CFLAGS="-g -Wall")
SConscript('core/SConscript', 'env')
SConscript('cskel/SConstruct', 'env')
env.Program("todoc", "todoc.c", LIBS=["core","cskel"], LIBPATH=['./core', './cskel'])

