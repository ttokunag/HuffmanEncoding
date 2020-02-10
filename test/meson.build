  
test_bit_input_stream_exe = executable('test_BitInputStream.cpp.executable', 
    sources: ['test_BitInputStream.cpp'], 
    dependencies : [bit_stream_dep, gtest_dep])
test('my BitInputStream test', test_bit_input_stream_exe)


test_bit_output_stream_exe = executable('test_BitOutputStream.cpp.executable', 
    sources: ['test_BitOutputStream.cpp'], 
    dependencies : [bit_stream_dep, gtest_dep]) # dependent on bitStream
test('my BitOutputStream test', test_bit_output_stream_exe)


test_hc_tree_exe = executable('test_HCTree.cpp.executable', 
    sources: ['test_HCTree.cpp'], 
    dependencies : [bit_stream_dep, encoder_dep, gtest_dep])
test('my HCTree test', test_hc_tree_exe)