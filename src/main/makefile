#preprocess
ifeq ($(PROJECT_SRC_PATH),)
	PROJECT_SRC_PATH = $(shell pwd)/..
endif

include $(PROJECT_SRC_PATH)/makefile.incl

.PHONEY : all clean rebuild install test

BUILD = libmwmath.a
LIB_INCS = $(wildcard *.h)

all:$(BUILD)

$(BUILD):$(LIB_OBJS)
	$(AR) $@ $^

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(MWMATH_MACRO) $(INC_MWSTL) $(INC_MWMATH) $(INC_MWGLOBAL) $(INC_LOG4CPLUS) -c $< -o $@

clean:
	$(RM) $(BUILD)
	$(RM) $(LIB_OBJS)

rebuild:
	$(MAKE) clean
	$(MAKE)

install:
	$(CP) $(BUILD) $(DIR_MWMATH_LIB)
	$(CP) $(LIB_INCS) $(DIR_MWMATH_INC)

test:
	$(MAKE)
	$(MAKE) install
	$(MAKE) -C $(DIR_TEST)
