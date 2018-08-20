#
# @(#) File:        Makefile
# @(#) Purpose:     Master build file
# @(#) Project:     Research Library
# @(#) Version:     1.5.1
#
# @(#) Created:     2016-08-11 08:03 mbejeran
# @(#) Modified:    2016-08-16 15:12 mbejeran
#
# @(#) Author:      Marc Bejerano <marcbejerano@gmail.com>
#
# @(#) Copyright:   Copyright (C) 2016, Hindsite Solutions, LLC., All Rights Reserved
# @(#) License:     BSD 3-Clause
#
# Copyright (c) 2016, Hindsite Solutions, LLC.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#

VERSION=1.5.1
ifndef PREFIX
	PREFIX=$(HOME)/Library
endif
PROJECTS = libTools libProperties libConfiguration libLogging

.PHONY: all
all: $(PROJECTS)

.PHONY: debug
debug:
	@DEBUG=1 make

.PHONY: release
release:
	@RELEASE=1 make

.PHONY: docs
docs:
	@echo "Generating documentation"
	@doxygen Doxyfile > doxygen.log

clean: $(PROJECTS)
	@echo "Removing generated documentation"
	@rm -fr doxygen.log docs 2>/dev/null

.PHONY: install
install: $(PROJECTS)
	@echo "---"
	@echo "All libraries installed to $(PREFIX)/lib"
	@echo "All headers installed to $(PREFIX)/include"

.PHONY: test
test: $(PROJECTS)

.PHONY: check
check: $(PROJECTS)

#install: $(TARGET) $(HEADERS)
#	$(foreach elemet,$(HEADERS),$(install -g root -o root -m 0644 -D $(element) /usr/local/include/research/$(element)))

.PHONY: $(PROJECTS)
$(PROJECTS):
	cd $@ && PREFIX=$(PREFIX) VERSION=$(VERSION) make $(MAKECMDGOALS)

