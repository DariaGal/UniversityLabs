#include "saxparser.h"
#include <QDebug>
#include <QHeaderView>

SaxParser::SaxParser(QTreeWidget *tree)
{
    treeWidget = tree;
    currentItem = 0;
}
bool SaxParser::readFile(const QString &fileName)
{
    QStringList labels;
    labels << QObject::tr("Этапы") << QObject::tr("Имя")<< QObject::tr("Выполнено");
    treeWidget->setHeaderLabels(labels);
    treeWidget->header()->resizeSection(0, 90);
    treeWidget->header()->resizeSection(1,130);
    treeWidget->header()->resizeSection(2, 50);
    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    return reader.parse(inputSource);
}
bool SaxParser::startElement(const QString & /* namespaceURI */,
                              const QString & /* localName */,
                              const QString &qName,
                              const QXmlAttributes &attributes)
{
    if(qName == "plan")
    {
        if(currentItem)
        {
             currentItem = new QTreeWidgetItem(currentItem);
        }else {
             currentItem  = new QTreeWidgetItem(treeWidget);
        }
        if(attributes.value("number")!=0)
        {
            currentItem->setText(0, "Этап "+attributes.value("number"));
        }else
        currentItem->setText(0, "План");
}
  /* if (qName == "stage")
    {
        if(currentItem)
        {
             currentItem = new QTreeWidgetItem(currentItem);
        }else {
             currentItem  = new QTreeWidgetItem(treeWidget);
        }
        QString str;
        QTextStream (&str)<<attributes.value("number");
        currentItem->setText(0,"Этап "+str);
        currentItem = new QTreeWidgetItem(currentItem);
    }*/ else {
        currentText.clear();
    }
    return true;
}
bool SaxParser::characters(const QString &str)
{
    currentText += str;
    return true;
}
bool SaxParser::endElement(const QString & /* namespaceURI */,
                            const QString & /* localName */,
                            const QString &qName)
{
    if (qName == "plan") {
        currentItem = currentItem->parent();
    }
  /*  if (qName == "stage") {
        currentItem = currentItem->parent();
        currentItem = currentItem->parent();

    }*/
    if (qName == "name")
    {
        currentItem->setTextAlignment(1, Qt::AlignHCenter | Qt::AlignVCenter);
        currentItem->setText(1, currentText);
    }
    /*if (qName == "days")
    {
        currentItem->setText(2, currentText);
    }*/
    if (qName == "done")
    {
        currentItem->setFlags(currentItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        if(currentText=="да")
        currentItem->setCheckState(2,Qt::Checked);
        else
            currentItem->setCheckState(2,Qt::Unchecked);
      //  currentItem->setText(2, currentText);
    }
    return true;
}
bool SaxParser::fatalError(const QXmlParseException &exception)
{
    qDebug() << "Parse error at line " << exception.lineNumber()
              << ", " << "column " << exception.columnNumber() << ": "
              << qPrintable(exception.message());
    return false;
}
