/*
 * Copyright (C) 2013 - 2015  Hong Jen Yee (PCMan) <pcman.tw@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef FM_SIDEPANE_H
#define FM_SIDEPANE_H

#include "libfmqtglobals.h"
#include <libfm/fm.h>
#include <QWidget>

class QComboBox;
class QVBoxLayout;
class QWidget;

namespace Fm {

class FileMenu;

class LIBFM_QT_API SidePane : public QWidget {
  Q_OBJECT

public:
  enum Mode {
      ModeNone = -1,
      ModePlaces = 0,
      ModeDirTree,
      NumModes
  };

public:
  explicit SidePane(QWidget* parent = 0);
  virtual ~SidePane();

  QSize iconSize() {
    return iconSize_;
  }

  void setIconSize(QSize size);

  FmPath* currentPath() {
    return currentPath_;
  }

  void setCurrentPath(FmPath* path);

  void setMode(Mode mode);

  Mode mode() {
    return mode_;
  }

  QWidget* view() {
    return view_;
  }

  const char *modeName(Mode mode);

  Mode modeByName(const char *str);

#if 0 // FIXME: are these APIs from libfm-qt needed?
  int modeCount(void) {
    return NumModes;
  }

  QString modeLabel(Mode mode);

  QString modeTooltip(Mode mode);
#endif

  void setShowHidden(bool show_hidden);

  bool showHidden() {
    return showHidden_;
  }

  bool setHomeDir(const char *home_dir);

  // libfm-gtk compatible alias
  FmPath* getCwd() {
    return currentPath();
  }

  void chdir(FmPath* path) {
    setCurrentPath(path);
  }

Q_SIGNALS:
  void chdirRequested(int type, FmPath* path);
  void openFolderInNewWindowRequested(FmPath* path);
  void openFolderInNewTabRequested(FmPath* path);
  void openFolderInTerminalRequested(FmPath* path);
  void createNewFolderRequested(FmPath* path);
  void modeChanged(Fm::SidePane::Mode mode);

  void prepareFileMenu(Fm::FileMenu* menu); // emit before showing a Fm::FileMenu

protected Q_SLOTS:
  void onPlacesViewChdirRequested(int type, FmPath* path);
  void onDirTreeViewChdirRequested(int type, FmPath* path);
  void onComboCurrentIndexChanged(int current);

private:
  void initDirTree();

private:
  FmPath* currentPath_;
  QWidget* view_;
  QComboBox* combo_;
  QVBoxLayout* verticalLayout;
  QSize iconSize_;
  Mode mode_;
  bool showHidden_;
};

}

#endif // FM_SIDEPANE_H
