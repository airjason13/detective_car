SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
#OBJS := main.o
DETECTIVE_OBJS := $(filter %.o, $(OBJS))
TARGET_DETECTIVE := detective
# targets
TARGET :=  $(TARGET_DETECTIVE)
# varables used in yocto
#bindir ?= /usr/bin

#LIBS :=

.PHONY: clean

all: $(TARGET)

%.o : %.c
	$(CC) -c $< -o $@ 
#	$(CC) -c $< -o $@ ${LDFLAGS} ${LIBS}

$(TARGET_DETECTIVE) : $(DETECTIVE_OBJS)
	$(CC) $(OBJS) -o $@ 
#	$(CC) $(DETECTIVE_OBJS) -o $@ ${LIBS} ${LDFLAGS}

#install:
#	install -d $(DESTDIR)$(bindir)
#	install -m 755 detective $(DESTDIR)$(bindir)/

clean:
	rm $(OBJS) 2>&1 > /dev/null
	rm $(TARGET_DETECTIVE) 2>&1 > /dev/null
