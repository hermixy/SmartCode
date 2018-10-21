#include "bookmarks.h"
#include <QMultiMap>
#include <tabwidget.h>

Bookmarks::Bookmarks(TabWidget * editorManager,QObject *parent) : QObject(parent)
{
  editorManager = editorManager;
}

Bookmarks::~Bookmarks()
{

}

void Bookmarks::toggleBookmark(const QString &fileName , int line, bool isToggled)
{
  if(!isToggled)
    {
      Bookmark bookmark;

      bookmark.fileName = fileName;
      bookmark.line = line;

      bookmarksList.append(bookmark);
      currentBookmark = -- bookmarksList.end();
    }
  else
    {
      if(bookmarksList.count() == 1)
        {
          bookmarksList.removeFirst();
        }
      else
        {
          QList<Bookmark>::iterator i;

          for (i = bookmarksList.begin(); i != bookmarksList.end(); ++i)
            {
              Bookmark bookmark = *i;

              if(bookmark.fileName == fileName && bookmark.line == line)
                {
                  if(i == --bookmarksList.end())
                    {
                      bookmarksList.erase(i);
                      currentBookmark = i - 1;
                    }
                  else
                    currentBookmark = bookmarksList.erase(i);
                }
            }
        }
    }
}

void Bookmarks::nextBookmark()
{
  prevNextBookmar(true);
}

void Bookmarks::prevBookmark()
{
  prevNextBookmar(false);
}

void Bookmarks::prevNextBookmar(bool next)
{
  if(next)
    {
      if(currentBookmark != bookmarksList.constEnd() - 1)
        currentBookmark += 1;
      else
        return;
    }
  else
    {
      if(currentBookmark != bookmarksList.constBegin())
        currentBookmark -= 1;
      else
        return;
    }

  Bookmark bookmark = *currentBookmark;

  _editorManager->openFileAt(bookmark.fileName,bookmark.line,0);
}

