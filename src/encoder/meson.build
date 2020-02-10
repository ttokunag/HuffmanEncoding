# meson.build of encoder directory

encoder = library('encoder', sources: ['HCNode.hpp', 'HCTree.hpp', 'HCTree.cpp'])

inc = include_directories('.')

encoder_dep = declare_dependency(include_directories: inc, link_with: encoder)