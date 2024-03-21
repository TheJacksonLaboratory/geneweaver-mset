project('purelib-and-platlib', 'cpp',
    default_options : ['cpp_std=c++11']
    )

py = import('python').find_installation(pure: false)

py.extension_module(
    'mset',
    'src/geneweaver/tools/mset/cpp/mset.cpp', # Adjusted path to match actual location
    install : true,
    subdir : 'geneweaver/tools/mset/cpp'
)