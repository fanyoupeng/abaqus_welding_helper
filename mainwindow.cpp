#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    uiInit();
}

MainWindow::~MainWindow(){
    delete ui;
}

/*
 * UI初始化
 */
void MainWindow::uiInit(){
    this->setWindowFlags(Qt::FramelessWindowHint );//无边界窗口,不能调整窗口的大小

    //添加logo
    this->setWindowIcon(QIcon(":/new/prefix1/CA-DCP.png"));

    //标题栏按钮提示
    ui->tbMini->setToolTip(tr("最小化"));
    ui->tbClose->setToolTip(tr("关闭"));
    ui->tbAbout->setToolTip(tr("关于"));

    //左边导航栏初始化
    QSize icoSize(24, 24);//图标大小
    QList<QToolButton *> tbtns = ui->wdLeft->findChildren<QToolButton *>();//获取导航栏按钮
    //循环遍历
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);//设置图标大小
        btn->setCheckable(true);//可选中
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));//绑定槽函数
    }
    //滚动条改变槽函数
    connect(ui->saWeld->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(bar_changed(int)));

    //建模初始化
    name="建模";
    ui->tbPart->setChecked(true);//默认为建模
    ui->lePartA->setText("90");
    ui->lePartB->setText("20");
    ui->lePartC->setText("6");
    ui->lePartD->setText("100");
    ui->lePartM->setText("3");

    //属性初始化
    //密度
    ui->leDens->setText("7.8e-9");
    //热导率
    ui->twCond->setRowCount(7);    //设置行数
    ui->twCond->setColumnCount(2); //设置列数
    ui->twCond->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twCond->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->twCond->verticalHeader()->setHidden(true);
    ui->twCond->horizontalHeader()->setHidden(true);
    //填写内容
    QTableWidgetItem *item = new QTableWidgetItem();//一格
    item->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item->setText("温度");
    ui->twCond->setItem(0,0,item);
    QTableWidgetItem *item_1 = new QTableWidgetItem();//一格
    item_1->setFlags(item_1->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_1->setText("热导率");
    ui->twCond->setItem(0,1,item_1);
    QString con[7]={"35.0","34.0","32.0","35.0","70.0","70.0"};
    QString con_temp[7]={"20.0","100.0","500.0","1300.0","1350.0","2000.0"};
    for(int i=0;i<6;i++){
        ui->twCond->setItem(i+1,0,new QTableWidgetItem(con_temp[i]));
        ui->twCond->setItem(i+1,1,new QTableWidgetItem(con[i]));
    }

    //潜热
    ui->twLate->setRowCount(2);    //设置行数
    ui->twLate->setColumnCount(3); //设置列数
    ui->twLate->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twLate->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->twLate->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->twLate->verticalHeader()->setHidden(true);
    ui->twLate->horizontalHeader()->setHidden(true);
    //填写内容
    QTableWidgetItem *item_2 = new QTableWidgetItem();//一格
    item_2->setFlags(item_2->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_2->setText("潜热");
    ui->twLate->setItem(0,2,item_2);
    QTableWidgetItem *item_3 = new QTableWidgetItem();//一格
    item_3->setFlags(item_3->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_3->setText("固相线温度");
    ui->twLate->setItem(0,1,item_3);
    QTableWidgetItem *item_4 = new QTableWidgetItem();//一格
    item_4->setFlags(item_4->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_4->setText("液相线温度");
    ui->twLate->setItem(0,0,item_4);
    ui->twLate->setItem(1,2,new QTableWidgetItem("220e6")); //设置表格内容
    ui->twLate->setItem(1,1,new QTableWidgetItem("1350")); //设置表格内容
    ui->twLate->setItem(1,0,new QTableWidgetItem("1400")); //设置表格内容

    //比热
    ui->twSpec->setRowCount(4);    //设置行数
    ui->twSpec->setColumnCount(2); //设置列数
    ui->twSpec->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twSpec->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->twSpec->verticalHeader()->setHidden(true);
    ui->twSpec->horizontalHeader()->setHidden(true);
    QTableWidgetItem *item_5 = new QTableWidgetItem();//一格
    item_5->setFlags(item_5->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_5->setText("比热");
    ui->twSpec->setItem(0,1,item_5);
    QTableWidgetItem *item_6 = new QTableWidgetItem();//一格
    item_6->setFlags(item_6->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_6->setText("温度");
    ui->twSpec->setItem(0,0,item_6);
    ui->twSpec->setItem(1,1,new QTableWidgetItem("460e6")); //设置表格内容
    ui->twSpec->setItem(2,1,new QTableWidgetItem("478e6")); //设置表格内容
    ui->twSpec->setItem(3,1,new QTableWidgetItem("500e6")); //设置表格内容
    ui->twSpec->setItem(1,0,new QTableWidgetItem("20")); //设置表格内容
    ui->twSpec->setItem(2,0,new QTableWidgetItem("50")); //设置表格内容
    ui->twSpec->setItem(3,0,new QTableWidgetItem("100")); //设置表格内容

    //分析步初始化
    //焊接分析步
    ui->tbStepWd->setRowCount(7);//设置行数
    ui->tbStepWd->setColumnCount(2); //设置列数
    ui->tbStepWd->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tbStepWd->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->tbStepWd->verticalHeader()->setHidden(true);
    ui->tbStepWd->horizontalHeader()->setHidden(true);
    QString str[7]={"焊接时间","分析步最大步数","增量初始值","增量最大值","增量最小值","每步最大温度变化","每步最大变化率"};
    QString value_welding[7]={"12.5","10000","0.05","0.005","5","60","0.1"};
    for(int i=0;i<7;i++){
            QTableWidgetItem *item = new QTableWidgetItem();//一格
            item->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
            item->setText(str[i]);
            ui->tbStepWd->setItem(i,0,item);
            ui->tbStepWd->setItem(i,1,new QTableWidgetItem(value_welding[i])); //设置表格内容
    }
    //冷却分析步
    ui->tbStepCl->setRowCount(7);//设置行数
    ui->tbStepCl->setColumnCount(2); //设置列数
    ui->tbStepCl->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tbStepCl->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->tbStepCl->verticalHeader()->setHidden(true);
    ui->tbStepCl->horizontalHeader()->setHidden(true);
    str[0]="冷却时间";
    QString value_colding[7]={"600.0","1000","0.01","0.001","6","60","0.1"};
    for(int i=0;i<7;i++){
            QTableWidgetItem *item = new QTableWidgetItem();//一格
            item->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));
            item->setText(str[i]);
            ui->tbStepCl->setItem(i,0,item);
            ui->tbStepCl->setItem(i,1,new QTableWidgetItem(value_colding[i])); //设置表格内容
    }

    //交互初始化
    //环境温度
    ui->leInte->setText("20");
    //换热系数
    ui->twInte->setRowCount(5);    //设置行数
    ui->twInte->setColumnCount(2); //设置列数
    ui->twInte->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twInte->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //隐藏表头和行号
    ui->twInte->verticalHeader()->setHidden(true);
    ui->twInte->horizontalHeader()->setHidden(true);
    //填写内容
    QTableWidgetItem *item_7 = new QTableWidgetItem();//一格
    item_7->setFlags(item->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_7->setText("温度");
    ui->twInte->setItem(0,0,item_7);
    QTableWidgetItem *item_8 = new QTableWidgetItem();//一格
    item_8->setFlags(item_8->flags() & (~Qt::ItemIsEditable& ~Qt::ItemIsSelectable));//不可选中，不可编辑
    item_8->setText("换热系数");
    ui->twInte->setItem(0,1,item_8);
    QString Film[4]={"20.0","100.0","300.0","2000.0"};
    QString Film_temp[4]={"0.006","0.01","0.03","0.3"};
    for(int i=0;i<4;i++){
        ui->twInte->setItem(i+1,1,new QTableWidgetItem(Film_temp[i]));
        ui->twInte->setItem(i+1,0,new QTableWidgetItem(Film[i]));
    }

    //加载初始化
    ui->leLoad->setText("20");
    QString path=QCoreApplication::applicationDirPath();//获取程序路径
    ui->leLoad2->setText(path.append("/welding/welding.for"));
}

/*
 * 导航栏按钮
 */
void MainWindow::buttonClick(){
    QToolButton *b = (QToolButton *)sender();
    name =b->text();
    QList<QToolButton *> tbtns = ui->wdLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
    if (name=="建模") {
        ui->saWeld->verticalScrollBar()->setValue(0);
    } else if (name=="属性"){
        ui->saWeld->verticalScrollBar()->setValue(483);
    } else if (name=="分析") {
        ui->saWeld->verticalScrollBar()->setValue(1182);
    } else if (name=="交互") {
        ui->saWeld->verticalScrollBar()->setValue(1575);
    } else if (name=="加载") {
        ui->saWeld->verticalScrollBar()->setValue(1857);
    }
}

/*
 * 退出按钮
 */
void MainWindow::on_tbClose_clicked(){
    this->close();
}

/*
 * 最小化按钮
 */
void MainWindow::on_tbMini_clicked(){
    this->showMinimized();
}

/*
 * 关于按钮
 */
void MainWindow::on_tbAbout_clicked(){
    About *about = new About(this);
    about->setWindowTitle(QStringLiteral("模式对话框"));
    about->exec();
}

/*
 * 鼠标可拖动
 */
void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        //改变移动状态.
        m_move = false;
    }
}

//选择热源子程序路径
void MainWindow::on_tbLoad_2_clicked(){
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("选择热源子程序"));
    //设置默认文件路径
    QString path=QCoreApplication::applicationDirPath();//获取程序路径
    fileDialog->setDirectory(path.append("/welding"));
    //设置文件过滤器
    fileDialog->setNameFilter(tr("File(*.for)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    if(fileNames.size())//选择了文件
        ui->leLoad2->setText(fileNames.at(0));
}

//增减表格
void MainWindow::on_tbCondAdd_clicked(){
    int count;
    count=ui->twCond->rowCount();
    ui->twCond->insertRow(count);
}

void MainWindow::on_tbCondSub_clicked(){
    int count;
    count=ui->twCond->rowCount();
    ui->twCond->removeRow(count-1);
}

void MainWindow::on_tbLateAdd_clicked(){
    int count;
    count=ui->twLate->rowCount();
    ui->twLate->insertRow(count);
}

void MainWindow::on_tbLateSub_clicked(){
    int count;
    count=ui->twLate->rowCount();
    ui->twLate->removeRow(count-1);
}

void MainWindow::on_tbSpecAdd_clicked(){
    int count;
    count=ui->twSpec->rowCount();
    ui->twSpec->insertRow(count);
}

void MainWindow::on_tbSpecSub_clicked(){
    int count;
    count=ui->twSpec->rowCount();
    ui->twSpec->removeRow(count-1);
}

void MainWindow::on_tbInteAdd_clicked(){
    int count;
    count=ui->twInte->rowCount();
    ui->twInte->insertRow(count);
}

void MainWindow::on_tbInteSub_clicked(){
    int count;
    count=ui->twInte->rowCount();
    ui->twInte->removeRow(count-1);
}

/*
 * 生成脚本
 */
QString MainWindow::createScript(QString name_str){
    QString str;
    /*
     *1 建模
     */
    if(name_str=="建模"){
        a=ui->lePartA->text();
        b=ui->lePartB->text();
        c=ui->lePartC->text();
        d=ui->lePartD->text();
        m=ui->lePartM->text();
        //1.1 创建草图s
        str.push_back("#\n#1 建模\n#\n#1.1 创建草图s\n");
        str.push_back("s = mdb.models['Model-1'].ConstrainedSketch(name='s1', sheetSize=200.0)\n");
        str.push_back(QString("s.Line(point1=(-%1-%2/2,%3), point2=(%1+%2/2,%3))\n").arg(a,b,c));
        str.push_back(QString("s.Line(point1=(%1+%2/2,%3), point2=(%1+%2/2,0))\n").arg(a,b,c));
        str.push_back(QString("s.Line(point1=(%1+%2/2,0), point2=(-%1-%2/2,0))\n").arg(a,b));
        str.push_back(QString("s.Line(point1=(-%1-%2/2,0), point2=(-%1-%2/2,%3))\n").arg(a,b,c));

        //1.2 拉伸
        str.push_back("#1.2 拉伸s\n");
        str.push_back("p = mdb.models['Model-1'].Part(name='steel_board', dimensionality=THREE_D,"
                        "type=DEFORMABLE_BODY)\n");
        str.push_back(QString("p.BaseSolidExtrude(sketch=s, depth=%1)\n").arg(d));

        //1.3 裁焊缝
        str.push_back("#1.3 裁焊缝s\n");
        str.push_back(QString("p.PartitionCellByPlaneThreePoints(cells=p.cells,"
                           "point1=(-%1/2,0,0), point2=(-%1/2,%2,0), point3=(-%1/2,0,%3))\n").arg(b,c,d));
        str.push_back(QString("p.PartitionCellByPlaneThreePoints(cells=p.cells,"
                           "point1=(%1/2,0,0), point2=(%1/2,%2,0), point3=(%1/2,0,%3))\n").arg(b,c,d));

        //1.4 划网格
        str.push_back("#1.4 划网格\n");
        str.push_back(QString("p.seedPart(size=%1, deviationFactor=0.1, minSizeFactor=0.1)\n").arg(m));
        str.push_back("p.generateMesh(regions=p.cells)\n");

        //1.5 更改网格类型
        str.push_back("#1.5 更改网格类型\n");
        str.push_back("elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)\n"
                      "p.setElementType(regions=(p.cells,), elemTypes=(elemType1,))\n");
    }

    /*
     *2 属性
     */
    if(name_str=="属性"){
        QString dens;
        dens=ui->leDens->text();
        int cond_count,late_count,spec_count;
        cond_count=ui->twCond->rowCount()-1;
        late_count=ui->twLate->rowCount()-1;
        spec_count=ui->twSpec->rowCount()-1;
        //2.1 创建钢属性steel
        str.push_back("#\n#2 属性\n#\n#2.1 创建钢属性steel\n");
        str.push_back("steel=mdb.models['Model-1'].Material(name='steel')\n");

        //密度
        str.push_back("#密度\n");
        str.push_back(QString("steel.Density(table=((%1, ), ))\n").arg(dens));

        //热导率
        QString condDate[cond_count][2];
        //读取每行数据
        for(int i=0;i<cond_count;i++){
            for(int j=0;j<2;j++){
                condDate[i][j]=ui->twCond->item(i+1,j)->text();
            }
        }
        str.push_back("#热导率\n");
        str.push_back("steel.Conductivity(temperatureDependency=ON, table=(");
        for(int i=0;i<cond_count;i++){
            str.push_back("(");
            str.push_back(condDate[i][1]);
            str.push_back(",");
            str.push_back(condDate[i][0]);
            str.push_back("),");
        }
        str.chop(1);//删除多余的逗号
        str.push_back("))\n");

        //潜热
        QString lateDate[cond_count][2];
        //读取每行数据
        for(int i=0;i<late_count;i++){
            for(int j=0;j<3;j++){
                lateDate[i][j]=ui->twLate->item(i+1,j)->text();
            }
        }
        str.push_back("#潜热\n");
        str.push_back("steel.LatentHeat(table=(");
        for(int i=0;i<late_count;i++){
            str.push_back("(");
            str.push_back(lateDate[i][2]);
            str.push_back(",");
            str.push_back(lateDate[i][1]);
            str.push_back(",");
            str.push_back(lateDate[i][0]);
            str.push_back("),");
        }
        //str.chop(1);//删除多余的逗号
        str.push_back("))\n");

        //比热
        QString specDate[spec_count][2];
        //读取每行数据
        for(int i=0;i<spec_count;i++){
            for(int j=0;j<2;j++){
                specDate[i][j]=ui->twSpec->item(i+1,j)->text();
            }
        }
        str.push_back("#比热\n");
        str.push_back("steel.SpecificHeat(temperatureDependency=ON, table=(");
        for(int i=0;i<spec_count;i++){
            str.push_back("(");
            str.push_back(specDate[i][1]);
            str.push_back(",");
            str.push_back(specDate[i][0]);
            str.push_back("),");
        }
        str.chop(1);//删除多余的逗号
        str.push_back("))\n");

        //2.2 建立截面属性
        str.push_back("#2.2 建立截面属性\n");
        str.push_back("mdb.models['Model-1'].HomogeneousSolidSection(name='Section-1',"
                      "material='steel', thickness=None)\n");

        //2.3 赋属性
        str.push_back("#2.3 赋属性\n");
        str.push_back("region = p.Set(cells=p.cells, name='Set-1')\n");
        str.push_back("p.SectionAssignment(region=region , sectionName='Section-1', offset=0.0,"
                      "offsetType=MIDDLE_SURFACE, offsetField='', thicknessAssignment=FROM_SECTION)\n");

        /*
         *3 装配
         */
        str.push_back("#\n#3 装配\n#\n#3.1 实例化部件\n");
        str.push_back("a=mdb.models['Model-1'].rootAssembly\n");
        str.push_back("pi=a.Instance(name='instance_part',part=p,dependent=ON)\n");
    }

    /*
     *4 分析步
     */
    if(name_str=="分析"){
        QString weldingData[7];
        QString coolingData[7];
        //读取每行数据
        for(int i=0;i<7;i++){
                weldingData[i]=ui->tbStepWd->item(i,1)->text();
        }
        for(int i=0;i<7;i++){
                coolingData[i]=ui->tbStepCl->item(i,1)->text();
        }
        //4.1 创建焊接分析步
        str.push_back("#\n#4 分析步\n#\n#4.1 创建焊接分析步\n");
        str.push_back(QString("mdb.models['Model-1'].HeatTransferStep(name='welding', previous='Initial',"
                              "description='welding',timePeriod=%1, maxNumInc=%2, initialInc=%3,"
                              "minInc=%4, maxInc=%5, deltmx=%6, mxdem=%7)\n").arg(weldingData[0],weldingData[1],weldingData[2]\
                ,weldingData[3],weldingData[4],weldingData[5],weldingData[6]));
        //4.2 创建冷却分析步
        str.push_back("#4.2 创建冷却分析步\n");
        str.push_back(QString("mdb.models['Model-1'].HeatTransferStep(name='cooling', previous='welding',"
                              "description='cooling',timePeriod=%1, maxNumInc=%2, initialInc=%3,"
                              "minInc=%4, maxInc=%5, deltmx=%6, mxdem=%7)\n").arg(coolingData[0],coolingData[1],coolingData[2]\
                ,coolingData[3],coolingData[4],coolingData[5],coolingData[6]));
        //4.3 创建场输出
        str.push_back("#4.3 创建场输出\n");
        str.push_back("mdb.models['Model-1'].fieldOutputRequests['F-Output-1'].setValues(variables=('NT', ))\n");
    }

    /*
     *5 交互
     */
    if(name_str=="交互"){
        a=ui->lePartA->text();
        b=ui->lePartB->text();
        c=ui->lePartC->text();
        d=ui->lePartD->text();
        int Inte_count;
        Inte_count=ui->twInte->rowCount()-1;
        //换热系数
        QString InteDate[Inte_count][2];
        //读取每行数据
        for(int i=0;i<Inte_count;i++){
         for(int j=0;j<2;j++){
             InteDate[i][j]=ui->twInte->item(i+1,j)->text();
         }
        }
        //5.1 创建换热系数（包含热辐射及热对流）
        str.push_back("#\n#5 交互\n#\n#5.1 创建换热系数（包含热辐射及热对流）\n");
        str.push_back("mdb.models['Model-1'].FilmConditionProp(name='IntProp-1', temperatureDependency=ON, dependencies=0, property=(");
        for(int i=0;i<Inte_count;i++){
         str.push_back("(");
         str.push_back(InteDate[i][1]);
         str.push_back(",");
         str.push_back(InteDate[i][0]);
         str.push_back("),");
        }
        str.chop(1);//删除多余的逗号
        str.push_back("))\n");
        //5.2 选择装配图实例表面
        str.push_back("#5.2 选择装配图实例表面\n");
        str.push_back("s = a.instances['instance_part'].faces\n");
        str.push_back(QString("faces=s.getByBoundingBox(xMin=-%1-%2/2,xMax=%1+%2/2,yMin=%3,yMax=%3,zMin=0,zMax=%5)\n").arg(a,b,c,d));
        str.push_back("region=a.Surface(side1Faces=faces, name='Surf-1')\n");
        //5.3 赋予换热系数
        str.push_back("#5.3 选择装配图实例表面\n");
        str.push_back(QString("mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='welding',"
                              "surface=region, definition=PROPERTY_REF, interactionProperty='IntProp-1',"
                              "sinkTemperature=%1, sinkAmplitude='', sinkDistributionType=UNIFORM,"
                              "sinkFieldName='')\n").arg(ui->leInte->text()));
    }

    /*
     *6 加载
     */
    if(name_str=="加载"){
        QString initTemp;
        initTemp=ui->leLoad->text();//焊件初始温度
        //6.1 给焊缝区加载移动热源
        str.push_back("#\n#6 加载\n#\n#6.1 给焊缝区加载移动热源\n");
        str.push_back("region = (a.instances['instance_part'].cells[2],)\n");
        str.push_back("mdb.models['Model-1'].BodyHeatFlux(name='welding_heat', createStepName='welding',"
                      "region=region, magnitude=1.0, distributionType=USER_DEFINED)\n");
        str.push_back("mdb.models['Model-1'].loads['welding_heat'].deactivate('cooling')\n");
        //6.2加载初始温度
        str.push_back("#6.2 2加载初始温度\n");
        str.push_back("c1 = a.instances['instance_part'].cells\n");
        str.push_back("region = a.Set(cells=c1, name='Set-1')\n");
        str.push_back(QString("mdb.models['Model-1'].Temperature(name='init_temp',"
                      "createStepName='Initial', region=region, distributionType=UNIFORM,"
                      "crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(%1, ))\n").arg(initTemp));
    }
    return str;
}

/*
 * 显示当前脚本
 */
void MainWindow::on_tbDisplayNow_clicked(){
   ui->teScript->setText(createScript(name));
}

/*
 * 显示工程脚本
 */
void MainWindow::on_tbDisplayAll_clicked(){
    QString str;
    str.push_back("#包含模块\n"
                  "from abaqus import *\n"
                  "from abaqusConstants import *\n"
                  "from caeModules import *\n"
                  "from driverUtils import executeOnCaeStartup\n");
    str.push_back(createScript("建模"));
    str.push_back(createScript("属性"));
    str.push_back(createScript("分析"));
    str.push_back(createScript("交互"));
    str.push_back(createScript("加载"));
    str.push_back(QString("mdb.Job(name='weld_thermal', model='Model-1', description='', type=ANALYSIS,"
                  "atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90,"
                  "memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True,"
                  "explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF,"
                  "modelPrint=OFF, contactPrint=OFF, historyPrint=OFF,"
                  "userSubroutine='%1',"
                  "scratch='', resultsFormat=ODB, multiprocessingMode=DEFAULT, numCpus=1,"
                  "numGPUs=0)\n").arg(ui->leLoad2->text()));
    ui->teScript->setText(str);
}

//复制到剪贴板
void MainWindow::on_tbCopy_clicked(){
    QClipboard *clipboard = QGuiApplication::clipboard();//获取系统剪贴板指针
    clipboard->setText(ui->teScript->toPlainText());//设置剪贴板内容
}

//滚动条改变
void MainWindow::bar_changed(int){
    //获取滚动条数值
    int bar_value=ui->saWeld->verticalScrollBar()->value();
    //所有导航栏按钮
    QList<QToolButton *> tbtns = ui->wdLeft->findChildren<QToolButton *>();
    if(bar_value>1867-150)
        name="加载";
    else if(bar_value>1585-150)
        name="交互";
    else if(bar_value>1192-150)
        name="分析";
    else if(bar_value>493-150)
        name="属性";
    else
        name="建模";
    foreach (QToolButton *btn, tbtns) {
        if (btn->text()==name) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
}
