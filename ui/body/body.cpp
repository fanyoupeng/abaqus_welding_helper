#include "body.h"
#include <QDebug>

body::body(QWidget *parent) : QWidget(parent){
    step_type=THERMAL;
    vboxLayout=new QVBoxLayout();
    this->setLayout(vboxLayout);
    uiInit();
}

body::~body(){

}

void body::uiInit(){
    //1、建模
    drawBigTitle(QString("1、建模"));
    if(step_type==THERMAL){
        lbs.push_back(new QLabel());
        vboxLayout->addWidget(lbs.last());
        lbs.last()->setMinimumSize(QSize(370, 220));
        lbs.last()->setMaximumSize(QSize(370, 220));
        lbs.last()->setStyleSheet(QStringLiteral("background-image: url(:/image/part.JPG);"));

        drawLine("焊件长度a","mm");
        drawLine("焊缝宽度b","mm");
        drawLine("焊件厚度c","mm");
        drawLine("焊件宽度d","mm");
        drawLine("网格大小","mm");
    }
    else{

    }

    //2、属性
    drawBigTitle(QString("2、属性"));

    if(step_type==THERMAL){
        drawLine("密度","t/m3");

        drawSmallTitle("热导率");

        const QString str3[]={
            "温度","热导率"
        };
        const QString str4[]={
            "20.0","35.0",
            "100.0","34.0",
            "500.0","32.0",
            "1300.0","35.0",
            "1350.0","70.0",
            "2000.0","70.0"
        };
        drawTable_A("mate",6,2,str3,str4);

        drawSmallTitle("潜热");

        const QString str5[]={
            "液相线温度","固相线温度","潜热"
        };
        const QString str6[]={
            "1400","1350","220e6"
        };
        drawTable_A("late",1,3,str5,str6);

        drawSmallTitle("比热");

        const QString str7[]={
            "温度","比热"
        };
        const QString str8[]={
            "20","460e6",
            "50","478e6",
            "100","500e6"
        };
        drawTable_A("spec",3,2,str7,str8);
    }
    else{
        drawLine("线膨胀系数","");

        drawSmallTitle("弹性");
        const QString str1[]={
            "杨氏模量","泊松比"
        };
        const QString str2[]={
            "200000.0","0.29",
        };
        drawTable_A("elas",1,2,str1,str2);

        drawSmallTitle("塑性");
        const QString str3[]={
            "屈服应力","塑性应变","温度",
        };
        const QString str4[]={
            "230.0", "0.0", "20.0",
            "235.0", "0.002", "20.0",
            "250.0", "0.1", "20.0",
            "180.0", "0.0", "600.0",
            "185.0", "0.002", "600.0",
            "190.0", "0.1", "600.0",
            "30.0", "0.0", "1000.0",
            "32.0", "0.002", "1000.0",
            "34.0", "0.1", "1000.0"
        };
        drawTable_A("plas",9,3,str3,str4);
    }

    //3、分析步
    drawBigTitle(QString("3、分析步"));
    if(step_type==THERMAL){


        drawSmallTitle("焊接分析步");

        const QString str9[]={
            "焊接时间","分析步最大步数","增量初始值","增量最大值","增量最小值","每步最大温度变化","每步最大变化率"
        };
        const QString str10[]={
            "12.5","10000","0.05","0.005","5","60","0.1"
        };
        drawTable_B("step_weld",7,2,str9,str10);

        drawSmallTitle("冷却分析步");

        const QString str11[]={
            "冷却时间","分析步最大步数","增量初始值","增量最大值","增量最小值","每步最大温度变化","每步最大变化率"
        };
        const QString str12[]={
            "600.0","1000","0.01","0.001","6","60","0.1"
        };
        drawTable_B("step_cold",7,2,str11,str12);
    }
    else{
        drawSmallTitle("焊接分析步");

        const QString str1[]={
            "焊接时间","分析步最大步数","增量初始值","增量最大值","增量最小值"
        };
        const QString str2[]={
            "12.5","1000","0.01","0.0001","0.1"
        };
        drawTable_B("step_weld",5,2,str1,str2);

        drawSmallTitle("冷却分析步");

        const QString str3[]={
            "冷却时间","分析步最大步数","增量初始值","增量最大值","增量最小值"
        };
        const QString str4[]={
            "600.0","10000","0.01","0.001","6"
        };
        drawTable_B("step_cold",5,2,str3,str4);
    }

    //4、交互
    drawBigTitle(QString("4、交互"));
    if(step_type==THERMAL){
        drawLine("环境温度","℃");

        drawSmallTitle("换热系数");

        const QString str14[]={
            "温度","比热"
        };
        const QString str15[]={
            "20","0.006",
            "100","0.01",
            "300","0.03",
            "2000","0.3"
        };
        drawTable_A("inte",4,2,str14,str15);
    }
    else{

    }

    //5、加载
    drawBigTitle(QString("5、加载"));
    if(step_type==THERMAL){
        drawLine("焊件初始温度","℃");

        drawFile("load","热源子程序路径","/welding");
    }
    else{
        drawSmallTitle("温度数据文件");
        drawFile("loadTemp","obd路径","/obd");

        drawSmallTitle("焊接过程");
        const QString str1[]={
            "起始分析步","起始增量","结束分析步","结束增量"
        };
        const QString str2[]={
            "1","1","1","949"
        };
        drawTable_B("step_cold",4,2,str1,str2);

        drawSmallTitle("冷却过程");
        const QString str3[]={
            "起始分析步","起始增量","结束分析步","结束增量"
        };
        const QString str4[]={
            "2","1","2","600"
        };
        drawTable_B("step_cold",4,2,str3,str4);
    }

    //弹簧
    sps.push_back(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    vboxLayout->addItem(sps.last());
}

void body::stepChange(){
    //删除已有控件
    for(int i=0;i<tbs.size();i++){
        this->layout()->removeWidget(tbs.at(i));
        delete tbs.at(i);
    }
    tbs.clear();
    for(int i=0;i<les.size();i++){
        this->layout()->removeWidget(les.at(i));
        delete les.at(i);
    }
    les.clear();
    for(int i=0;i<tws.size();i++){
        this->layout()->removeWidget(tws.at(i));
        delete tws.at(i);
    }
    tws.clear();
    for(int i=0;i<lbs.size();i++){
        this->layout()->removeWidget(lbs.at(i));
        delete lbs.at(i);
    }
    lbs.clear();
    for(int i=0;i<sps.size();i++){
        this->layout()->removeItem(sps.at(i));
        delete sps.at(i);
    }
    sps.clear();
    for(int i=0;i<wds.size();i++){
        this->layout()->removeWidget(wds.at(i));
        delete wds.at(i);
    }
    wds.clear();
    if(step_type==THERMAL)
        step_type=DEFORMATION;
    else
        step_type=THERMAL;
    uiInit();
}

void body::drawSmallTitle(QString str){
    lbs.push_back(new QLabel());
    vboxLayout->addWidget(lbs.last());

    lbs.last()->setText(str);
    lbs.last()->setObjectName(str);
    lbs.last()->setProperty("type", "title_small");
}

void body::drawBigTitle(QString str){
    lbs.push_back(new QLabel());
    vboxLayout->addWidget(lbs.last());
    lbs.last()->setMinimumSize(QSize(370, 40));
    lbs.last()->setMaximumSize(QSize(370, 40));

    lbs.last()->setText(str);
    lbs.last()->setObjectName(str);
    lbs.last()->setAlignment(Qt::AlignCenter);
    lbs.last()->setProperty("type", "title_big");
}

void body::drawLine(QString str1,QString str2){
    wds.push_back(new QWidget());
    wds.last()->setMinimumSize(QSize(370, 30));
    wds.last()->setMaximumSize(QSize(370, 30));

    vboxLayout->addWidget(wds.last());

    QLabel * lb1=new QLabel(wds.last());
    lb1->setGeometry(QRect(10, 0,100, 30));
    lb1->setText(str1);

    QLineEdit * le=new QLineEdit(wds.last());
    le->setGeometry(QRect(150, 0,100, 30));

    QLabel * lb2=new QLabel(wds.last());
    lb2->setGeometry(QRect(270, 0,100, 30));
    lb2->setText(str2);
}

void body::drawTable_A(QString name,int row,int col,const QString header[],const QString str[]){
    tws.push_back(new QTableWidget());
    vboxLayout->addWidget(tws.last());
    tws.last()->setMinimumSize(QSize(370, 120));
    tws.last()->setMaximumSize(QSize(370, 120));
    tws.last()->setObjectName(name);
    tws.last()->setRowCount(row+1);    //设置行数
    tws.last()->setColumnCount(col); //设置列数
    //隐藏表头和行号
    tws.last()->verticalHeader()->setHidden(true);
    tws.last()->horizontalHeader()->setHidden(true);
    for(int i=0;i<col;i++){
        tws.last()->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        //填写表头
        QTableWidgetItem *item = new QTableWidgetItem();//一格
        item->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
        item->setText(header[i]);
        tws.last()->setItem(0,i,item);
         //填写内容
        for(int j=0;j<row;j++){
             tws.last()->setItem(j+1,i,new QTableWidgetItem(str[j*col+i])); //设置表格内容
        }
    }

    wds.push_back(new QWidget());
    wds.last()->setMinimumSize(QSize(370, 30));
    wds.last()->setMaximumSize(QSize(370, 30));
    vboxLayout->addWidget(wds.last());

    QToolButton *tb1=new QToolButton(wds.last());
    tb1->setGeometry(QRect(95, 0,30, 30));
    tb1->setObjectName(name+"Add");
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/image/add.png"), QSize(), QIcon::Normal, QIcon::Off);
    tb1->setIcon(icon1);
    connect(tb1,SIGNAL(clicked(bool)),this,SLOT(btAdd()));

    QToolButton *tb2=new QToolButton(wds.last());
    tb2->setGeometry(QRect(295, 0,30, 30));
    tb2->setObjectName(name+"Sub");
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/image/sub.png"), QSize(), QIcon::Normal, QIcon::Off);
    tb2->setIcon(icon2);
    connect(tb2,SIGNAL(clicked(bool)),this,SLOT(btSub()));
}


void body::drawTable_B(QString name,int row,int col,const QString header[],const QString str[]){
    tws.push_back(new QTableWidget());
    vboxLayout->addWidget(tws.last());
    tws.last()->setMinimumSize(QSize(370, 120));
    tws.last()->setMaximumSize(QSize(370, 120));
    tws.last()->setObjectName(name);
    tws.last()->setRowCount(row);    //设置行数
    tws.last()->setColumnCount(col); //设置列数
    //隐藏表头和行号
    tws.last()->verticalHeader()->setHidden(true);
    tws.last()->horizontalHeader()->setHidden(true);
    for(int i=0;i<col;i++){
        tws.last()->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        //填写内容
        for(int j=0;j<row;j++){
            if(i==0){
                //填写表头
                QTableWidgetItem *item = new QTableWidgetItem();//一格
                item->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
                item->setText(header[j]);
                tws.last()->setItem(j,0,item);
            }
            else
                tws.last()->setItem(j,i,new QTableWidgetItem(str[(i-1)*row+j])); //设置表格内容
        }
    }
}

/*
 * function:文件控件
 * name:控件名
 * str:标题
 * initPath:默认路径（相对程序）
 */
void body::drawFile(QString name,QString str,QString initPath){
    wds.push_back(new QWidget());
    wds.last()->setMinimumSize(QSize(370, 30));
    wds.last()->setMaximumSize(QSize(370, 30));
    vboxLayout->addWidget(wds.last());
    lbs.push_back(new QLabel(wds.last()));
    lbs.last()->setGeometry(QRect(10, 0,100, 30));
    lbs.last()->setText(str);

    QLineEdit *le=new QLineEdit(wds.last());
    le->setObjectName(name+"le");
    le->setGeometry(QRect(100, 0,150, 30));
    QString path=QCoreApplication::applicationDirPath();//获取程序路径
    le->setText(path.append(initPath));

    QToolButton *tb=new QToolButton(wds.last());
    tb->setGeometry(QRect(270, 0,30, 30));
    tb->setObjectName(name+"bt");
    QIcon icon;
    icon.addFile(QStringLiteral(":/image/file.png"), QSize(), QIcon::Normal, QIcon::Off);
    tb->setIcon(icon);
    connect(tb,SIGNAL(clicked(bool)),this,SLOT(fileBt()));
}

void body::btAdd(){
    QToolButton *b = (QToolButton *)sender();
    QString name =b->objectName();
    name.resize(name.size()-3);
    QTableWidget * tw=this->findChild<QTableWidget *>(name);
    int count;
    count=tw->rowCount();
    tw->insertRow(count);

}

void body::btSub(){
    QToolButton *b = (QToolButton *)sender();
    QString name =b->objectName();
    name.resize(name.size()-3);
    QTableWidget * tw=this->findChild<QTableWidget *>(name);
    int count;
    count=tw->rowCount();
    if(count>=2){
        tw->removeRow(count-1);
    }
}

void body::fileBt(){
    QToolButton *b = (QToolButton *)sender();
    QString name =b->objectName();
    name.resize(name.size()-2);
    QLineEdit * le=this->findChild<QLineEdit *>(name+"le");
    QFileDialog fileDialog;
    //定义文件对话框标题
    fileDialog.setWindowTitle(QStringLiteral("选择热源子程序"));
    //设置默认文件路径
    QString path=QCoreApplication::applicationDirPath();//获取程序路径
    fileDialog.setDirectory(path);
    //设置文件过滤器
    //fileDialog.setNameFilter(tr("File(*.for)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog.setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }
    if(fileNames.size())//选择了文件
        le->setText(fileNames.at(0));
}
