DEPEND_FILE = depend_file # dependency file name

CC = gcc 
AR = ar
RANLIB = ranlib # create Library list

LIB_NAME = lib_HDLC       # static library name
LIB_FULL_NAME = lib$(LIB_NAME).a	

LIB_SRCS = hdlc.c
LIB_OBJS = $(LIB_SRCS:.c=.o)  # create object file

LIBS = -l$(LIB_NAME)     #library name
LIB_DIR = -L./			# library directory

TARGET_SRCS = run.c
TARGET_OBJS = $(TARGET_SRCS:.c=.o)
TARGET_NAMES = test_SHDLC	

.SUFFIXES : .c .o

all : $(LIB_FULL_NAME) $(TARGET_NAMES)

$(LIB_FULL_NAME) : $(LIB_OBJS)		# Create Static Library Command 
	$(AR) rcv $@ $(LIB_OBJS)        # ar rcv liblib_HDLC hdlc.o
	$(RANLIB) $@

$(TARGET_NAMES): $(TARGET_OBJS)     
	$(CC) -o $(TARGET_NAMES) $(TARGET_SRCS) $(LIB_DIR) $(LIBS)
				# gcc -o test_SHDLC run.c -L. -llib_HDLC
depend:
	$(CC) -MM $(LIB_SRCS) $(TARGET_SRCS) > $(DEPEND_FILE)

clean :
	rm -f $(LIB_FULL_NAME) $(LIB_OBJS) $(TARGET_NAMES) $(TARGET_OBJS) $(DEPEND_FILE)


