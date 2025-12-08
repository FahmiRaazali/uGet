uglib_sources = [
  'UgStdio.c',
  'UgString.c',
  'UgThread.c',
  'UgSocket.c',
  'UgUtil.c',
  'UgFileUtil.c',
  'UgArray.c',
  'UgList.c',
  'UgSLink.c',
  'UgOption.c',
  'UgUri.c',
  'UgNode.c',
  'UgData.c',
  'UgInfo.c',
  'UgRegistry.c',
  'UgValue.c',
  'UgEntry.c',
  'UgBuffer.c',
  'UgJson.c',
  'UgJson-custom.c',
  'UgJsonFile.c',
  'UgJsonrpc.c',
  'UgJsonrpcSocket.c',
  'UgJsonrpcCurl.c',
  'UgHtml.c',
  'UgHtmlEntry.c',
  'UgHtmlFilter.c',
]

libuglib = static_library('uglib',
  uglib_sources,
  include_directories : inc,
  dependencies : [glib_dep, curl_dep],
  c_args : ['-D_GNU_SOURCE'] # Often needed for some extensions
)

libuglib_dep = declare_dependency(
    link_with : libuglib,
    include_directories : inc
)
