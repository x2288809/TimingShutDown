#include "ConfigXML.h"

ConfigXML::ConfigXML(QWidget *parent) : QMainWindow(parent)
{

}

void ConfigXML::updateConfigXML(QString time, int dateBoxArg,int automatic, QString date)
{
    qDebug() << "定时时间：" << time;
    qDebug() << "定时日期：" << date;
    qDebug() << "是否设置日期：" << dateBoxArg;
    qDebug() << "是否自动启动：" << automatic;
    QFile file("Config.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"错误","更新XML，文件打开失败1");
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))//从字节数组中解析XML文档，并将其设置为文档的内容
    {
        file.close();
        qDebug() << "异常关闭";
        return;
    }
    file.close();

    QDomElement Root = doc.documentElement();//获得根节点元素
    QDomNodeList Timing = Root.elementsByTagName("Timing");
    QDomNodeList Date = Root.elementsByTagName("Date");
    QDomNodeList Time = Root.elementsByTagName("Time");
    //找到 ID = 1 的那个元素，再对这个元素所在位置[i]的其他属性和元素进行操作
    for(int i=0;i<Timing.count();i++)
    {
        QDomElement e = Timing.at(i).toElement();
        if(!e.isNull())
        {
            if(e.attribute("id")=="1")
            {
                Time.at(i).firstChild().setNodeValue(time);
                Date.at(i).firstChild().setNodeValue(date);
                qDebug() << "更新节点值";
                e.setAttribute("dateBoxArg",dateBoxArg);//设置ID = 1所在节点元素的dateBoxArg值
                e.setAttribute("automatic",automatic);//设置ID = 1所在节点元素的automatic值
    //            root.removeChild(list.at(i));//删除某个节点
            }
        }
    }

    if(!file.open(QFile::WriteOnly|QFile::Truncate))//重写文件，如果不用truncate就是在后面追加内容，就无效了
    {
        QMessageBox::warning(this,"错误","更新XML内容，文件打开失败2");
        return;
    }
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();

}
