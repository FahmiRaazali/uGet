uget_gtk4_sources = [
  'UgtkUtil.c', 'UgtkConfig.c', 'UgtkSetting.c',
  'UgtkNodeList.c', 'UgtkNodeTree.c', 'UgtkNodeView.c',
  'UgtkTraveler.c', 'UgtkSummary.c',
  'UgtkTrayIcon.c', 'UgtkBanner.c',
  'UgtkSequence.c', 'UgtkSelector.c',
  'UgtkProxyForm.c', 'UgtkDownloadForm.c', 'UgtkCategoryForm.c',
  'UgtkNodeDialog.c', 'UgtkBatchDialog.c',
  'UgtkScheduleForm.c', 'UgtkSettingForm.c', 'UgtkSettingDialog.c',
  'UgtkConfirmDialog.c', 'UgtkAboutDialog.c',
  'UgtkMenubar.c', 'UgtkMenubar-ui.c',
  'UgtkApp.c', 'UgtkApp-ui.c', 'UgtkApp-callback.c',
  'UgtkApp-timeout.c', 'UgtkApp-main.c'
]

executable('uget-gtk4',
  uget_gtk4_sources,
  include_directories : inc,
  dependencies : [
    gtk4_dep,
    glib_dep,
    curl_dep,
    libnotify_dep,
    appindicator_dep,
    gstreamer_dep,
    libpwmd_dep,
    openssl_dep,
    libgcrypt_dep,
    libuglib_dep,
    libuget_dep
  ],
  install : true
)
