import os
import platform
import struct
import subprocess

# Initialized options for build engine.
opts = Variables([], ARGUMENTS)
# Gets the standard flags, CC, CCX, ...
env = Environment(tools=['cc', 'cxx', 'clang', 'clangxx',
                  'gcc', 'g++', 'link', 'ar', 'gnulink', 'as'], ENV=os.environ)
# Define scons build options.
opts.Add(BoolVariable(key='use_llvm',
         help=" Use LLVM/ Clang compiler.", default='no'))

opts.Add(EnumVariable(key='platform', help="Build for platform",
         default='', allowed_values=['', 'windows', 'linux', 'darwin'], map={}, ignorecase=0))

opts.Add(EnumVariable(key='bits', help="Architecture",
         default='', allowed_values=['', '64', '32'], map={}, ignorecase=0))

opts.Add(EnumVariable(key='build', help="Build project", default='debug',
         allowed_values=['d', 'debug', 'r', 'release'], map={}, ignorecase=0))

opts.Add(PathVariable(key='target_path',
         help="The path where the library is stored.", default='bin', validator=PathVariable.PathAccept))

opts.Add(PathVariable(key='target_name', help="The library name",
         default='dsaa', validator=PathVariable.PathAccept))

opts.Add(EnumVariable(key='target', help="Project is inteded to build: ", default='run_test',
         allowed_values=['run_test', 'static_library', 'shared_library'], map={}, ignorecase=0))

# Update environment with opts variables.
opts.Update(env)

# Local includes paths.
test_arrays_path = 'test/data_structures/arrays/'
test_lists_path = 'test/data_structures/lists/'
test_data_structures_paths = [test_arrays_path, test_lists_path]

test_cases_paths = ['modules/', 'test/', 'test/algorithms/']
test_cases_paths += test_data_structures_paths

root_path = './'

data_structures_paths = 'data_structures/'

library_paths = [root_path, data_structures_paths]

if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'
else:
    env['CC'] = 'gcc'
    env['CXX'] = 'g++'

if env['platform'] == '':
    host_platform = platform.system().lower()
    if host_platform == '':
        print("can't auto detech host platform. quit!")
        quit()
    else:
        env['platform'] = host_platform

if env['bits'] == '':
    env['bits'] = struct.calcsize("P") * 8
if env['build'] == 'd':
    env['build'] = 'debug'
if env['build'] == 'r':
    env['build'] = 'release'

if env['build'] in ('d', 'debug'):
    # Debugging Your Program.
    env.Append(CXXFLAGS=['-g3'])
    env.Append(CXXFLAGS=['-Og'])
    # Request or Suppress Warnings.
    env.Append(CXXFLAGS=['-Wall'])
    env.Append(CXXFLAGS=['-Wabi=11'])
    env.Append(CXXFLAGS=['-Wextra'])
    # Control Diagnostic Messages Formatting.
    env.Append(CXXFLAGS=['-fdiagnostics-show-location=once'])
    env.Append(CXXFLAGS=['-fdiagnostics-color=always'])
    env.Append(CXXFLAGS=['-fdiagnostics-urls=always'])
    env.Append(CXXFLAGS=['-fdiagnostics-show-template-tree'])
    env.Append(CXXFLAGS=['-fdiagnostics-path-format=inline-events'])
    env.Append(CXXFLAGS=['-fdiagnostics-show-path-depths'])
    # Controlling C++ Dialect.
    env.Append(CXXFLAGS=['-Wcomma-subscript'])
    env.Append(CXXFLAGS=['-Wctor-dtor-privacy'])
    # env.Append(CXXFLAGS=['-Wenum-conversion'])
    # env.Append(CXXFLAGS=['-Winvalid-imported-macros'])
    env.Append(CXXFLAGS=['-Wnoexcept'])
    env.Append(CXXFLAGS=['-Wreorder'])
    env.Append(CXXFLAGS=['-Wredundant-tags'])
    env.Append(CXXFLAGS=['-Weffc++'])
    env.Append(CXXFLAGS=['-Wstrict-null-sentinel'])
    env.Append(CXXFLAGS=['-Wold-style-cast'])
    env.Append(CXXFLAGS=['-Woverloaded-virtual'])
    env.Append(CXXFLAGS=['-Wsign-promo'])
    # env.Append(CXXFLAGS=['-Wno-mismatched-new-delete'])
    # env.Append(CXXFLAGS=['-Wmismatched-dealloc'])
    env.Append(CXXFLAGS=['-Wmismatched-tags'])
    env.Append(CXXFLAGS=['-Wzero-as-null-pointer-constant'])
    env.Append(CXXFLAGS=['-Wextra-semi'])
    env.Append(CXXFLAGS=['-Wsuggest-final-types'])
    env.Append(CXXFLAGS=['-Wsuggest-final-methods'])
    env.Append(CXXFLAGS=['-Wsuggest-override'])
    env.Append(CXXFLAGS=['-Wuseless-cast'])
else:
    env.Append(CXXFLAGS=['-O3'])

# Controlling C Dialect.
env.Append(CXXFLAGS=['-std=c++20'])
env.Append(CPPPATH=library_paths)

env['target_name'] += '.' + env['platform'] + \
    '.' + env['build'] + '.' + str(env['bits'])

result_name = env['target_path'] + '/' + \
    env['platform'] + '/' + env['target_name']
src_files = []

for item in library_paths:
    src_files += Glob(item + '*.cpp')


def run_program(target, source, env):
    subprocess.call("./" + result_name +
                    env['PROGSUFFIX'] + ' --reporter compact --success')
    return None


if env['target'] == 'run_test':
    print("Build and run test cases for :", env['target_name'])
    env.Append(CPPPATH=test_cases_paths)
    for item in test_cases_paths:
        src_files += Glob(item + '*.cpp')

    program = env.Program(target=result_name, source=src_files)
    # # Run test after build.
    # subprocess.call(
    #     result_name + env['PROGSUFFIX'] + ' --reporter compact --success')
else:
    if env['target'] == 'shared_library':
        print("Build SharedLibrary for: ", env['target_name'])
        env.SharedLibrary(target=result_name, source=src_files)
    else:
        print("Build StaticLibrary for: ", env['target_name'])
        env.StaticLibrary(target=result_name, source=src_files)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
