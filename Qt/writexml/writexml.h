#ifndef WRITEXML_H
#define WRITEXML_H
#include <QTreeWidget>
#include <QXmlStreamWriter>
#include <QFile>
class WriteXml
{
public:
    WriteXml(QTreeWidget *tree);
    bool writeXml(const QString &fileName);
private:
    QTreeWidget *treeWidget;
    void writeIndexEntry(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item);
};

#endif // WRITEXML_H
