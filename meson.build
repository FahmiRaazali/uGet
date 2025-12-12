project('uget', 'c',
  version : '2.3.0',
  default_options : ['warning_level=1', 'c_std=gnu99'])

add_project_arguments('-DHAVE_CONFIG_H', language : 'c')

cc = meson.get_compiler('c')

# Dependencies
gtk_dep = dependency('gtk+-3.0', version : '>= 3.4')

glib_dep = dependency('glib-2.0')
gthread_dep = dependency('gthread-2.0')
curl_dep = dependency('libcurl', version : '>= 7.19.1')
libnotify_dep = dependency('libnotify', required : get_option('notify'))

appindicator_dep = dependency('appindicator3-0.1', required : get_option('appindicator'))

gstreamer_dep = dependency('gstreamer-1.0', required : get_option('gstreamer'))
if not gstreamer_dep.found()
  gstreamer_dep = dependency('gstreamer-0.10', required : get_option('gstreamer'))
endif
libpwmd_dep = dependency('libpwmd-8.0', version : '>= 8.3.0', required : get_option('pwmd'))
openssl_dep = dependency('libcrypto', required : get_option('openssl'))
libgcrypt_dep = dependency('libgcrypt', required : false)

# Configuration
conf_data = configuration_data()
conf_data.set_quoted('PACKAGE', meson.project_name())
conf_data.set_quoted('VERSION', meson.project_version())
conf_data.set_quoted('PACKAGE_VERSION', meson.project_version())
conf_data.set_quoted('GETTEXT_PACKAGE', meson.project_name())
conf_data.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
conf_data.set_quoted('UG_DATADIR', join_paths(get_option('prefix'), get_option('datadir')))

if glib_dep.found()
  conf_data.set('HAVE_GLIB', 1)
endif

if libnotify_dep.found()
  conf_data.set('HAVE_LIBNOTIFY', 1)
endif

if appindicator_dep.found()
  conf_data.set('HAVE_APP_INDICATOR', 1)
endif

if gstreamer_dep.found()
  conf_data.set('HAVE_GSTREAMER', 1)
endif

if libpwmd_dep.found()
  conf_data.set('HAVE_LIBPWMD', 1)
endif

if get_option('rss_notify')
  conf_data.set('HAVE_RSS_NOTIFY', 1)
endif

if get_option('unix_socket')
  conf_data.set('USE_UNIX_DOMAIN_SOCKET', 1)
endif

# Feature flags - all features enabled for GTK UI compatibility
# Future: Add conditional compilation with #ifdef guards in UI code
# to allow disabling individual plugins/features
conf_data.set('HAVE_PLUGIN_CURL', 1)
conf_data.set('HAVE_PLUGIN_ARIA2', 1)
conf_data.set('HAVE_RSS', 1)
conf_data.set('HAVE_BATCH_SEQUENCE', 1)
conf_data.set('HAVE_IPC', 1)

if openssl_dep.found()
  conf_data.set('USE_OPENSSL', 1)
endif

# GnuTLS support (simplified logic compared to configure.ac for now)
if get_option('gnutls')
    libgcrypt_config = find_program('libgcrypt-config', required : false)
    if libgcrypt_config.found()
        conf_data.set('USE_GNUTLS', 1)
        # We might need to extract flags manually if pkg-config fails for gcrypt
        # For now, assume dependency('libgcrypt') works or we might need a custom dependency
    endif
endif

configure_file(output : 'config.h',
               configuration : conf_data)

# Include directories
inc = include_directories('.', 'src/uglib', 'src/uget')

# Subdirectories
subdir('src')
subdir('data')
subdir('po')
subdir('tests')
