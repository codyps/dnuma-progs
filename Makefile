
TARGETS = dnuma-trace-2
obj-dnuma-trace-2 = dnuma-trace.o

include base.mk

.PHONY: install-dnuma
install-dnuma:
	mkdir -p $(BINDIR) &&	\
	cp bin/dnuma-test $(BINDIR)/dnuma-test && \
	cp bin/meminfo    $(BINDIR)/meminfo && \
	cp bin/dnuma-stats $(BINDIR)/dnuma-stats

install : install-dnuma
