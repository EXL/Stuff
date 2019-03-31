### Convert BMP files to JPG images:

```bash
$ mogrify -format jpg *.bmp
```

### Create map list from files:

```bash
$ ls -1 | rev | cut -c 9- | rev | uniq > map_list.txt
```

### Create thumbnails:

```bash
$ mogrify -format jpg -path thumbs -thumbnail 320x232 *.jpg
```

### Optimize JPG images:

```bash
$ find -type f -iname "*.jpg" -exec jpegoptim --strip-all {} \;
```

### Optimize PNG images:

```bash
$ find -type f -iname "*.png" -exec optipng -o7 -strip all {} \;
```

Drop `images/` and `images/thumbs` dirictories with image files here. Syntax: `mapname000X.{jpg,png}`, where X is number of screen starts with 0.
