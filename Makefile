DOXYFILE = Doxyfile
DEPENDENCIES = "doxygen" "foo" "bar"


# Iterate through the dependencies and make sure they are
# installed. If not, let the user know and then stop.
define check_dependencies =
@for cmd in $(DEPENDENCIES); do \
    which $$cmd > /dev/null || (echo "Please install \"$$cmd\""; exit 1)  \
done
endef


check:
	$(check_dependencies)

docs:
	doxygen $(DOXYFILE)

.PHONY: docs check
