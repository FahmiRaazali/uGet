# uGet Download Manager

uGet is a lightweight yet powerful open source download manager for GNU/Linux developed with GTK+.

## Features

- Multi-connection downloads (split files into segments for faster downloads)
- Download queue management and scheduler
- Clipboard monitoring for URLs
- Batch downloads with wildcard support
- Browser integration via JSON-RPC
- aria2 plugin support for advanced downloading
- Torrent and Metalink file support
- Pause and resume downloads
- Download categories and organization

## Build & Installation

This project uses the **Meson** build system.

### Prerequisites

To build uGet, you need the following tools and libraries:

- **Build Tools**: `meson`, `ninja`, `pkg-config`
- **Required Libraries**:
  - `gtk+-3.0` (>= 3.4)
  - `glib-2.0`
  - `libcurl` (>= 7.19.1)
- **Optional Libraries**:
  - `libnotify` - Desktop notifications
  - `appindicator3-0.1` - System tray icon
  - `gstreamer-1.0` - Sound notifications
  - `libcrypto` (OpenSSL) or `libgcrypt` (GnuTLS) - For MEGA plugin

### Building

1. **Set up the build directory:**
   ```sh
   meson setup build
   ```

2. **Compile the project:**
   ```sh
   meson compile -C build
   ```

3. **Run the application:**
   ```sh
   ./build/src/ui-gtk/uget-gtk
   ```

4. **Install (optional):**
   ```sh
   sudo meson install -C build
   ```

### Build Options

You can customize the build using `meson configure` or by passing `-Doption=value` during setup.

| Option | Default | Description |
|--------|---------|-------------|
| `notify` | `enabled` | Enable desktop notifications (libnotify) |
| `appindicator` | `auto` | Enable system tray icon (AppIndicator) |
| `gstreamer` | `enabled` | Enable sound notifications (GStreamer) |
| `openssl` | `enabled` | Enable OpenSSL support |
| `gnutls` | `false` | Enable GnuTLS support (alternative to OpenSSL) |
| `rss_notify` | `true` | Enable RSS update notifications |
| `unix_socket` | `false` | Enable UNIX domain socket for IPC |
| `pwmd` | `disabled` | Enable pwmd password manager support |

#### Examples

**Build without sound support:**
```sh
meson setup build -Dgstreamer=disabled
```

**Build without notifications:**
```sh
meson setup build -Dnotify=disabled
```

**Reconfigure an existing build:**
```sh
meson configure build -Dnotify=disabled
meson compile -C build
```

## Documentation

- [Architecture Overview](docs/architecture.md) - Technical documentation of uGet's core design
- [JSON-RPC API](docs/json-rpc-api.md) - Browser integration and remote control interface

## License

uGet is licensed under the GNU Lesser General Public License v2.1 (LGPL-2.1). See [COPYING](COPYING) for details.

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

## Links

- **Website**: https://ugetdm.com
- **Source**: https://github.com/ugetdm/uget