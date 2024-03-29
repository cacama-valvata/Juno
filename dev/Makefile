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
D = vision-n-scope
SECTS = $(sort $(wildcard vision-n-scope/*.md))
#SECTS = $(D)/0-titlepage.md $(D)/1-background.md $(D)/2-problem.md $(D)/3-solution.md $(D)/4-evaluation.md $(D)/5-stakeholders.md $(D)/6-constraints.md $(D)/7-contributions.md 8-iteration.md 9-changelog.md

# Change output file format
#    Default: pdf
OUT = pdf


all: out/formatting.$(OUT) out/workflow.$(OUT) out/design.$(OUT) out/capital-request.$(OUT) out/vision-n-scope.$(OUT) out/fall_retrospective.$(OUT)


out/formatting.%: out/ formatting.md
	$(PANDOC) formatting.md -o out/formatting.$* $(OPTS)

out/workflow.%: out/ workflow.md
	$(PANDOC) workflow.md -o out/workflow.$* $(OPTS)

out/design.%: out/ design.md
#	$(PANDOC) design.md -o design.$* $(OPTS)
	cp design.pdf out/design.pdf

out/capital-request.%: out/ capital-request.md
	$(PANDOC) capital-request.md -o out/capital-request.$* $(OPTS)

out/vision-n-scope.%: out/ vision-n-scope/*
	$(PANDOC) $(SECTS) -o out/vision-n-scope.$* --metadata-file vision-n-scope/metadata.yml $(OPTS)

out/fall_retrospective.%: out/ fall_retrospective.md
	$(PANDOC) fall_retrospective.md -o out/fall_retrospective.$* $(OPTS)

out/security_design_review.%: out/ security_design_review.md
	$(PANDOC) security_design_review.md -o out/security_design_review.$* $(OPTS)

out/:
	mkdir -p out/

clean: 
	rm -rf out/
