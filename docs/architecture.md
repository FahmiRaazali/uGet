# uGet Architecture

This document describes the internal data structures and architecture of uGet.

## Node Hierarchy

```
UgNode
└── UgetNode (Root, Category, Download, File)
```

## UgetNode Tree Structure

```
Root ─┬─ Category1 ─┬─ Download1 (URI)
      │             │
      │             └─ Download2 (URI)
      │                (torrent path)
      │
      └─ Category2 ─┬─ Download3 (URI)
                    │  (metalink path)
                    │
                    └─ Download4 (URI)
```

## Virtual Views

### "All Category" - Real and Fake Nodes

```
  Real           Fake L1        Fake L2

Category0 ──┐
Category1 ──┼──> all ──────┬──> all active
Category2 ──┘              ├──> all queuing
                           ├──> all finished
                           └──> all recycled
```

### "All Status" - Real and Fake Nodes

```
  Real           Fake

Category ──┬──> active
           ├──> queuing
           ├──> finished
           ├──> recycled
           │
           └──> sorted
```

## Data Storage Format

Each category is stored in a separate JSON file.

### Example: `Category-Home.json`

```json
{
  "info": {
    "category": {},
    "common": {
      "name": "Home"
    },
    "proxy": {},
    "http": {},
    "ftp": {}
  },
  "children": [
    {
      "info": {
        "common": {
          "name": "download-file1",
          "file": "download-file1.torrent"
        },
        "files": {
          "collection": [
            {
              "name": "download-file1.zip",
              "type": 0
            }
          ]
        },
        "proxy": {},
        "http": {},
        "ftp": {}
      },
      "children": []
    },
    {
      "info": {
        "common": {
          "name": "download-file3",
          "file": "download-file3.7z"
        },
        "proxy": {},
        "http": {},
        "ftp": {}
      },
      "children": []
    }
  ]
}
```

## Source Code Structure

### `src/uglib/` (LGPL)

Low-level library for uGet. Based on:
- Standard C library
- POSIX/Windows threads
- Socket API
- libcurl

**Compile flags:**
- `HAVE_GLIB` - Enable if your program uses GLib

### `src/uget/` (LGPL)

Application core logic (see `UgetApp.h`). Contains:
- curl and aria2 plugins
- Download control
- Command line parsing
- Queue management

**Compile flags:**
- `HAVE_GLIB` - Enable if your program uses GLib
- `NDEBUG` - Disable debug code & messages in plugins
- `NO_RETRY_IF_CONNECT_FAILED` - Disable retry on connection failure
- `NO_URI_HASH` - Disable URI Hash Table (`UgetHash`)

### `src/ui-gtk/` (LGPL)

GTK3 user interface for uGet. Contains platform/library dependent code.

### `src/ui-gtk4/` (LGPL)

GTK4 user interface for uGet. Modern implementation using GtkApplication patterns.