##
##	[makefile]
##	Created by Micael Levi on 09/06/2016
##	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
##

-include *.mk


.PHONY: depend clean


all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o  $@ $^ $(LIBS)
	$(PRINT) $(MSGUSO)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(MAIN)
	$(PRINT) "ARQUIVOS REMOVIDOS:\n$(OBJS) $(MAIN)"

mostlyclean:
	@$(RM) $(OBJS)
	$(PRINT) "OBJETOS REMOVIDOS."

depend: $(SRCS)
	makedepend $(INCLUDES) $^
