encoder = library('encoder', sources: ['HCNode.hpp', 'HCTree.hpp','HCTree.cpp'], dependencies: [bit_stream_dep])

inc = include_directories('.')

encoder_dep = declare_dependency(include_directories: inc,
  link_with: encoder)