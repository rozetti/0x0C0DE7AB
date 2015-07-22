#ifndef RZQTEXTDOCUMENTHELPER_H
#define RZQTEXTDOCUMENTHELPER_H

class QTextDocument;

#include <utility>

namespace rz
{
class RZQTextDocumentHelper
{
public:
    RZQTextDocumentHelper() = delete;

    static std::pair<int, int> getVisibleBlockNumbers(QTextDocument *doc);
};
}

#endif // RZQTEXTDOCUMENTHELPER_H
