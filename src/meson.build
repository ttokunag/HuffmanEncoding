subdir('bitStream')
subdir('encoder')

biconverter_exe = executable('bitconverter.cpp.executable', 
    sources: ['bitconverter.cpp'],
    dependencies : [bit_stream_dep],
    install : true)

compress_exe = executable('compress.cpp.executable', 
    sources: ['compress.cpp'],
    dependencies : [encoder_dep],
    install : true)

uncompress_exe = executable('uncompress.cpp.executable', 
    sources: ['uncompress.cpp'],
    dependencies : [encoder_dep],
    install : true)