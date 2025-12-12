# uGet JSON-RPC API

uGet provides a JSON-RPC interface over TCP at `localhost:14777`. This allows external applications (such as browser extensions) to communicate with uGet.

## Methods

### `uget.sendCommand`

Sends command-line arguments to uGet. This is typically used to add new downloads.

#### Request

```json
{
  "jsonrpc": "2.0",
  "method": "uget.sendCommand",
  "params": [
    "--user=foo",
    "--password=bar",
    "http://foo.bar.idv/test.mp4"
  ],
  "id": 1
}
```

#### Response

```json
{
  "jsonrpc": "2.0",
  "result": true,
  "id": 1
}
```

#### Parameters

The `params` array accepts the same arguments as the uGet command line:

| Parameter | Description |
|-----------|-------------|
| `--user=USERNAME` | HTTP/FTP username |
| `--password=PASSWORD` | HTTP/FTP password |
| `--folder=PATH` | Download destination folder |
| `--filename=NAME` | Override filename |
| `--category-index=N` | Category index (0-based) |
| `--quiet` | Don't show download dialog |
| `URL` | The URL to download |

---

### `uget.present`

Brings the uGet main window to the foreground.

#### Request

```json
{
  "jsonrpc": "2.0",
  "method": "uget.present",
  "id": 1
}
```

#### Response

```json
{
  "jsonrpc": "2.0",
  "result": true,
  "id": 1
}
```

---

## Connection Details

- **Protocol**: JSON-RPC 2.0
- **Transport**: TCP socket
- **Host**: `localhost` (127.0.0.1)
- **Port**: `14777`

## Example Usage

Using `netcat` to send a download request:

```bash
echo '{"jsonrpc":"2.0","method":"uget.sendCommand","params":["https://example.com/file.zip"],"id":1}' | nc localhost 14777
```

Using `curl`:

```bash
curl -X POST -H "Content-Type: application/json" \
  -d '{"jsonrpc":"2.0","method":"uget.sendCommand","params":["https://example.com/file.zip"],"id":1}' \
  http://localhost:14777
```
