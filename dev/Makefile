# Compile developer documents into pdf or html or whatever you want

# Either use natively installed pandoc or utilize container with pandoc
#    Comment out either line
#PANDOC = pandoc
PANDOC = docker run --rm -v $(shell pwd):/data detjensrobert/arch-pandoc:full

# Pandoc options
OPTS = -s -V geometry:margin=1in --highlight=tango -F pantable

# Which sections of the Vision and Scope document do you want to include?
#    Helpful for submitting class assignments that only want certain sections
#    Comment out either line
#SECTS = $(sort $(wildcard vision-n-scope/*.md))
D = vision-n-scope
SECTS = $(D)/0-titlepage.md $(D)/1-background.md $(D)/2-problem.md $(D)/3-solution.md $(D)/4-evaluation.md $(D)/5-stakeholders.md $(D)/6-constraints.md

# Change output file format
#    Default: pdf
OUT = pdf


all: out/formatting.$(OUT) out/workflow.$(OUT) out/design.$(OUT) out/vision-n-scope.$(OUT)

out/formatting.%: out/ formatting.md
	$(PANDOC) formatting.md -o out/formatting.$* $(OPTS)

out/workflow.%: out/ workflow.md
	$(PANDOC) workflow.md -o out/workflow.$* $(OPTS)

out/design.%: out/ design.md
#	$(PANDOC) design.md -o design.$* $(OPTS)
	cp design.pdf out/design.pdf

out/vision-n-scope.%: out/ vision-n-scope/*
	$(PANDOC) $(SECTS) -o out/vision-n-scope.$* --metadata-file vision-n-scope/metadata.yml $(OPTS)

out/:
	mkdir -p out/

clean: 
	rm -rf out/
