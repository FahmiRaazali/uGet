/*
 *
 *   Copyright (C) 2012-2020 by C.H. Huang
 *   plushuang.tw@gmail.com
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  ---
 *
 *  In addition, as a special exception, the copyright holders give
 *  permission to link the code of portions of this program with the
 *  OpenSSL library under certain conditions as described in each
 *  individual source file, and distribute linked combinations
 *  including the two.
 *  You must obey the GNU Lesser General Public License in all respects
 *  for all of the code used other than OpenSSL.  If you modify
 *  file(s) with this exception, you may extend this exception to your
 *  version of the file(s), but you are not obligated to do so.  If you
 *  do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source
 *  files in the program, then also delete it here.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <unistd.h>

// ----------------------------------------------------------------------------
// path

#if defined _WIN32 || defined _WIN64
#include <windows.h>

const char *ugtk_get_install_dir(void) {
  static gchar *install_dir = NULL;

  if (install_dir == NULL) {
    gchar *path;
    gunichar2 *path_wcs;
    HMODULE hmod;

    hmod = GetModuleHandle(NULL);
    // UNICODE
    path_wcs = g_malloc(sizeof(wchar_t) * MAX_PATH);
    GetModuleFileNameW(hmod, path_wcs, MAX_PATH);
    path = g_utf16_to_utf8(path_wcs, -1, NULL, NULL, NULL);
    g_free(path_wcs);
    install_dir = g_path_get_dirname(path);
    g_free(path);
  }
  return install_dir;
}

gboolean ugtk_is_portable_mode(void) {
  static int portable = -1;
  char *local_path;

  if (portable == -1) {
    local_path =
        g_build_filename(ugtk_get_install_dir(), "uget-portable-mode", NULL);
    portable = g_file_test(local_path, G_FILE_TEST_EXISTS);
    g_free(local_path);
  }
  return portable;
}

const char *ugtk_get_data_dir(void) {
  static gchar *data_dir = NULL;

  if (data_dir == NULL)
    data_dir = g_build_filename(ugtk_get_install_dir(), "..", "share", NULL);
  return data_dir;
}

const char *ugtk_get_config_dir(void) {
  static const gchar *config_dir = NULL;

  if (config_dir == NULL) {
    if (ugtk_is_portable_mode() == TRUE)
      config_dir =
          g_build_filename(ugtk_get_install_dir(), "..", "config", NULL);
    else
      config_dir = g_get_user_config_dir();
  }
  return config_dir;
}

#else

const char *ugtk_get_data_dir(void) {
  static gchar *data_dir = NULL;

  if (data_dir == NULL) {
    // try to find data dir relative to executable (for development/portable)
    char path[4096];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1) {
      path[len] = '\0';
      gchar *dir = g_path_get_dirname(path); // executable dir
      // Build path: <exe_dir>/../../../data (assuming build format
      // build/src/ui-gtk/uget-gtk) Adjusting for standard build directory
      // structure where binary is deeply nested or just check parent
      // directories until we find 'data'

      // Let's try to assume relative path from build dir to source root
      // If running from <root>/build/src/ui-gtk/uget-gtk
      // Source data is at <root>/data

      gchar *root_check = g_build_filename(dir, "..", "..", "..", "data", NULL);
      if (g_file_test(root_check, G_FILE_TEST_IS_DIR)) {
        data_dir = root_check;
      } else {
        g_free(root_check);
        // Try another common depth or just assume installed
      }
      g_free(dir);
    }

    if (data_dir == NULL)
      data_dir = g_strdup(UG_DATADIR);
  }
  return data_dir;
}

const char *ugtk_get_config_dir(void) { return g_get_user_config_dir(); }

#endif // _WIN32 || _WIN64

const char *ugtk_get_locale_dir(void) {
  static gchar *locale_dir = NULL;

  if (locale_dir == NULL)
    locale_dir = g_build_filename(ugtk_get_data_dir(), "locale", NULL);

  return locale_dir;
}
