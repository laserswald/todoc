env = Environment(CPPPATH = ['core', 'cskel'])
SConscript('core/SConscript', {'env':env})
SConscript('cskel/SConstruct', {'env':env})
env.Program("todoc", "todoc.c", LIBS=["core","cskel"], LIBPATH=['./core', './cskel'])

