env = Environment(CPPPATH = ['core', 'cskel'])
SConscript('core/SConscript')
SConscript('cskel/SConstruct')
env.Program("todoc", "todoc.c", LIBS=["core","cskel"], LIBPATH=['./core', './cskel'])

