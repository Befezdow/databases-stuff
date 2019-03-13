#ifndef BTREEITEM_H
#define BTREEITEM_H

#include "functor.h"
#include "key.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStack>
#include <QDataStream>

const int FILENAME_LENGTH = 10;
const QString FORMAT = ".b";
const QString RELATIVE_PATH = QString("dbfiles") + QDir::separator();

#ifndef MIN_NODE_SIZE
#define MIN_NODE_SIZE 500
#define MAX_NODE_SIZE (2 * MIN_NODE_SIZE)
#endif

template <typename T>
class BTreeNode
{
    QList<Key<T>> keysList;
    QStringList childsList;
    bool isLeaf;
    QString nodeFileName;

public:
    BTreeNode(bool leaf = true):
        isLeaf(leaf),
        nodeFileName("")
    {
        if (leaf)
        {
            childsList.push_back("");
        }
    }

    ///TODO Сделать фабрику
    BTreeNode(QList<Key<T>> keys, QStringList childs, bool leaf = true):
        isLeaf(leaf)
    {
        if ((keys.size() + 1) != childs.size())
        {
            throw QString("BTreeNode :: constructor : Incorrect data was received");
        }

        foreach (Key<T> key, keys)
        {
            keysList.append(key);
        }

        foreach (QString child, childs)
        {
            childsList.append(child);
        }
    }

    //File format: BTREEIsleaf21DataDataFilename
    void loadData(QString filename)
    {
        nodeFileName = filename;
        QFile file(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + filename + FORMAT);
        if (!file.open(QIODevice::ReadOnly))
        {
            throw QString("BTreeNode :: loadData : File '" + filename + FORMAT + "' can't be opened");
        }
        QDataStream stream(&file);
        char* temp;

        unsigned int bytesCount = 5;
        temp = new char[bytesCount];
        stream.readRawData(temp,bytesCount);
        if (temp[0] != 'B' || temp[1] != 'T' || temp[2] != 'R' || temp[3] != 'E' || temp[4] != 'E')
        {
            delete[] temp;
            throw QString("BTreeNode :: loadData : File '" + filename + FORMAT + "' has unknown format");
        }
        delete[] temp;
//        qDebug()<<"Format has been accepted";

        bytesCount = 1;
        temp = new char[bytesCount];
        stream.readRawData(temp,bytesCount);
        isLeaf = *((bool*)temp);
        delete[] temp;
//        qDebug()<<"Is leaf: " << isLeaf;

        bytesCount = 4;
        temp = new char[bytesCount];
        stream.readRawData(temp,bytesCount);
        int keysCount = *((int*)temp);
        if (keysCount > MAX_NODE_SIZE)
        {
            throw QString("BTreeNode :: loadData : File '" + filename + FORMAT + "' has incompatable keys count");
        }
        delete[] temp;
//        qDebug()<<"Keys count: " << keysCount;

        bytesCount = 4;
        temp = new char[bytesCount];
        stream.readRawData(temp,bytesCount);
        int childsCount = *((int*)temp);
        if (childsCount > keysCount + 1)
        {
            throw QString("BTreeNode :: loadData : File '" + filename + FORMAT + "' has incompatable childs count");
        }
        delete[] temp;
//        qDebug()<<"Childs count: " << childsCount;

        keysList.clear();
        childsList.clear();

        for (int i = 0; i < keysCount; ++i)
        {
            Key<T> element;
            stream >> element;
            keysList.append(element);
        }

//        qDebug()<<"Childs:";
        for (int i = 0; i < childsCount; ++i)
        {
            unsigned int length = FILENAME_LENGTH;
            temp = new char[length];
            stream.readRawData(temp,length);
            QString child(temp);
            child = child.trimmed();
            childsList.append(child);
            delete[] temp;
//            qDebug()<<child;
        }

        file.close();
    }

    void saveData() const
    {
        if (!QDir(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH).exists())
        {
            BTreeNode::createDir();
        }

        QFile file(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + nodeFileName + FORMAT);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            throw QString("BTreeNode :: saveData : File '" + nodeFileName + FORMAT + "' can't be opened");
        }
        QDataStream stream(&file);

        char* temp = new char[5];
        strcpy(temp,"BTREE");
        stream.writeRawData(temp,5);
        delete[] temp;
//        qDebug()<<"Format has been written";

        stream.writeRawData((char*)&isLeaf,1);
//        qDebug()<<"Is leaf: " << isLeaf;

        int keysCount = keysList.size();
        int childsCount = childsList.size();
        stream.writeRawData((char*)&keysCount,4);
        stream.writeRawData((char*)&childsCount,4);
//        qDebug()<<QString::number(keysCount) + " keys was written";
//        qDebug()<<QString::number(childsCount) + " childs was written";

        foreach (Key<T> key,keysList)
        {
            stream << key;
        }

        foreach(QString child,childsList)
        {
            QByteArray bytes = child.toLatin1();
            stream.writeRawData(bytes.data(),FILENAME_LENGTH);
//            qDebug()<<child;
        }

        file.close();
    }

    void print() const
    {
        qDebug()<<"KEYS:"<<keysList.size();
        foreach (Key<T> key, keysList)
        {
            key.value.print();
        }

        qDebug()<<"CHILDS:"<<childsList.size();
        foreach (QString child, childsList)
        {
            qDebug()<<child;
        }
    }

    static void createDir()
    {
        QDir dir(qApp->applicationDirPath());
        QStringList list = RELATIVE_PATH.split(QDir::separator());
        for (int i = 0; i < list.size(); ++i)
        {
            if (!dir.cd(list.at(i)))
            {
                dir.mkdir(list.at(i));
            }
        }
    }

    QString addElement(const unsigned int treeNumber, unsigned int& nodesCount, Functor* less, Functor* equal, Key<T> newKey, QStack<BTreeNode<T>>& chain, BTreeNode newC = BTreeNode(false))
    {
        ///TODO Заменить поиск делением на 2
        bool pushBack = true;
        for (int i = 0; i < keysList.length(); ++i)
        {
            if (newKey.lessThen(keysList.at(i), less, equal))
            {
                keysList.insert(i, newKey);
                childsList.insert(i + 1, newC.nodeFileName);
                pushBack = false;
                break;
            }
        }

        if (pushBack)
        {
            keysList.push_back(newKey);
            childsList.push_back(newC.nodeFileName);
        }

        if (keysList.length() > MAX_NODE_SIZE)
        {
            int middlePos = floor(keysList.length() / 2);
            Key<T> middleElem = keysList[middlePos];
            BTreeNode newNode(keysList.mid(middlePos + 1), childsList.mid(middlePos + 1), this->isLeaf);
            newNode.setFileName(QString::number(treeNumber) + "_" + QString::number(++nodesCount));

            while (this->keysList.length() > middlePos)
            {
                keysList.pop_back();
                childsList.pop_back();
            }

            this->saveData();
            newNode.saveData();

            if (!chain.isEmpty())
            {
                BTreeNode par = chain.pop();
                QString str = par.addElement(treeNumber, nodesCount, less, equal, middleElem, chain, newNode);
                par.saveData();
                return str;
            }
            else
            {
                BTreeNode par(false);
                par.setFileName(QString::number(treeNumber) + "_" + QString::number(++nodesCount));
                par.keysList.push_back(middleElem);
                par.childsList.push_back(this->nodeFileName);
                par.childsList.push_back(newNode.nodeFileName);
                par.saveData();
                return par.nodeFileName;
            }
        }
        this->saveData();
        return "";
    }

//    QString removeElement(Functor* lessOperation, int pos, BTreeNode& par)
//    {
//        if (pos < 0 || pos >= this->keysList.size())
//        {
//            throw QString("BTreeNode :: removeElement : index is out of range");
//        }

//        if (this->isLeaf)
//        {
//            if (par.nodeFileName.isEmpty())
//            {
//                keysList.removeAt(pos);
//                childsList.pop_back();
//                this->saveData();
//                return "";
//            }

//            if (this->keysList.size() > MIN_NODE_SIZE)
//            {
//                keysList.removeAt(pos);
//                childsList.removeAt(pos + 1);
//                this->saveData();
//            }
//            else
//            {
//                Key<T> temp = keysList.back();

//                BTreeNode leftSibling(false);
//                BTreeNode rightSibling(false);

//                ///TODO  Заменить поиск делением на 2
//                bool isLast = true;
//                int i;
//                for (i = 0; i < par.keysList.size(); ++i)
//                {
//                    if ((*lessOperation)(temp, par.keysList.at(i)))//temp < par.keysList.at(i))  ////////////////////////////
//                    {
//                        if (i == 0)
//                        {
//                            rightSibling.loadData(par.childsList.at(i + 1));
//                        }
//                        else
//                        {
//                            leftSibling.loadData(par.childsList.at(i - 1));
//                            rightSibling.loadData(par.childsList.at(i + 1));
//                        }
//                        isLast = false;
//                        break;
//                    }
//                }

//                if (isLast)
//                {
//                    leftSibling.loadData(par.childsList.at(par.childsList.size() - 2));
//                }

//                if (!leftSibling.nodeFileName.isEmpty() && leftSibling.keysList.size() > MIN_NODE_SIZE)
//                {
//                    Key<T> temp1 = leftSibling.keysList.back();
//                    leftSibling.keysList.pop_back();
//                    Key<T> temp2 = par.keysList[i - 1];
//                    par.keysList.removeAt(i - 1);
//                    par.keysList.insert(i - 1,temp1);
//                    this->keysList.removeAt(pos);
//                    this->keysList.push_front(temp2);

//                    par.saveData();
//                    this->saveData();
//                    leftSibling.saveData();
//                }
//                else if (!rightSibling.nodeFileName.isEmpty() && rightSibling.keysList.size() > MIN_NODE_SIZE)
//                {
//                    Key<T> temp1 = rightSibling.keysList.first();
//                    rightSibling.keysList.pop_front();
//                    Key<T> temp2 = par.keysList[i];
//                    par.keysList.removeAt(i);
//                    par.keysList.insert(i,temp1);
//                    this->keysList.removeAt(pos);
//                    this->keysList.push_back(temp2);

//                    par.saveData();
//                    this->saveData();
//                    rightSibling.saveData();
//                }
//                else
//                {
//                    qDebug()<<"Merge";
//                    this->keysList.removeAt(pos);

//                    if (!leftSibling.nodeFileName.isEmpty())
//                    {
//                        qDebug()<<"left - base";
//                        leftSibling.keysList.push_back(par.keysList[i - 1]);
//                        leftSibling.childsList.push_back("");
//                        par.keysList.removeAt(i - 1);
//                        par.childsList.removeAt(i);
//                        foreach (Key<T> elem, this->keysList)
//                        {
//                            leftSibling.keysList.push_back(elem);
//                            leftSibling.childsList.push_back("");
//                        }

//                        leftSibling.saveData();
//                    }
//                    else
//                    {
//                        rightSibling.keysList.push_front(par.keysList[i]);
//                        rightSibling.childsList.push_front("");
//                        par.keysList.removeAt(i);
//                        par.childsList.removeAt(i);
//                        foreach (Key<T> elem, this->keysList)
//                        {
//                            rightSibling.keysList.push_front(elem);
//                            rightSibling.childsList.push_front("");
//                        }
//                        rightSibling.saveData();
//                    }

//                    par.saveData();

//                    QFile file(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + this->nodeFileName + FORMAT);
//                    if (!file.remove())
//                    {
//                        throw QString("BTreeNode :: removeElement : File '" + this->nodeFileName + "' can't be deleted");
//                    }
//                }
//            }
//        }
//        else
//        {
//            BTreeNode left(false);
//            BTreeNode right(false);

//            left.loadData(childsList.at(pos));
//            right.loadData(childsList.at(pos + 1));

//            if (left.keysList.size() > MIN_NODE_SIZE)
//            {
//                while (!left.isLeaf)
//                {
//                    left.loadData(left.childsList.back());
//                }
//                Key<T> temp = left.keysList.back();
//                left.keysList.pop_back();
//                this->keysList.removeAt(pos);
//                this->keysList.insert(pos,temp);

//                left.saveData();
//                this->saveData();
//            }
//            else if (right.keysList.size() > MIN_NODE_SIZE)
//            {
//                while (!right.isLeaf)
//                {
//                    right.loadData(right.childsList.front());
//                }
//                Key<T> temp = right.keysList.front();
//                right.keysList.pop_front();
//                this->keysList.removeAt(pos);
//                this->keysList.insert(pos,temp);

//                right.saveData();
//                this->saveData();
//            }
//            else
//            {
//                qDebug()<<"Merge";
//                qDebug()<<left.keysList;
//                qDebug()<<right.keysList;

//                int tempIndex = left.keysList.size();

//                Key<T> value = this->keysList[pos];
//                this->keysList.removeAt(pos);
//                this->childsList.removeAt(pos + 1);
//                left.keysList.push_back(value);
//                int i;
//                for (i = 0; i < right.keysList.size(); ++i)
//                {
//                    left.keysList.push_back(right.keysList[i]);
//                    left.childsList.push_back(right.childsList[i]);
//                }
//                left.childsList.push_back(right.childsList[i]);

//                qDebug()<<left.keysList;
//                qDebug()<<right.keysList;

//                this->saveData();

//                left.removeElement(lessOperation,tempIndex,*this);

//                QFile file(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + right.nodeFileName + FORMAT);
//                if (!file.remove())
//                {
//                    throw QString("BTreeNode :: removeElement : File '" + right.nodeFileName + "' can't be deleted");
//                }

//                if (this->keysList.isEmpty())
//                {
//                    QFile file(qApp->applicationDirPath() + QDir::separator() + RELATIVE_PATH + this->nodeFileName + FORMAT);
//                    if (!file.remove())
//                    {
//                        throw QString("BTreeNode :: removeElement : File '" + this->nodeFileName + "' can't be deleted");
//                    }

//                    return left.nodeFileName;
//                }
//            }
//        }

//        return "";
//    }

    void setFileName(QString name)
    {
        nodeFileName = name;
    }

    const QList<Key<T>>& getKeys() const
    {
        return keysList;
    }

    const QStringList& getChilds() const
    {
        return childsList;
    }

    bool getIsLeaf() const
    {
        return isLeaf;
    }

    QString getNodeFileName() const
    {
        return nodeFileName;
    }
};

#endif // BTREEITEM_H
