
ascii_prn: ../../bin/prod_ascii_prn
.PHONY: ascii_prn

../../bin/prod_ascii_prn: ascii_prn.cc ../ENCODING_LAYER/ascii_endec.hpp ../BINARY_LAYER/prn_scrambling.hpp ../BINARY_LAYER/south_interface.hpp ../IO_INTERFACE/io_interface.hpp ../ENCODING_LAYER/ascii_endec.cc ../BINARY_LAYER/prn_scrambling.cc ../BINARY_LAYER/south_interface.cc ../IO_INTERFACE/io_interface.cc
	g++ -g -o $@ $< ../ENCODING_LAYER/ascii_endec.cc ../BINARY_LAYER/prn_scrambling.cc ../BINARY_LAYER/south_interface.cc ../IO_INTERFACE/io_interface.cc

