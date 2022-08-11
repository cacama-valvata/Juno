all: pdf html

pdf: formatting.md workflow.md
	mkdir ./pdf
	pandoc formatting.md -o pdf/formatting.pdf
	pandoc workflow.md -o pdf/workflow.pdf
	pandoc design.md -o pdf/design.pdf

html: formatting.md workflow.md
	mkdir ./html
	pandoc formatting.md -o html/formatting.html
	pandoc workflow.md -o html/workflow.html
	pandoc design.md -o html/design.html

clean: 
	rm -rf ./html ./pdf
