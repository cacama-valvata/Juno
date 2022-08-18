# Development Notes

Documents to aid in Juno development.

- Code style guide (formatting.md)
- Development guide (workflow.md)
- Design document (design.md)

The `images/` directory provides the images referenced in various documents (most notably `design.md`). Images are best viewed in their respective documents.

## Compilation

To compile the documents into HTML or PDF, install `pandoc`:

```
# Debian and Ubuntu
sudo apt install pandoc texlive

# Fedora
sudo dnf install pandoc texlive

# Arch and Manjaro
sudo pacman -Sy pandoc texlive-most
```

Build the docs with either:

`make html-docs`
`make pdf-docs`

Built documents will be found in their respective folders: `./html/` or `./pdf/`
