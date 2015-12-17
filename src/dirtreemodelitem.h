/*
 * Copyright (C) 2014 - 2015  Hong Jen Yee (PCMan) <pcman.tw@gmail.com>
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

#ifndef FM_DIRTREEMODELITEM_H
#define FM_DIRTREEMODELITEM_H

#include "libfmqtglobals.h"
#include <libfm/fm.h>
#include <QIcon>
#include <QList>
#include <QModelIndex>

namespace Fm {

class DirTreeModel;
class DirTreeView;

class LIBFM_QT_API DirTreeModelItem {
public:
  friend class DirTreeModel; // allow direct access of private members in DirTreeModel
  friend class DirTreeView; // allow direct access of private members in DirTreeView

  explicit DirTreeModelItem();
  explicit DirTreeModelItem(FmFileInfo* info, DirTreeModel* model, DirTreeModelItem* parent = nullptr);
  ~DirTreeModelItem();

  void loadFolder();
  void unloadFolder();

  inline bool isPlaceHolder() const {
    return (fileInfo_ == nullptr);
  }

  void setShowHidden(bool show);

private:
  void freeFolder();
  void addPlaceHolderChild();
  DirTreeModelItem* childFromName(const char* utf8_name, int* pos);
  DirTreeModelItem* childFromPath(FmPath* path, bool recursive) const;

  DirTreeModelItem* insertFileInfo(FmFileInfo* fi);
  int insertItem(Fm::DirTreeModelItem* newItem);
  QModelIndex index();

  static void onFolderFinishLoading(FmFolder* folder, gpointer user_data);
  static void onFolderFilesAdded(FmFolder* folder, GSList* files, gpointer user_data);
  static void onFolderFilesRemoved(FmFolder* folder, GSList* files, gpointer user_data);
  static void onFolderFilesChanged(FmFolder* folder, GSList* files, gpointer user_data);

private:
  FmFileInfo* fileInfo_;
  FmFolder* folder_;
  QString displayName_ ;
  QIcon icon_;
  bool expanded_;
  bool loaded_;
  DirTreeModelItem* parent_;
  DirTreeModelItem* placeHolderChild_;
  QList<DirTreeModelItem*> children_;
  QList<DirTreeModelItem*> hiddenChildren_;
  DirTreeModel* model_;
};

}

#endif // FM_DIRTREEMODELITEM_H
