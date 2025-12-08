test_sources = [
  'test-json.c',
  'test-jsonrpc.c',
  'test-plugin+app.c',
  'test-info.c',
  'test-uglib.c',
  'test-uget.c'
]

# We need to build each test individually
test_json = executable('test-json', 'test-json.c',
  include_directories : inc,
  dependencies : [libuglib_dep, glib_dep, curl_dep]
)
test('test-json', test_json)

test_jsonrpc = executable('test-jsonrpc', 'test-jsonrpc.c',
  include_directories : inc,
  dependencies : [libuget_dep, libuglib_dep, glib_dep, curl_dep]
)
test('test-jsonrpc', test_jsonrpc)

test_plugin_app = executable('test-plugin-app', 'test-plugin+app.c',
  include_directories : inc,
  dependencies : [libuget_dep, libuglib_dep, glib_dep, curl_dep, libgcrypt_dep, openssl_dep]
)
test('test-plugin-app', test_plugin_app)

test_info = executable('test-info', 'test-info.c',
  include_directories : inc,
  dependencies : [libuglib_dep, glib_dep, curl_dep]
)
test('test-info', test_info)

test_uglib = executable('test-uglib', 'test-uglib.c',
  include_directories : inc,
  dependencies : [libuglib_dep, glib_dep, curl_dep]
)
test('test-uglib', test_uglib)

test_uget = executable('test-uget', 'test-uget.c',
  include_directories : inc,
  dependencies : [libuget_dep, libuglib_dep, glib_dep, curl_dep]
)
test('test-uget', test_uget)
