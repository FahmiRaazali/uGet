# uGet Download Manager

uGet is a lightweight yet powerful Open Source download manager for GNU/Linux developed with GTK+.

## Build & Installation

This project uses the **Meson** build system.

### Prerequisites

To build uGet, you need the following tools and libraries:

*   **Build Tools**: `meson`, `ninja`, `pkg-config`
*   **Required Libraries**:
    *   `gtk+-3.0` (for GTK3 build) OR `gtk4` (for GTK4 build)
    *   `libcurl`
    *   `libnotify` (optional, for notifications)
    *   `libappindicator3` (optional, for tray icon)
    *   `gstreamer-1.0` (optional, for sound)
    *   `openssl` or `gnutls`

### Building

1.  **Set up the build directory:**
    ```sh
    meson setup build
    ```

2.  **Compile the project:**
    ```sh
    meson compile -C build
    ```

3.  **Run the application:**
    ```sh
    ./build/src/ui-gtk/uget-gtk
    ```

4.  **Install (optional):**
    ```sh
    sudo meson install -C build
    ```

### Configuration Options

You can customize the build using `meson configure` or by passing `-Doption=value` during setup.

| Option | Default | Description |
| :--- | :--- | :--- |
| `gtk_version` | `'3'` | Choose GTK version: `'3'`, `'4'`, or `'both'` |
| `notify` | `enabled` | Enable system notifications (libnotify) |
| `appindicator` | `auto` | Build support for AppIndicator (tray icon) |
| `gstreamer` | `enabled` | Enable audio support via GStreamer |
| `openssl` | `enabled` | Enable OpenSSL support |
| `gnutls` | `false` | Enable GnuTLS support (alternative to OpenSSL) |
| `rss_notify` | `true` | Enable RSS update notifications |
| `unix_socket` | `false` | Enable UNIX Domain Socket control |

#### Configuration Examples

**Build with GTK 4 (Experimental):**
```sh
meson setup build -Dgtk_version=4
```

**Build without PulseAudio/GStreamer:**
```sh
meson setup build -Dgstreamer=disabled
```

**Reconfigure an existing build:**
```sh
meson configure build -Dgtk_version=3 -Dnotify=disabled
meson compile -C build
```
