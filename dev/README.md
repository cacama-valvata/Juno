# Development Notes

Documents to aid in Juno development.

- Code style guide (formatting.md)
- Development guide (workflow.md)
- Design document (design.md)
- Vision & Scope class assignment (vision-n-scope/*)

The `images/` directory provides the images referenced in various documents (most notably `design.md`). Images are best viewed in their respective documents.

## Compilation

To compile the documents into PDF, install `pandoc`:

```
# Debian and Ubuntu
sudo apt install pandoc texlive

# Fedora
sudo dnf install pandoc texlive

# Arch and Manjaro
sudo pacman -Sy pandoc texlive-most

# Docker
md2pdfd () {
  docker run --rm -v $(pwd):/data -u $(id -u):$(id -g) detjensrobert/arch-pandoc:full "$1" -o "${1%%.md}.pdf" ${@:2}
}
md2pdfd file.md (options)
```

Build the docs with:

`make all`

Built documents will be found in the folder `out/`.

By default, the built files will be PDFs. To change which output format the docs are built into, change the `OUT` variable in `Makefile` to the appropriate file extension.
