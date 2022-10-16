# Compile developer documents into pdf, html, or both

# Either use natively installed pandoc or utilize container with pandoc
#    Comment out either line
#PANDOC = pandoc
PANDOC = docker run --rm -v $(shell pwd):/data detjensrobert/arch-pandoc:full

# Pandoc options
OPTS = -s -V geometry:margin=1in --highlight=tango

# Which sections of the Vision and Scope document do you want to include?
#    Helpful for submitting class assignments that only want certain sections
#    Comment out either line
#SECTS = $(sort $(wildcard vision-n-scope/*.md))
D = vision-n-scope
SECTS = $(D)/0-titlepage.md $(D)/1-background.md $(D)/2-problem.md


all: pdf-docs html-docs

%-docs: formatting.md workflow.md design.md
	mkdir -p $*

	$(PANDOC) formatting.md -o $*/formatting.$* $(OPTS)
	$(PANDOC) workflow.md -o $*/workflow.$* $(OPTS)
#	$(PANDOC) design.md -o $*/design.$* $(OPTS)
	cp design.pdf $*/design.pdf
	$(PANDOC) $(SECTS) -o $*/vision-n-scope.pdf --metadata-file vision-n-scope/metadata.yml $(OPTS)

clean: 
	rm -rf ./html ./pdf
