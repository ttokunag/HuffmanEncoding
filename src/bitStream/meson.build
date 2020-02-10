bit_stream = library('bit_stream', sources: [
  'input/BitInputStream.cpp', 'input/BitInputStream.hpp',
  'output/BitOutputStream.cpp', 'output/BitOutputStream.hpp'])

inc = include_directories('.','input','output')

bit_stream_dep = declare_dependency(include_directories: inc,
  link_with: bit_stream)