# meson.build of src directory

# bitStream should come first because meson.build of encoder is dependent on bitStream
subdir('bitStream')
subdir('encoder')


bitconverter_exe = executable('bitconverter.cpp.executable', 
    sources: ['bitconverter.cpp'],
    dependencies : [bit_stream_dep],
    install : true)


compress_exe = executable('compress.cpp.executable', 
    sources: ['compress.cpp'],
    dependencies : [cxxopts_dep, bit_stream_dep, encoder_dep],
    install : true)


uncompress_exe = executable('uncompress.cpp.executable', 
    sources: ['uncompress.cpp'],
    dependencies : [cxxopts_dep, bit_stream_dep, encoder_dep, cxxopts_dep],
    install : true)