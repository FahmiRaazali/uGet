# uGet Architecture

This document describes the internal architecture, data structures, and design patterns of uGet.

## Table of Contents

- [Project Structure](#project-structure)
- [Library Overview](#library-overview)
- [Node Hierarchy](#node-hierarchy)
- [Virtual Views](#virtual-views)
- [Plugin System](#plugin-system)
- [Threading Model](#threading-model)
- [Data Storage Format](#data-storage-format)
- [Build Configuration](#build-configuration)

---

## Project Structure

```
src/
├── uglib/              # Low-level utility library
│   └── meson.build     # Builds: libuglib
│
├── uget/               # uGet core library
│   ├── UgetMedia-youtube.c   # YouTube parser
│   ├── UgetPluginMedia.c     # Media plugin for YouTube
│   ├── UgetPluginMega.c      # MEGA.nz plugin
│   └── meson.build           # Builds: libuget
│
└── ui-gtk/             # GTK3 UI
    └── meson.build           # Links: libuglib + libuget
```

### Naming Conventions

| Prefix | Library | Description |
|--------|---------|-------------|
| `ug_*` | uglib | Low-level utilities (strings, files, JSON, etc.) |
| `uget_*` | uget | Application-specific (plugins, nodes, data) |
| `ugtk_*` | ui-gtk | GTK UI components |

---

## Library Overview

### uglib (Low-level Utilities)

Provides common utilities used throughout the project:

| File | Purpose |
|------|---------|
| `UgString.c` | String manipulation, URI encoding/decoding |
| `UgUri.c` | URI parsing |
| `UgUtil.c` | General utilities |
| `UgFileUtil.c` | File operations |
| `UgJson.c` | JSON parser/writer |
| `UgValue.c` | JSON value representation |
| `UgEntry.c` | JSON-to-struct mapping |
| `UgBuffer.c` | Dynamic buffer |
| `UgList.c` | Linked list |
| `UgNode.c` | Tree node structure |
| `UgData.c` | Data container |
| `UgInfo.c` | Info container |
| `UgRegistry.c` | Type registry |
| `UgThread.c` | Thread abstraction |
| `UgSocket.c` | Socket abstraction |

### uget (Application Core)

Contains the download manager logic:

| File | Purpose |
|------|---------|
| `UgetNode.c` | Download/category node |
| `UgetData.c` | Download data structures |
| `UgetFiles.c` | File list management |
| `UgetTask.c` | Download task scheduler |
| `UgetApp.c` | Application state |
| `UgetPlugin.c` | Plugin base class |
| `UgetPluginCurl.c` | CURL-based downloader |
| `UgetPluginAria2.c` | aria2 RPC plugin |
| `UgetPluginMedia.c` | YouTube media plugin |
| `UgetPluginMega.c` | MEGA.nz plugin |
| `UgetEvent.c` | Event system |
| `UgetHash.c` | Hash verification |

### ui-gtk (GTK3 Interface)

GTK3 user interface:

| File | Purpose |
|------|---------|
| `UgtkApp.c` | Main application |
| `UgtkWindow.c` | Main window |
| `UgtkTrayIcon.c` | System tray icon |
| `UgtkMenubar.c` | Menu bar |
| `UgtkNodeView.c` | Download list view |
| `UgtkNodeDialog.c` | Download properties dialog |
| `UgtkBatchDialog.c` | Batch download dialog |
| `UgtkSettingDialog.c` | Settings dialog |
| `UgtkAboutDialog.c` | About dialog |

---

## Node Hierarchy

uGet uses a tree structure to organize downloads and categories:

```
UgetApp
└── real (UgetNode)           # Root node for real data
    ├── Category 1 (UgetNode)
    │   ├── Download A (UgetNode)
    │   ├── Download B (UgetNode)
    │   └── Download C (UgetNode)
    ├── Category 2 (UgetNode)
    │   └── Download D (UgetNode)
    └── ...
```

### UgetNode Structure

```c
struct UgetNode {
    UgetNode*  parent;      // Parent node
    UgetNode*  children;    // First child
    UgetNode*  next;        // Next sibling
    UgetNode*  prev;        // Previous sibling
    UgetNode*  real;        // Real node (for virtual nodes)
    UgInfo*    info;        // Attached data (UgetCommon, UgetProgress, etc.)
    int        state;       // Node state flags
};
```

### Info Attachments

Each node can have multiple info structures attached:

| Info Type | Purpose |
|-----------|---------|
| `UgetCommon` | URL, filename, folder, state |
| `UgetProgress` | Download progress, speed, ETA |
| `UgetProxy` | Proxy settings |
| `UgetHttp` | HTTP settings (user, password, referrer) |
| `UgetFtp` | FTP settings |
| `UgetLog` | Log messages |
| `UgetRelation` | Task/plugin relationship |

---

## Virtual Views

uGet uses virtual nodes to provide different views of the same data:

```
UgetApp
├── real          # Actual data (categories → downloads)
├── split         # Downloads split from categories (flat list)
├── sorted        # Sorted view of downloads
├── mix           # Mixed view (all downloads)
└── mix_split     # Split view of mix
```

### Filter Functions

Virtual views use filter functions to control what appears:

```c
// Example: Show only active downloads
int filter_active(UgetNode* node, UgetNode* src) {
    UgetRelation* relation = ug_info_get(src->info, UgetRelationInfo);
    if (relation && relation->task)
        return TRUE;  // Include in view
    return FALSE;     // Exclude
}
```

---

## Plugin System

uGet uses a plugin architecture for download engines:

### Plugin Types

| Plugin | Purpose |
|--------|---------|
| `UgetPluginCurl` | HTTP/HTTPS/FTP downloads via libcurl |
| `UgetPluginAria2` | BitTorrent/Metalink via aria2 RPC |
| `UgetPluginMedia` | YouTube video downloads |
| `UgetPluginMega` | MEGA.nz downloads |

### Plugin Interface

```c
struct UgetPluginClass {
    const char*  name;
    int  (*start)(UgetPlugin* plugin, UgetNode* node);
    int  (*stop)(UgetPlugin* plugin);
    int  (*sync)(UgetPlugin* plugin, UgetNode* node);
    // ...
};
```

### Plugin Lifecycle

1. **Create**: `uget_plugin_new(PluginClass)`
2. **Start**: `plugin->start(plugin, node)` - Begin download
3. **Sync**: `plugin->sync(plugin, node)` - Update progress
4. **Stop**: `plugin->stop(plugin)` - Pause/cancel

---

## Threading Model

### Main Components

1. **UI Thread**: GTK main loop, handles user interaction
2. **Download Threads**: One per active download (plugin manages)
3. **aria2 Thread**: Single thread for aria2 RPC communication

### Synchronization

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│   UI Thread  │     │ Plugin Thread │     │ aria2 Thread │
│              │     │               │     │              │
│  UgtkApp     │◄────│  UgetPlugin   │◄────│  UgetAria2   │
│  (GTK main)  │     │  (download)   │     │  (JSON-RPC)  │
└──────────────┘     └──────────────┘     └──────────────┘
       │                    │                    │
       └────────────────────┴────────────────────┘
                    Mutex + Condition Variables
```

### Thread Safety

- `UgetNode` modifications use `ug_mutex`
- Plugin state changes are atomic
- Event queue is thread-safe

---

## Data Storage Format

uGet stores data in JSON format:

### Directory Structure

```
~/.config/uGet/
├── Setting.json        # Application settings
├── CategoryList.json   # Category metadata
└── category0/          # Per-category folder
    ├── *.json          # Download entries
    └── ...
```

### Download Entry Format

```json
{
  "common": {
    "uri": "https://example.com/file.zip",
    "file": "file.zip",
    "folder": "/home/user/Downloads"
  },
  "progress": {
    "complete": 1048576,
    "total": 10485760
  }
}
```

---

## Build Configuration

### Meson Options

| Option | Default | Description |
|--------|---------|-------------|
| `notify` | `true` | Desktop notifications via libnotify |
| `appindicator` | `true` | AppIndicator tray icon support |
| `gstreamer` | `true` | Sound notifications via GStreamer |
| `openssl` | `false` | OpenSSL for MEGA plugin |
| `pwmd` | `false` | Password manager daemon support |

### Build Commands

```bash
# Configure
meson setup build

# Compile
meson compile -C build

# Install
sudo meson install -C build

# Run tests
meson test -C build
```

### Dependencies

Required:
- GTK+ 3.0 (>= 3.4)
- GLib 2.0
- libcurl (>= 7.19.1)

Optional:
- libnotify (desktop notifications)
- appindicator3 (system tray)
- GStreamer (sound notifications)
- OpenSSL (MEGA plugin)
- libpwmd (password manager)

---

## Key Design Patterns

### 1. Info Registry Pattern

Types are registered globally and looked up by ID:

```c
// Register type
ug_registry_add(&registry, UgetCommonInfo);

// Look up by name
const UgDataInfo* info = ug_registry_find(&registry, "common");
```

### 2. Virtual Node Pattern

Views are created by linking virtual nodes to real nodes:

```c
// Create virtual view with filter
uget_node_make_fake(virtual_root, real_root, filter_func);
```

### 3. Plugin Agent Pattern

Plugins can delegate to other plugins:

```c
// Agent pattern for aria2
UgetPluginAgent → UgetPluginAria2 → aria2 daemon
```

---

## Further Reading

- [uGet Website](https://ugetdm.com)
- [GTK Documentation](https://docs.gtk.org/)
- [libcurl Documentation](https://curl.se/libcurl/)
- [aria2 Manual](https://aria2.github.io/)