.SUFFIXES: .cc .o .lo

COMPILE = $(CXX) -Wall -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -g -O
INC_PATH =
LIB_PATH = -L/usr/local/lib

SHARED_OBJS = mp4.lo mp4_meta.lo

ALL_OBJS = $(SHARED_OBJS)

ALL_PRGS = 
ALL_LIBS = libtsmp4.so

all: $(ALL_OBJS) $(ALL_PRGS) $(ALL_LIBS)

libtsmp4.so:
	$(COMPILE) -o $@ $< -shared $(SHARED_OBJS) $(LIB_PATH)
.cc:
	$(COMPILE) -o $@ $< $(SHARED_OBJS) $(LIB_PATH) $(INC_PATH)
.cc.o:
	$(COMPILE) -c -o $@ $<  $(INC_PATH)
.cc.lo:
	$(COMPILE) -c -fPIC -o $@ $<  $(INC_PATH)
install:
	/bin/cp -f $(ALL_LIBS) /usr/lib64/trafficserver/plugins/
clean:
	rm -rf $(ALL_OBJS) $(ALL_PRGS) $(ALL_LIBS) build

