#!python
import os
opts = Variables([], ARGUMENTS)        

# Gets the standard flags, CC, CCX, ...
env = DefaultEnvironment()

# Define scons build options.
opts.Add(EnumVariable('build', help="Build project", default='debug', allowed_values=['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', help="Build for platform", default='', allowed_values=['', 'windows', 'linux', 'mac']))
opts.Add(BoolVariable('use_llvm', help=" Use LLVM/ Clang compiler", default='no'))
opts.Add(PathVariable('target_path', help="The path where the binary is stored.", default='bin/'))
opts.Add(PathVariable('target_name', help="The library name", default='dsaa', validator=PathVariable.PathAccept))

# Local dependencies path.
includes_path = ['./', 'algorithms/']

# Only allow 64 bits at the moment.
bits = 64

# Update environment with opts variables.
opts.Update(env)

if env['platform'] == '':
    print("No valid target platform selected.")
    quit();

if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

if env['platform'] == 'mac':
    env['target_path'] += 'mac/'
    env.Append(CCFLAGS=['-arch', 'x86_64'])
    env.Append(CXXFLAGS=['-std=c++17'])
    env.Append(LINKFLAGS=['-arch', 'x86_64'])
    if env['build'] in ('debug', 'd'):
        env.Append(CCFLAGS=['-g', '-O2'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])
elif env['platform'] == 'linux':
    env['target_path'] += 'linux/'
    env.Append(CCFLAGS=['-fPIC'])
    env.Append(CXXFLAGS=['-std=c++17'])
    if env['build'] in ('debug', 'd'):
        env.Append(CCFLAGS=['-g3', '-Og'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])
elif env['platform'] == "windows":
    env['target_path'] += 'windows/'
    env.Append(ENV=os.environ)
    env.Append(CCFLAGS=['-W3', '-GR'])
    if env['build'] in ('debug', 'd'):
        env.Append(CPPDEFINES=['_DEBUG'])
        env.Append(CCFLAGS=['-EHsc', '-MDd', '-ZI'])
        env.Append(LINKFLAGS=['-DEBUG'])
    else:
        env.Append(CPPDEFINES=['NDEBUG'])
        env.Append(CCFLAGS=['-O2', '-EHsc', '-MD'])

# Make sure library is properly includes.
env.Append(CPPPATH=includes_path)

sources = []
for item in includes_path:
   sources += Glob(item + '*.cpp')
library = env.Program(target=env['target_path'] + env['target_name'], source=sources)
Default(library)
# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
