all: pdf-docs html-docs

%-docs: formatting.md workflow.md design.md
	[ ! -d "$*" ] && mkdir $*

	pandoc formatting.md -o $*/formatting.$* -V geometry:margin=1in --highlight=tango
	pandoc workflow.md -o $*/workflow.$* -V geometry:margin=1in --highlight=tango
	pandoc design.md -o $*/design.$* -V geometry:margin=1in --highlight=tango

clean: 
	rm -rf ./html ./pdf
