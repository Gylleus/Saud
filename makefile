SRC = game.cpp entity.cpp item.cpp wizard.cpp environment.cpp health_item.cpp key.cpp vendor.cpp

OBJS = $(SRC:.cpp=.o)

CO = g++
CFLAGS = -Wall -std=c++0x
LFLAGS =
LINK_TARGET = game_test
all : depend $(LINK_TARGET)

clean :
	rm -f $(LINK_TARGET) $(OBJS) ./.depend

depend: .depend

.depend : $(SRC)
	rm -f ./.depend
	$(CO) $(CFLAGS) -MM $^ -MF ./.depend

$(LINK_TARGET) : $(OBJS)
	$(CO) $^ $(LFLAGS) -o $@

%.o : %.cpp
	$(CO) $< $(CFLAGS) -c

include .depend

