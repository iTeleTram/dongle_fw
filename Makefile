.PHONY: clean All

All:
	@echo "----------Building project:[ dongle - Debug ]----------"
	@"$(MAKE)" -f  "dongle.mk" && "$(MAKE)" -f  "dongle.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ dongle - Debug ]----------"
	@"$(MAKE)" -f  "dongle.mk" clean
