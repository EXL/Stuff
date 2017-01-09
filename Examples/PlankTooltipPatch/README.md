## Build and Run instructions

1. Download [Plank Sources](https://launchpad.net/plank/1.0/0.11.1/+download/plank-0.11.1.tar.xz), version 0.11.1;
2. Install all dependencies: **vala** with **valac**, **libbamf/bamf**, **libgtop**, **libwnck3** and other;
3. Unpack the sources for example, in */tmp* catalog:
    ```bash
    $ cd ~/Downloads
    $ tar -xJf plank-0.11.1.tar.xz -C /tmp/
    ```

4. Clone this gist repo:
    ```bash
    $ git clone https://gist.github.com/9596722a2b62a84483e861a43e08d847.git PlankTooltipPatch
    ```

5. Patch the sources:
    ```bash
    $ cd /tmp/plank-0.11.1/
    $ patch -Np1 < ~/Downloads/PlankTooltipPatch/Plank_0_11_1_show_tooltips_feature_for_yakimka.patch
    patching file data/ui/preferences.ui
    patching file lib/Widgets/PreferencesWindow.vala
    patching file lib/libplank.symbols
    ```

6. Compile Plank:
    ```bash
    $ ./autogen.sh --prefix=/usr
    $ make -j5
    ```

7. Run and enjoy:
    ```bash
    $ ./src/plank
    ```

## Misc

1. Run plank with preferences window:
    ```bash
    $ ./src/plank --preferences
    ```

2. Drop old plank settings:
    ```bash
    $ dconf reset -f /net/launchpad/plank/docks/dock1/
    ```
