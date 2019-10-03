#include "writexml.h"
#include <QDebug>
WriteXml::WriteXml(QTreeWidget *tree)
{
    treeWidget = tree;
}
bool WriteXml::writeXml(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString());
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("plan");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
        writeIndexEntry(&xmlWriter, treeWidget->topLevelItem(i));
    xmlWriter.writeEndDocument();
    file.close();
    if (file.error()) {
        qDebug() << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString());
        return false;
    }
    return true;
}
void WriteXml::writeIndexEntry(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item)
{
    QString stepNum=item->text(0);
    qDebug()<<stepNum;
    if(stepNum!="План")
    {
    QStringList num = stepNum.split(" ");
    xmlWriter->writeStartElement("plan");

    xmlWriter->writeAttribute("number", num.value(1));
    xmlWriter->writeTextElement("name", item->text(1));
    if(item->checkState(2)==Qt::Checked)
    {
        xmlWriter->writeTextElement("done", "да");
    }
    else xmlWriter->writeTextElement("done", "нет");
    }
    for (int i = 0; i < item->childCount(); ++i)
        writeIndexEntry(xmlWriter, item->child(i));
    xmlWriter->writeEndElement();

}
