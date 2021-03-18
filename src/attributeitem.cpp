#include "attributeitem.h"

extern bool debug;

AttributeItem::AttributeItem(const QList<QVariant> &data, TreeItem *parent)
    : BranchItem(data, parent)
{
    TreeItem::setType(Attribute);
    internal = false;
    attrType = Undefined;
}

AttributeItem::~AttributeItem() {}

void AttributeItem::set(const QString &k, const QString &v, const Type &)
{
    key = k;
    value = QVariant(v);
    attrType = String;
    createHeading();
}

void AttributeItem::get(QString &k, QString &v, Type &t) // FIXME-0  really?
{
    k = key;
    v = value.toString();
    t = attrType;
}

void AttributeItem::setKey(const QString &k) // FIXME-2 Check if key aready exists in branch?
{
    key = k;
    createHeading();
}

QString AttributeItem::getKey()
{
    return key;
}

void AttributeItem::setValue(const QString &v)
{
    value = v;
    attrType = String;
    createHeading();
}

void AttributeItem::setValue(const qlonglong &n)
{
    value = n;
    attrType = Integer;
    createHeading();
}

void AttributeItem::setValue(const QDateTime &dt)
{
    value = dt;
    attrType = DateTime;
    createHeading();
}

QVariant AttributeItem::getValue()
{
    return value;
}

void AttributeItem::setAttributeType(const Type &t)
{
    attrType = t;
}

AttributeItem::Type AttributeItem::getAttributeType()
{
    return attrType;
}

QString AttributeItem::getAttributeTypeString()
{
    switch (attrType) {
        case Integer:
            return "Integer";
        case String:
            return "String";
        case DateTime:
            return "DateTime";
        case Undefined:
            return "Undefined";
        }
    }

    void AttributeItem::setInternal(bool b) { internal = b; }

    bool AttributeItem::isInternal() { return internal; }

QString AttributeItem::getDataXML()
{
    QString a;
    a = attribut("key", getKey());
    a += attribut("value", getValue().toString());
    a += attribut("type", getAttributeTypeString());
    return singleElement("attribute", a);
}

void AttributeItem::createHeading() // FIXME-3 Visible in TreeEditor, should not go to MapEditor
{
    setHeadingPlainText(
        QString("[Attr] %1: %2").arg(key).arg(value.toString()));
}
