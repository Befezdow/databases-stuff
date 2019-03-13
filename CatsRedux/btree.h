#ifndef BTREE_H
#define BTREE_H

#include <QObject>
#include <QDebug>
#include "btreenode.h"
#include "functor.h"

template <typename T>
class BTree : public QObject
{
    QString root;
    QString infoFileName;                                   //файл с информацией о бд, здесь содержится имя корневого файла и кол-во нод в бд, ее степень
    unsigned long elementsCount;

    const unsigned int treeNumber;
    unsigned int nodesCount;
    static unsigned int treesCount;

    Functor* less;
    Functor* equal;
    Functor* startsWith;

    QList<T> getAllSubTreeElements(QString fileName)
    {
        QList<T> result;

        BTreeNode<T> node(true);
        node.loadData(fileName);

        QList<Key<T>> keys = node.getKeys();
        QStringList childs = node.getChilds();

        for (int i = 0; i < keys.size(); ++i)
        {
            if (!node.getIsLeaf())
            {
                QList<T> t = getAllSubTreeElements(childs.at(i));
                foreach(T val, t)
                {
                    result.append(val);
                }
            }

            result.append(keys.at(i).value);
        }

        if (!node.getIsLeaf())
        {
            QList<T> t = getAllSubTreeElements(childs.last());
            foreach(T val, t)
            {
                result.append(val);
            }
        }
        return result;
    }

    void print(QString fileName)
    {
        BTreeNode<T> node(true);
        node.loadData(fileName);

        node.print();

        foreach (QString child, node.getChilds())
        {
            if (!child.isEmpty())
            {
                print(child);
            }
        }
    }

    QList<T> getEqualSubTreeElement(QString fileName, T value)
    {
        QList<T> result;

        BTreeNode<T> node(true);
        node.loadData(fileName);

        QList<Key<T>> keys = node.getKeys();
        QStringList childs = node.getChilds();

        bool goIntoLast = true;

        for (int i = 0; i < keys.size(); ++i)
        {
            if ((*less)(value, keys.at(i).value))
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getEqualSubTreeElement(childs.at(i), value);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                goIntoLast = false;
                break;
            }
            else if ((*less)(keys.at(i).value, value))
            {
                continue;
            }
            else
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getEqualSubTreeElement(childs.at(i), value);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                result.push_back(keys.at(i).value);
            }
        }

        if (goIntoLast && !node.getIsLeaf())
        {
            QList<T> t = getEqualSubTreeElement(childs.last(), value);
            foreach(T val, t)
            {
                result.push_back(val);
            }
        }

        return result;
    }

    QList<T> getInRangeSubTreeElement(QString fileName, T firstValue, T secondValue)
    {
        QList<T> result;

        BTreeNode<T> node(true);
        node.loadData(fileName);

        QList<Key<T>> keys = node.getKeys();
        QStringList childs = node.getChilds();

        bool goIntoLast = true;

        for (int i = 0; i < keys.size(); ++i)
        {
            if ((*less)(secondValue, keys.at(i).value))
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getInRangeSubTreeElement(childs.at(i), firstValue, secondValue);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                goIntoLast = false;
                break;
            }
            else if ((*less)(keys.at(i).value, firstValue))
            {
                continue;
            }
            else
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getInRangeSubTreeElement(childs.at(i), firstValue, secondValue);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                result.push_back(keys.at(i).value);
            }
        }

        if (goIntoLast && !node.getIsLeaf())
        {
            QList<T> t = getInRangeSubTreeElement(childs.last(), firstValue, secondValue);
            foreach(T val, t)
            {
                result.push_back(val);
            }
        }

        return result;
    }

    QList<T> getStartsWithSubTreeElements(QString fileName, T value)
    {
        QList<T> result;

        BTreeNode<T> node(true);
        node.loadData(fileName);

        QList<Key<T>> keys = node.getKeys();
        QStringList childs = node.getChilds();

        bool goIntoLast = true;

        for (int i = 0; i < keys.size(); ++i)
        {
            if ((*less)(value, keys.at(i).value))
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getStartsWithSubTreeElements(childs.at(i), value);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                if ((*startsWith)(keys.at(i).value, value))
                {
                    result.push_back(keys.at(i).value);
                }
                else
                {
                    goIntoLast = false;
                    break;
                }
            }
            else if ((*less)(keys.at(i).value, value))
            {
                continue;
            }
            else
            {
                if (!node.getIsLeaf())
                {
                    QList<T> t = getEqualSubTreeElement(childs.at(i), value);
                    foreach(T val, t)
                    {
                        result.push_back(val);
                    }
                }

                result.push_back(keys.at(i).value);
            }
        }

        if (goIntoLast && !node.getIsLeaf())
        {
            QList<T> t = getStartsWithSubTreeElements (childs.last(), value);
            foreach(T val, t)
            {
                result.push_back(val);
            }
        }

        return result;
    }

    void updateInfoFile()
    {
        if (!QDir(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH).exists())
        {
            BTreeNode<T>::createDir();
        }

        QFile file (qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + infoFileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            throw QString("BTree :: updateInfoFile : Info file not found and can't be created");
        }

        QDataStream stream(&file);

        QByteArray bytes = root.toLatin1();
        stream.writeBytes(bytes.data(), FILENAME_LENGTH);
        stream.writeBytes((char*)&elementsCount, sizeof(unsigned long));
        stream.writeBytes((char*)&nodesCount, 4);
//        unsigned short temporary = MIN_NODE_SIZE;
//        stream.writeBytes((char*)&temporary, 2);

        file.close();
    }

public:
    BTree(QString infoFile, QObject *parent = Q_NULLPTR) : QObject(parent),
        infoFileName(infoFile),
        treeNumber(treesCount++),
        nodesCount(0)
    {
        QFile file (qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + infoFileName);
        if (file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"Info file has been founded";
            QDataStream stream(&file);
            char* temp;

            unsigned int bytesCount = FILENAME_LENGTH;
            stream.readBytes(temp, bytesCount);
            QString rootName(temp);
            root = rootName.trimmed();
            delete[] temp;

            bytesCount = 8;
            stream.readBytes(temp, bytesCount);
            elementsCount = *((unsigned long*)temp);
            delete[] temp;

            bytesCount = 4;
            stream.readBytes(temp, bytesCount);
            nodesCount = *((unsigned int*)temp);
            delete[] temp;

//            bytesCount = 2;
//            stream.readBytes(temp, bytesCount);
//            MIN_NODE_SIZE = *((unsigned short*)temp);
//            MAX_NODE_SIZE = 2 * MIN_NODE_SIZE;
//            delete[] temp;
        }
        else
        {
            qDebug()<<"Info file hasn't been founded";
            root = QString::number(treeNumber) + "_0";
            elementsCount = 0;

            updateInfoFile();
            qDebug()<<"Info file has been created";

            BTreeNode<T> node;
            node.setFileName(root);
            node.saveData();
            qDebug()<<"First node has been created";
        }
    }

    QList<T> getAll()
    {
        return getAllSubTreeElements(root);
    }

    QList<T> getEqual(T value)
    {
        return getEqualSubTreeElement(root, value);
    }

    QList<T> getInRange(T firstValue, T secondValue)
    {
        if ((*less)(secondValue, firstValue))
        {
            return QList<T>();
        }
        else
        {
            return getInRangeSubTreeElement(root, firstValue, secondValue);
        }
    }

    QList<T> getStartsWith(T value)
    {
        return getStartsWithSubTreeElements(root, value);
    }

    void printTree()
    {
        print(root);
    }

//    QPair<QStack<BTreeNode<T>>,int> findElement(T element)
//    {
//        BTreeNode<T> node(false);
//        node.loadData(root);
//        QStack<BTreeNode<T>> stack;
//        while(true)
//        {
//            stack.push(node);

//            bool goIntoLast = true;
//            QList<T> keys = node.getKeys();
//            QStringList childs = node.getChilds();
//            for (int i = 0; i < keys.size(); ++i)
//            {
//                if ((*lessOrEqual)(element, keys.at(i)))//element <= keys.at(i))              ///////////////////////
//                {
//                    if ((*equal)(keys.at(i), element))//keys.at(i) == element)          ///////////////////////
//                    {
//                        return QPair<QStack<BTreeNode<T>>,int> (stack, i);
//                    }
//                    else
//                    {
//                        if (node.getIsLeaf())
//                        {
//                            return QPair<QStack<BTreeNode<T>>,int> (stack, -1);
//                        }
//                        else
//                        {
//                            node.loadData(childs[i]);
//                            goIntoLast = false;
//                            break;
//                        }
//                    }
//                }
//            }

//            if (goIntoLast)
//            {
//                if (node.getIsLeaf())
//                {
//                    return QPair<QStack<BTreeNode<T>>,int> (stack, -1);
//                }
//                else
//                {
//                    node.loadData(childs.back());
//                }
//            }
//        }
//    }

    void addElement(T element)
    {
        BTreeNode<T> node(false);
        node.loadData(root);

        QStack<BTreeNode<T>> stack;

        Key<T> k(elementsCount++,element);

        while (true)
        {
            if (node.getIsLeaf())
            {
                QString str = node.addElement(treeNumber, nodesCount, less, equal, k, stack);

                if (!str.isEmpty())
                {
                    root = str;
                }
                break;
            }

            stack.push(node);

            QList<Key<T>> keys = node.getKeys();
            QStringList childs = node.getChilds();

            bool goIntoLast = true;
            for (int i = 0; i < keys.length(); ++i)
            {
                Key<T> temp = keys.at(i);

                if (k.lessThen(temp, less, equal))
                {
                    goIntoLast = false;
                    node.loadData(childs.at(i));
                    break;
                }
            }
            if (goIntoLast)
            {
                node.loadData(childs.back());
            }
        }

        updateInfoFile();
    }

//    bool removeElement(T element)
//    {
//        BTreeNode<T> node(false);
//        node.loadData(root);
//        BTreeNode<T> par(false);

//        while(true)
//        {
//            bool goIntoLast = true;
//            QList<T> keys = node.getKeys();
//            QStringList childs = node.getChilds();
//            for (int i = 0; i < keys.size(); ++i)
//            {
//                if ((*lessOrEqual)(element, keys.at(i)))//element <= keys.at(i))              //////////////////////////
//                {
//                    if ((*equal)(keys.at(i), element))//keys.at(i) == element)          /////////////////////////
//                    {
//                        qDebug()<<"The element lies in the"<<node.getNodeFileName()<<"node";
//                        QString str = node.removeElement(less, i, par);
//                        if (!str.isEmpty())
//                        {
//                            root = str;
//                            updateInfoFile();
//                        }
//                        return true;
//                    }
//                    else
//                    {
//                        if (node.getIsLeaf())
//                        {
//                            return false;
//                        }
//                        else
//                        {
//                            par = node;
//                            node.loadData(childs[i]);
//                            goIntoLast = false;
//                            break;
//                        }
//                    }
//                }
//            }

//            if (goIntoLast)
//            {
//                if (node.getIsLeaf())
//                {
//                    return false;
//                }
//                else
//                {
//                    par = node;
//                    node.loadData(childs.back());
//                }
//            }
//        }
//    }

    void setFunctors(Functor* less, Functor* equal, Functor* startsWith)
    {
        this->less = less;
        this->equal = equal;
        this->startsWith = startsWith;
    }
};

template <typename T>
unsigned int BTree<T>::treesCount = 0;

#endif // BTREE_H
