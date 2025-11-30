# Build with Meson

## Prerequisites

- Meson
- Ninja
- GTK+ 3.0
- GLib
- libcurl
- libnotify (optional)
- libappindicator3 (optional)
- GStreamer (optional)
- OpenSSL or GnuTLS

## Build Steps

1.  **Setup the build directory:**

    ```bash
    meson setup build
    ```

2.  **Compile:**

    ```bash
    meson compile -C build
    ```

3.  **Install (optional):**

    ```bash
    sudo meson install -C build
    ```

## Run

You can run the compiled binary directly:

```bash
./build/src/ui-gtk/uget-gtk
```

## Configuration Options

You can configure options using `meson configure`:

```bash
meson configure build -Dnotify=disabled
```

Available options (see `meson_options.txt`):
- `notify` - Enable libnotify support (default: enabled)
- `appindicator` - Build support for application indicators (default: auto)
- `gstreamer` - Enable GStreamer audio support (default: enabled)
- `pwmd` - Enable pwmd support (default: disabled)
- `rss_notify` - Enable RSS Notify (default: true)
- `unix_socket` - Enable UNIX Domain Socket (default: false)
- `openssl` - Enable OpenSSL support (default: enabled)
- `gnutls` - Enable GnuTLS support (default: false)

## Reconfiguring the Build

If you make changes to `meson.build` (such as changing the version number or build options), you need to reconfigure:

```bash
meson setup --reconfigure build
```

Then recompile:

```bash
meson compile -C build
```

## Changing Version

To change the project version:

1. Edit the `version` field in the root `meson.build` file
2. Reconfigure the build: `meson setup --reconfigure build`
3. Recompile: `meson compile -C build`

## Troubleshooting

### Version not updating after changing `meson.build`

If the version doesn't update after changing it in `meson.build`, make sure to:
1. Run `meson setup --reconfigure build` to regenerate `config.h`
2. Recompile with `meson compile -C build`

### Clean build

If you encounter issues, you can clean and rebuild:

```bash
rm -rf build
meson setup build
meson compile -C build
```
