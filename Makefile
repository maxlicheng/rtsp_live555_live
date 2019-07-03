ARCH = linux
DEFAULT_ARCH = linux
ifeq ($(ARCH),$(DEFAULT_ARCH))
ARCH_PATH = linux
CPLUSPLUS_COMPILER =    c++
#$(info arch is $(ARCH_PATH))
else
ARCH_PATH = armlinux
CPLUSPLUS_COMPILER =    arm-none-linux-gnueabi-c++
#$(info arch is $(ARCH_PATH))
endif
INCLUDES         = -I./include/$(ARCH_PATH)/live555/UsageEnvironment -I./include/$(ARCH_PATH)/live555/groupsock \
                                -I./include/$(ARCH_PATH)/live555/liveMedia -I./include/$(ARCH_PATH)/live555/BasicUsageEnvironment \
                                -I./include/$(ARCH_PATH)/x264 -I./include/encoder
LIVE555_LIBS =  ./lib/$(ARCH_PATH)/livelib/libliveMedia.a ./lib/$(ARCH_PATH)/livelib/libgroupsock.a \
		./lib/$(ARCH_PATH)/livelib/libBasicUsageEnvironment.a ./lib/$(ARCH_PATH)/livelib/libUsageEnvironment.a
X264_LIBS 	 =  ./lib/$(ARCH_PATH)/x264lib/libx264.so ./lib/$(ARCH_PATH)/x264lib/libx264.so.157
LIBS         =  $(LIVE555_LIBS) $(X264_LIBS)

COMPILE_OPTS =      $(INCLUDES) -I. -O2 -DSOCKLEN_T=socklen_t -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -g
C 			 =         c
C_COMPILER   =       cc
C_FLAGS 	 =       $(COMPILE_OPTS) $(CPPFLAGS) $(CFLAGS)
CPP 		 =           cpp
CPLUSPLUS_FLAGS =   $(COMPILE_OPTS) -Wall -DBSD=1 $(CPPFLAGS) $(CXXFLAGS)
OBJ 		 =           o
LINK 		 =  $(CPLUSPLUS_COMPILER) -o
LINK_OPTS    =  -ldl  -lm -lpthread -ldl -g
CONSOLE_LINK_OPTS = $(LINK_OPTS)
LINK_OBJ	 = H264FramedLiveSource.o H264VideoStreamer.o

APP = H264VideoStreamer

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<
.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

$(APP): $(LINK_OBJ)
	$(LINK)$@  $(LINK_OBJ)  $(LIBS) $(CONSOLE_LINK_OPTS)
	
clean:
	-rm -rf *.$(OBJ) $(APP) core *.core *~ include/*~

