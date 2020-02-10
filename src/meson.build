subdir('encoder')
subdir('bitStream')

# TODO: Define autocomplete_exe to output executable file named 
#       autocomplete.cpp.executable

bitconverter_exe = executable('bitconverter.cpp.executable', 
    sources: ['bitconverter.cpp'],
    dependencies : [bit_stream_dep],
    install : true)