TARGETS=assert_UT

all: $(TARGETS)
test: $(TARGETS) $(addprefix run-,$(TARGETS))

%: %.cpp
	$(CXX) -o$@ $^ -lboost_unit_test_framework

run:
	./hello --log_level=test_suite > file.txt

clean:
	rm $(TARGETS)

help:
	@echo "https://www.ibm.com/developerworks/aix/library/au-ctools1_boost/"