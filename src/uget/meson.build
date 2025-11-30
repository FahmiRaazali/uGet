uget_sources = [
  'UgetSequence.c',
  'UgetRss.c',
  'UgetRpc.c',
  'UgetOption.c',
  'UgetData.c',
  'UgetFiles.c',
  'UgetNode.c',
  'UgetNode-compare.c',
  'UgetNode-filter.c',
  'UgetTask.c',
  'UgetHash.c',
  'UgetSite.c',
  'UgetApp.c',
  'UgetEvent.c',
  'UgetPlugin.c',
  'UgetA2cf.c',
  'UgetCurl.c',
  'UgetAria2.c',
  'UgetMedia.c',
  'UgetMedia-youtube.c',
  'UgetPluginCurl.c',
  'UgetPluginAria2.c',
  'UgetPluginMedia.c',
  'UgetPluginAgent.c',
  'UgetPluginMega.c',
  'UgetPluginEmpty.c',
]

if libpwmd_dep.found()
  uget_sources += 'pwmd.c'
endif

libuget = static_library('uget',
  uget_sources,
  include_directories : inc,
  dependencies : [glib_dep, libpwmd_dep],
)

libuget_dep = declare_dependency(
    link_with : libuget,
    include_directories : inc
)
