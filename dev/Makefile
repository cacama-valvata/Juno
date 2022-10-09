# Compile developer documents into pdf, html, or both

# Either use natively installed pandoc or utilize container with pandoc
#    Comment out either line
PANDOC = pandoc
#PANDOC = docker run --rm -v "$(shell pwd):/data" -u $shell id -u:$(shell id -g) detjensrobert/arch-pandoc

# Pandoc options
OPTS = -V geometry:margin=1in --highlight=tango

# Which sections of the Vision and Scope document do you want to include?
#    Helpful for submitting class assignments that only want certain sections
#    Comment out either line
SECTS = $(sort $(wildcard vision-n-scope/*.md))
#SECTS = vision-n-scope/0-titlepage.md 


all: pdf-docs html-docs

%-docs: formatting.md workflow.md design.md
	[ ! -d "$*" ] && mkdir $*

	$(PANDOC) formatting.md -o $*/formatting.$* $(OPTS)
	$(PANDOC) workflow.md -o $*/workflow.$* $(OPTS)
	$(PANDOC) design.md -o $*/design.$* $(OPTS)
	$(PANDOC) $(SECTS) -o $*/vision-n-scope.pdf --metadata-file vision-n-scope/metadata.yml $(OPTS)

clean: 
	rm -rf ./html ./pdf
