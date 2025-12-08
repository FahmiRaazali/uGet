# uGet Download Manager

uGet is a lightweight yet powerful Open Source download manager for GNU/Linux developed with GTK+.

## Build Instructions

This project uses the Meson build system.

### Prerequisites

You will need `meson` and `ninja` installed. You will also need to install the necessary dependencies for the project (e.g., `gtk3`, `libcurl`, etc.).

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
    The executable will be located at `build/src/ui-gtk/uget-gtk`.
    ```sh
    ./build/src/ui-gtk/uget-gtk
    ```
