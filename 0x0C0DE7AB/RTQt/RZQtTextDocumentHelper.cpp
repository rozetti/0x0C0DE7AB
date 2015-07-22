#include "RZQtTextDocumentHelper.h"

#include <QTextBlock>
#include <QTextDocument>

namespace rz
{
std::pair<int, int> RZQTextDocumentHelper::getVisibleBlockNumbers(QTextDocument *doc)
{
    int first = 0;

    QTextBlock block=doc->begin();
    for(; block!= doc->end(); block = block.next())
    {
        if (block.isVisible())
        {
            break;
        }
        ++first;
    }

    int last = first;
    for(; block!= doc->end(); block = block.next())
    {
        if (!block.isVisible())
        {
            break;
        }
        ++last;
    }

    return std::make_pair(first, last);
}

}
