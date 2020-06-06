# -*- coding: mbcs -*-

#包含模块
from abaqus import *
from abaqusConstants import *
from caeModules import *
from driverUtils import executeOnCaeStartup

#
#1 建模
#
#1.1 创建草图s
s = mdb.models['Model-1'].ConstrainedSketch(name='s1', sheetSize=200.0)
s.Line(point1=(-100.0, 6.0), point2=(100.0, 6.0))
s.Line(point1=(100.0, 6.0), point2=(100.0, 0.0))
s.Line(point1=(100.0, 0.0), point2=(-100.0, 0.0))
s.Line(point1=(-100.0, 0.0), point2=(-100.0, 6.0))

#1.2 拉伸
p = mdb.models['Model-1'].Part(name='steel_board', dimensionality=THREE_D, 
    type=DEFORMABLE_BODY)
p.BaseSolidExtrude(sketch=s, depth=100.0)

#1.3 裁焊缝
#依据三点拆分
p.PartitionCellByPlaneThreePoints(cells=p.cells, point1=(-10,0,0), point2=(-10,6,0), point3=(-10,0,100))
p.PartitionCellByPlaneThreePoints(cells=p.cells, point1=(10,0,0), point2=(10,6,0), point3=(10,0,100))

#
#2 设置属性
#
#2.1 创建钢属性steel
steel=mdb.models['Model-1'].Material(name='steel')
#密度
steel.Density(table=((7.8e-09, ), ))
#热导率
steel.Conductivity(temperatureDependency=ON, table=((35.0, 20.0), (34.0, 100.0), (32.0, 500.0), (35.0, 1300.0), (70.0, 1350.0), (70.0, 2000.0)))
#潜热
steel.LatentHeat(table=((220000000.0, 1350.0, 1400.0), ))
#比热
steel.SpecificHeat(temperatureDependency=ON, table=((460000000.0, 20.0), (478000000.0, 50.0), (500000000.0, 100.0)))

# 2.2 建立截面属性
mdb.models['Model-1'].HomogeneousSolidSection(name='Section-1', material='steel', thickness=None)

#2.3 赋属性
region = p.Set(cells=p.cells, name='Set-1')
p.SectionAssignment(region=region , sectionName='Section-1', offset=0.0, offsetType=MIDDLE_SURFACE, offsetField='', thicknessAssignment=FROM_SECTION)

#
#3 装配
#
#3.1 实例化部件
a=mdb.models['Model-1'].rootAssembly
pi=a.Instance(name='instance_part',part=p,dependent=ON)

#
#4 分析步
#
#4.1 创建焊接分析步
mdb.models['Model-1'].HeatTransferStep(name='welding', previous='Initial', description='welding', timePeriod=12.5, maxNumInc=10000, initialInc=0.05, minInc=0.0005, maxInc=5, deltmx=60.0, mxdem=0.1)
#4.2 创建冷却分析步
mdb.models['Model-1'].HeatTransferStep(name='cooling', previous='welding', description='cooling', timePeriod=600.0, maxNumInc=1000, initialInc=0.01, minInc=0.001, maxInc=6, deltmx=60, mxdem=0.1)
#4.3 创建场输出
mdb.models['Model-1'].fieldOutputRequests['F-Output-1'].setValues(variables=('NT', ))

#
#5 与环境交互
#
#5.1 创建换热系数（包含热辐射及热对流）
mdb.models['Model-1'].FilmConditionProp(name='IntProp-1', temperatureDependency=ON, dependencies=0, property=((0.006, 20.0), (0.01, 100.0), (0.03, 300.0), (0.3, 2000.0)))
#5.2 选择装配图实例表面
s = a.instances['instance_part'].faces
faces=s.getByBoundingBox(xMin=-100,xMax=100,yMin=6,yMax=6,zMin=0,zMax=100)
region=a.Surface(side1Faces=faces, name='Surf-1')
#5.3 赋予换热系数
mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='welding', 
    surface=region, definition=PROPERTY_REF, interactionProperty='IntProp-1', 
    sinkTemperature=20.0, sinkAmplitude='', sinkDistributionType=UNIFORM, 
    sinkFieldName='')

#
#6 加载
#
#6.1 给焊缝区加载移动热源
region = (a.instances['instance_part'].cells[2],)
#region = a.Set(cells=c1, name='welding_bead')
mdb.models['Model-1'].BodyHeatFlux(name='welding_heat', createStepName='welding', 
    region=region, magnitude=1.0, distributionType=USER_DEFINED)
#冷却过程不能激活热源
mdb.models['Model-1'].loads['welding_heat'].deactivate('cooling')

#6.2 加载初始温度
c1 = a.instances['instance_part'].cells
region = a.Set(cells=c1, name='Set-1')
mdb.models['Model-1'].Temperature(name='init_temp', 
    createStepName='Initial', region=region, distributionType=UNIFORM, 
    crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(20.0, ))

#
#7 划分网格
#
#7.1 划分网格
p.seedPart(size=3.0, deviationFactor=0.1, minSizeFactor=0.1)
p.generateMesh(regions=p.cells)

#7.2 更改网格类型
elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
p.setElementType(regions=(p.cells,), elemTypes=(elemType1,))

#
#8 创建分析步
#
mdb.Job(name='weld_thermal', model='Model-1', description='', type=ANALYSIS, 
    atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
    memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
    explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
    modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, 
    userSubroutine='C:\\Users\\31082\\Desktop\\abaqus\\welding.for', 
    scratch='', resultsFormat=ODB, multiprocessingMode=DEFAULT, numCpus=1, 
    numGPUs=0)
