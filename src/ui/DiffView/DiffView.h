//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//

#ifndef DIFFVIEW_H
#define DIFFVIEW_H

#include "../FindWidget.h"
#include "editor/TextEditor.h"
#include "git/Commit.h"
#include "git/Diff.h"
#include "git/Index.h"
#include "host/Account.h"
#include "plugins/Plugin.h"
#include "app/Application.h"
#include "app/Theme.h"
#include <QMap>
#include <QScrollArea>
#include <QVBoxLayout>

class FileWidget;

namespace DiffViewStyle {
    const int kIndent = 2;
    const int kArrowWidth = 20;
    const int kArrowMargin = 6;
    const QString kHunkFmt = "<h4>%1</h4>";

    const QString kStyleSheet =
      "DiffView {"
      "  border-image: url(:/sunken.png) 4 4 4 4;"
      "  border-left-width: 4;"
      "  border-top-width: 4;"
      "  padding-left: -4;"
      "  padding-top: -4"
      "}"
      "DiffView FileWidget {"
      "  background-clip: content;"
      "  border-image: url(:/shadow.png) 8 8 8 8;"
      "  border-width: 8;"
      "  padding-left: -2;"
      "  padding-top: -2"
      "}";

    const QString kButtonStyleFmt =
      "QToolButton {"
      "  background: %1"
      "}"
      "QToolButton:pressed {"
      "  background: %2"
      "}";

    const QDir::Filters kFilters =
      QDir::Files |
      QDir::Dirs |
      QDir::Hidden |
      QDir::NoDotAndDotDot;

    const QUrl::FormattingOptions kUrlFormat =
      QUrl::PreferLocalFile |
      QUrl::StripTrailingSlash |
      QUrl::NormalizePathSegments;
}

struct Annotation
{
  QString text;
  QByteArray styles;
};

class DiffView : public QScrollArea, public EditorProvider
{
  Q_OBJECT

public:
  DiffView(const git::Repository &repo, QWidget *parent = nullptr);
  virtual ~DiffView();

  QWidget *file(int index);

  void setDiff(const git::Diff &diff);
  void setFilter(const QStringList &paths);

  const QList<PluginRef> &plugins() const { return mPlugins; }
  const Account::CommitComments &comments() const { return mComments; }

  QList<TextEditor *> editors() override;
  void ensureVisible(TextEditor *editor, int pos) override;

signals:
  void diagnosticAdded(TextEditor::DiagnosticKind kind);
  void discarded(const QString &name);

protected:
  void dropEvent(QDropEvent *event) override;
  void dragEnterEvent(QDragEnterEvent *event) override;

private:
  bool canFetchMore();
  void fetchMore(int count = 4);
  void fetchAll(int index = -1);

  git::Diff mDiff;
  QMap<QString,git::Patch> mStagedPatches;

  QList<FileWidget *> mFiles;
  QList<QMetaObject::Connection> mConnections;

  QList<PluginRef> mPlugins;
  Account::CommitComments mComments;

  QVBoxLayout* mFileWidgetLayout{nullptr};

  QList<int> mIndexes;
};

#endif
